// boost-;gcc np_server.cc -I.. -I$(boost-prefix)/include -L$(boost-prefix)/lib -std=c++11 -lstdc++  -o /tmp/np_server && /tmp/np_server 
/**
np_server.cc
==============

Started from  /usr/local/env/boost/basio/example/cpp03/chat/chat_server.cpp

**/

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "NP.hh"

using boost::asio::ip::tcp;

typedef NP<float>               np_message ; 
typedef std::deque<np_message> np_message_queue;

class np_participant
{
    public:
        virtual ~np_participant() {}
        virtual void deliver(const np_message& msg) = 0;
};

typedef boost::shared_ptr<np_participant> np_participant_ptr;

//----------------------------------------------------------------------

class np_room
{
    public:
        void join(np_participant_ptr participant);
        void leave(np_participant_ptr participant);
        void deliver(const np_message& msg);
    private:
        std::set<np_participant_ptr> participants_;
        enum { max_recent_msgs = 3 };
        np_message_queue recent_msgs_;
};

void np_room::join(np_participant_ptr participant)
{
    participants_.insert(participant);
    std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
    boost::bind(&np_participant::deliver, participant, _1));
}

void np_room::leave(np_participant_ptr participant)
{
    participants_.erase(participant);
}

void np_room::deliver(const np_message& msg)
{
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    std::for_each(
        participants_.begin(), participants_.end(),
        boost::bind(&np_participant::deliver, _1, boost::ref(msg))
    );
}

//----------------------------------------------------------------------

class np_session
    : 
    public np_participant,
    public boost::enable_shared_from_this<np_session>
{
    public:
        np_session(boost::asio::io_context& io_context, np_room& room);
        tcp::socket& socket();
        void start();
        void deliver(const np_message& msg);
        void handle_read_header(const boost::system::error_code& error);
        void handle_read_body(const boost::system::error_code& error);
        void handle_write(const boost::system::error_code& error);
    private:
        tcp::socket        socket_;
        np_room&          room_;
        np_message        read_msg_;
        np_message_queue  write_msgs_;
};

np_session::np_session(boost::asio::io_context& io_context, np_room& room)
    : 
    socket_(io_context),
    room_(room)
{
}

tcp::socket& np_session::socket()
{
    return socket_;
}

void np_session::start()
{
    room_.join(shared_from_this());
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_msg_._prefix),
        boost::bind(&np_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
        );
}


void np_session::handle_read_header(const boost::system::error_code& error)
{
    std::cout << "np_session::handle_read_header" << std::endl ; 
    if (!error && read_msg_.decode_prefix())
    {
        std::cout << "np_session::handle_read_header : decode_prefix succeeds " << std::endl ; 
        std::vector<boost::asio::mutable_buffer> np_bufs;
        np_bufs.push_back(boost::asio::buffer(read_msg_._hdr));
        np_bufs.push_back(boost::asio::buffer(read_msg_.data));
        np_bufs.push_back(boost::asio::buffer(read_msg_.meta));

        boost::asio::async_read(
            socket_, np_bufs, 
            boost::bind(&np_session::handle_read_body, shared_from_this(),boost::asio::placeholders::error)
        );
    }
    else
    {
        room_.leave(shared_from_this());
    }
}

void np_session::handle_read_body(const boost::system::error_code& error)
{
    std::cout << "np_session::handle_read_body" << std::endl ; 
    if (!error && read_msg_.decode_header())
    {
        read_msg_.dump(); 

        room_.deliver(read_msg_);
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_._prefix),
            boost::bind(&np_session::handle_read_header, shared_from_this(),boost::asio::placeholders::error)
        );
    }
    else
    {
        room_.leave(shared_from_this());
    }
}

void np_session::deliver(const np_message& msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        np_message& write_msg = write_msgs_.front() ; 

        std::vector<boost::asio::const_buffer> np_bufs;
        np_bufs.push_back(boost::asio::buffer(write_msg._prefix));
        np_bufs.push_back(boost::asio::buffer(write_msg._hdr));
        np_bufs.push_back(boost::asio::buffer(write_msg.data));
        np_bufs.push_back(boost::asio::buffer(write_msg.meta));

        boost::asio::async_write(
            socket_, 
            np_bufs, 
            boost::bind(&np_session::handle_write, shared_from_this(),boost::asio::placeholders::error)
        );
    }
}

void np_session::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        write_msgs_.pop_front();
        if (!write_msgs_.empty())
        {
            np_message& write_msg = write_msgs_.front() ; 

            std::vector<boost::asio::const_buffer> np_bufs;
            np_bufs.push_back(boost::asio::buffer(write_msg._prefix));
            np_bufs.push_back(boost::asio::buffer(write_msg._hdr));
            np_bufs.push_back(boost::asio::buffer(write_msg.data));
            np_bufs.push_back(boost::asio::buffer(write_msg.meta));

            boost::asio::async_write(
                socket_,
                np_bufs, 
                boost::bind(&np_session::handle_write, shared_from_this(),boost::asio::placeholders::error)
            );
        }
    }
    else
    {
        room_.leave(shared_from_this());
    }
}

typedef boost::shared_ptr<np_session> np_session_ptr;
//----------------------------------------------------------------------
class np_server
{
    public:
        np_server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint);
        void start_accept();
        void handle_accept(np_session_ptr session, const boost::system::error_code& error);
    private:
        boost::asio::io_context& io_context_;
        tcp::acceptor            acceptor_;
        np_room                 room_;
};

np_server::np_server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint)
    : 
    io_context_(io_context),
    acceptor_(io_context, endpoint)
{
    std::cout << "np_server::np_server" << std::endl ; 
    start_accept();
}

void np_server::start_accept()
{
    std::cout << "np_server::start_accept" << std::endl ; 
    np_session_ptr new_session(new np_session(io_context_, room_));
    acceptor_.async_accept(
        new_session->socket(),
        boost::bind(&np_server::handle_accept, this, new_session, boost::asio::placeholders::error)
    );
}
 
void np_server::handle_accept(np_session_ptr session, const boost::system::error_code& error)
{
    std::cout << "np_server::handle_accept" << std::endl ; 
    if(!error)
    {
        session->start();
    }
    start_accept();
}
//----------------------------------------------------------------------


typedef boost::shared_ptr<np_server> np_server_ptr;
typedef std::list<np_server_ptr> np_server_list;

//----------------------------------------------------------------------
const char* getenv_(const char* key, const char* fallback){ return getenv(key) ? getenv(key) : fallback ; }
const char* getport(){ return getenv_("TCP_PORT", "15006" ) ; }

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            argc = 2 ; 
            argv[1] = (char*)getport(); 

   
        }
        boost::asio::io_context io_context;
        np_server_list servers;
        for (int i = 1; i < argc; ++i)
        {
            using namespace std; // For atoi.
            std::cout << "np_server port:" << argv[i] <<  std::endl ; 
            tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
            np_server_ptr server(new np_server(io_context, endpoint));
            servers.push_back(server);
        }
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

