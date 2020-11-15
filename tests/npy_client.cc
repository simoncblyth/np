// started from /usr/local/env/boost/basio/example/cpp03/chat/chat_client.cpp
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "NP.hh"

using boost::asio::ip::tcp;

typedef NP<float>               npy_message ; 
typedef std::deque<npy_message> npy_message_queue;

class npy_client
{
    public:
        npy_client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);
        void write(const npy_message& msg);
        void close();
    private:
        void handle_connect(    const boost::system::error_code& error);
        void handle_read_header(const boost::system::error_code& error);
        void handle_read_body(  const boost::system::error_code& error);

        void do_write(npy_message msg);
        void handle_write(const boost::system::error_code& error);
        void do_close();
    private:
        boost::asio::io_context& io_context_;
        tcp::socket              socket_;
        npy_message              read_msg_;
        npy_message_queue        write_msgs_;
};


npy_client::npy_client(
    boost::asio::io_context& io_context,
    const tcp::resolver::results_type& endpoints)
    : 
    io_context_(io_context),
    socket_(io_context)
{
    std::cout << "npy_client::npy_client" << std::endl ;  
    boost::asio::async_connect(
        socket_, 
        endpoints,
        boost::bind(&npy_client::handle_connect, this,boost::asio::placeholders::error)
    );
}

void npy_client::write(const npy_message& msg)
{
    std::cout << "npy_client::write msg " << msg.desc() << std::endl ; 
    boost::asio::post(io_context_,boost::bind(&npy_client::do_write, this, msg));
}

void npy_client::close()
{
    std::cout << "npy_client::close " << std::endl ; 
    boost::asio::post(io_context_, boost::bind(&npy_client::do_close, this));
}

void npy_client::handle_connect(const boost::system::error_code& error)
{
    std::cout << "npy_client::handle_connect" << std::endl ;  
    if (!error)
    {
        boost::asio::async_read(socket_,
            boost::asio::buffer(read_msg_.read_net_hdr.data(), net_hdr::LENGTH),
            boost::bind(&npy_client::handle_read_header, this, boost::asio::placeholders::error)
        );
    }
}

void npy_client::handle_read_header(const boost::system::error_code& error)
{
    std::cout << "npy_client::handle_read_header" << std::endl ;  
    if (!error && read_msg_.read_item_size(0) > 0 )
    {
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
            boost::bind(&npy_client::handle_read_body, this, boost::asio::placeholders::error)
        );
    }
    else
    {
        do_close();
    }
}

void npy_client::handle_read_body(const boost::system::error_code& error)
{
    std::cout << "npy_client::handle_read_body" << std::endl ;  
    if (!error)
    {
        std::cout.write(read_msg_.body(), read_msg_.body_length());
        std::cout << "\n";
        boost::asio::async_read(socket_,
            boost::asio::buffer(read_msg_.data(), npy_message::header_length),
            boost::bind(&npy_client::handle_read_header, this, boost::asio::placeholders::error)
        );
    }
    else
    {
        do_close();
    }
}

void npy_client::do_write(npy_message msg)
{
    std::cout << "npy_client::do_write" << std::endl ;  
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front().data(),write_msgs_.front().length()),
            boost::bind(&npy_client::handle_write, this, boost::asio::placeholders::error)
        );
    }
}
 
void npy_client::handle_write(const boost::system::error_code& error)
{
    std::cout << "npy_client::handle_write" << std::endl ;  
    if (!error)
    {
        write_msgs_.pop_front();
        if (!write_msgs_.empty())
        {
            boost::asio::async_write(socket_,
                boost::asio::buffer(write_msgs_.front().data(),write_msgs_.front().length()),
                boost::bind(&npy_client::handle_write, this,boost::asio::placeholders::error)
            );
        }
    }
    else
    {
        do_close();
    }
}

void npy_client::do_close()
{
    std::cout << "npy_client::do_close" << std::endl ;  
    socket_.close();
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: npy_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);

        npy_client c(io_context, endpoints);
        boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

        char line[npy_message::max_body_length + 1];
        while (std::cin.getline(line, npy_message::max_body_length + 1))
        {
            using namespace std; // For strlen and memcpy.

            npy_message msg;
            msg.body_length(strlen(line));
            memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();

            c.write(msg);
        }

        c.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

