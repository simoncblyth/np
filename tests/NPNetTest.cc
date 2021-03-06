// boost-;gcc NPNetTest.cc -std=c++11 -I.. -I$(boost-prefix)/include -lpthread -lstdc++ -o /tmp/NPNetTest && /tmp/NPNetTest 
/**
NPNetTest.cc
=============

Start server in one session::

    /tmp/NPNetTest s

On invoking client in another session the server responds with 
an array sent via the socket using tcp::iostream.::

    /tmp/NPNetTest 

Note that the same executable acts as both server and client according 
to the argument.
**/

#include <string>
#include <sstream>
#include <iostream>
#include <boost/asio.hpp>
#include "NP.hh"

using boost::asio::ip::tcp;

const char* getenv_(const char* key, const char* fallback){ return getenv(key) ? getenv(key) : fallback ; }
const char* gethost(){ return getenv_("TCP_HOST", "127.0.0.1") ; }
const char* getport(){ return getenv_("TCP_PORT", "15008" ) ; }

std::string make_meta(unsigned count)
{
    const char* head = R"({"from":"make_meta", "count":)";     
    const char* tail = R"( })";     
    std::stringstream ss ; 
    ss << head << count << tail ; 
    return ss.str(); 
}
int server()
{
    NP* a = new NP("<f4", 10,4) ; a->fillIndexFlat(); a->meta = "{}" ; 
    unsigned count(0); 
    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), atoi(getport()));
        tcp::acceptor acceptor(io_context, endpoint);
        std::cout << "server startup" << std::endl; 
        for (;;)
        {
            tcp::iostream stream;
            boost::system::error_code ec;
            acceptor.accept(stream.socket(), ec);
            if (!ec)
            {
                std::cout << "server sending array via stream " << count << std::endl ; 
                a->meta = make_meta(count); 
                count++ ; 
                stream << *a ;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0 ; 
}
int client()
{
    try
    {
        tcp::iostream stream(gethost(), getport());
        if (!stream){
            std::cout << "Unable to connect: " << stream.error().message() << std::endl;
            return 0;
        }
        std::cout << "client recv array from stream " << std::endl ; 
        NP* a = new NP() ; 
        stream >> *a ; 
        a->dump(); 
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0 ; 
}
int main(int argc, char** argv){ return ( argc > 1 && argv[1][0] == 's' ) ? server() : client() ; }
