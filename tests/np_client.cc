// boost-;gcc np_client.cc -I.. -I$(boost-prefix)/include -L$(boost-prefix)/lib -std=c++11 -lstdc++ -lboost_thread -o /tmp/np_client && /tmp/np_client 
/**
np_client.cpp
================

started from /usr/local/env/boost/basio/example/cpp03/chat/chat_client.cpp

**/

#include <cstdlib>
#include <deque>
#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "NP.hh"

using boost::asio::ip::tcp;

typedef NP<float>               np_message ; 
typedef std::deque<np_message>  np_message_queue;

class np_client
{
    public:
        np_client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);
        void write(const np_message& msg);
        void close();
    private:
        void handle_connect(    const boost::system::error_code& error);
        void handle_read_header(const boost::system::error_code& error);
        void handle_read_body(  const boost::system::error_code& error);

        void do_write(np_message msg);
        void handle_write(const boost::system::error_code& error);
        void do_close();
    private:
        boost::asio::io_context& io_context_;
        tcp::socket              socket_;
        np_message              read_msg_;
        np_message_queue        write_msgs_;
};

np_client::np_client(
    boost::asio::io_context& io_context,
    const tcp::resolver::results_type& endpoints)
    : 
    io_context_(io_context),
    socket_(io_context)
{
    std::cout << "np_client::np_client" << std::endl ;  
    boost::asio::async_connect(
        socket_, 
        endpoints,
        boost::bind(&np_client::handle_connect, this, boost::asio::placeholders::error)
    );
}

void np_client::write(const np_message& msg)
{
    std::cout << "np_client::write msg " << msg.desc() << std::endl ; 
    boost::asio::post(io_context_,boost::bind(&np_client::do_write, this, msg));
}

void np_client::close()
{
    std::cout << "np_client::close " << std::endl ; 
    boost::asio::post(io_context_, boost::bind(&np_client::do_close, this));
}

void np_client::handle_connect(const boost::system::error_code& error)
{
    std::cout << "np_client::handle_connect" << std::endl ;  
    if (!error)
    {
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_._net_hdr),
            boost::bind(&np_client::handle_read_header, this, boost::asio::placeholders::error)
        );
    }
}

void np_client::handle_read_header(const boost::system::error_code& error)
{
    std::cout << "np_client::handle_read_header" << std::endl ;  
    if (!error && read_msg_.decode_net_header() )
    {
        std::vector<boost::asio::mutable_buffer> np_bufs;
        np_bufs.push_back(boost::asio::buffer(read_msg_._hdr));
        np_bufs.push_back(boost::asio::buffer(read_msg_.data));
        np_bufs.push_back(boost::asio::buffer(read_msg_.meta));

        boost::asio::async_read(
            socket_, np_bufs,
            boost::bind(&np_client::handle_read_body, this, boost::asio::placeholders::error)
        );
    }
    else
    {
        do_close();
    }
}

void np_client::handle_read_body(const boost::system::error_code& error)
{
    std::cout << "np_client::handle_read_body" << std::endl ;  
    if (!error && read_msg_.decode_arr_header())
    {
        read_msg_.dump(); 

        boost::asio::async_read(socket_,
            boost::asio::buffer(read_msg_._net_hdr),
            boost::bind(&np_client::handle_read_header, this, boost::asio::placeholders::error)
        );
    }
    else
    {
        do_close();
    }
}

void np_client::do_write(np_message msg)
{
    std::cout << "np_client::do_write" << std::endl ;  

    msg.update_headers(); 

    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        np_message& write_msg = write_msgs_.front() ; 

        std::vector<boost::asio::const_buffer> np_bufs;
        np_bufs.push_back(boost::asio::buffer(write_msg._net_hdr));
        np_bufs.push_back(boost::asio::buffer(write_msg._hdr));
        np_bufs.push_back(boost::asio::buffer(write_msg.data));
        np_bufs.push_back(boost::asio::buffer(write_msg.meta));

        boost::asio::async_write(socket_, np_bufs,
            boost::bind(&np_client::handle_write, this, boost::asio::placeholders::error)
        );
    }
}
 
void np_client::handle_write(const boost::system::error_code& error)
{
    std::cout << "np_client::handle_write" << std::endl ;  
    if (!error)
    {
        write_msgs_.pop_front();
        if (!write_msgs_.empty())
        {
            np_message& write_msg = write_msgs_.front() ; 

            std::vector<boost::asio::const_buffer> np_bufs;
            np_bufs.push_back(boost::asio::buffer(write_msg._net_hdr));
            np_bufs.push_back(boost::asio::buffer(write_msg._hdr));
            np_bufs.push_back(boost::asio::buffer(write_msg.data));
            np_bufs.push_back(boost::asio::buffer(write_msg.meta));

            boost::asio::async_write(socket_, np_bufs,
                boost::bind(&np_client::handle_write, this,boost::asio::placeholders::error)
            );
        }
    }
    else
    {
        do_close();
    }
}

void np_client::do_close()
{
    std::cout << "np_client::do_close" << std::endl ;  
    socket_.close();
}

const char* getenv_(const char* key, const char* fallback){ return getenv(key) ? getenv(key) : fallback ; }
const char* gethost(){ return getenv_("TCP_HOST", "127.0.0.1") ; }
const char* getport(){ return getenv_("TCP_PORT", "15006" ) ; }

std::string make_meta(unsigned count)
{
    const char* head = R"({"from":"np_client", "count":)";    
    const char* tail = R"( })";    
    std::stringstream ss ; 
    ss << head << count << tail ; 
    return ss.str(); 
}

int main(int argc, char** argv)
{
    try
    {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        const char* host = gethost(); 
        const char* port = getport(); 
        std::cout << "np_client host:" << host << " port:" << port << std::endl ; 
        tcp::resolver::results_type endpoints = resolver.resolve(host, port);

        np_client c(io_context, endpoints);
        boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

        np_message msg(10,4) ;
        msg.meta = make_meta(42); 
        msg.fillIndexFlat();
        msg.dump();  

        c.write(msg);

        c.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

