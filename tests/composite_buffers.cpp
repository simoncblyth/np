// boost-;gcc -std=c++11 composite_buffers.cpp -I$(boost-prefix)/include -lstdc++ -o /tmp/composite_buffers && /tmp/composite_buffers s

/**
composite_buffers.cpp
-----------------------

Experiment with scatter-gather copy/read/write 

https://www.boost.org/doc/libs/1_51_0/doc/html/boost_asio/reference/buffer.html

https://www.boost.org/doc/libs/1_52_0/doc/html/boost_asio/overview/core/buffers.html

* A scatter-read receives data into multiple buffers.
* A gather-write transmits multiple buffers.

https://stackoverflow.com/questions/14413322/how-to-create-buffer-sequence

https://www.boost.org/doc/libs/1_52_0/doc/html/boost_asio/example/serialization/connection.hpp

**/

#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const char* getenv_(const char* key, const char* fallback){ return getenv(key) ? getenv(key) : fallback ; } 
const char* gethost(){ return getenv_("TCP_HOST", "127.0.0.1") ; } 
const char* getport(){ return getenv_("TCP_PORT", "15008" ) ; } 

void test_copy_gather()  // succeeds
{
    std::cout << "test_copy_gather" << std::endl ; 
    std::string s1("red"); 
    std::string s2("green"); 
    std::string s3("blue"); 

    std::vector<boost::asio::const_buffer> bufs;
    bufs.push_back(boost::asio::buffer(s1));
    bufs.push_back(boost::asio::buffer(s2));
    bufs.push_back(boost::asio::buffer(s3));

    size_t sz = boost::asio::buffer_size(bufs) ;
    std::cout << " sz " << sz << std::endl ; 

    std::string s123(sz,'\0');
    boost::asio::buffer_copy(boost::asio::buffer(s123), bufs); 

    std::cout << " s123 " << s123 << std::endl ;  
    assert( s123.compare("redgreenblue") == 0 ); 
}

void test_copy_scatter()  // now succeeds 
{
    std::cout << "test_copy_scatter" << std::endl ; 
    std::string s1(3,'\0');
    std::string s2(5,'\0');
    std::string s3(4,'\0');

    std::vector<boost::asio::mutable_buffer> mbufs;
    mbufs.push_back(boost::asio::buffer(s1));
    mbufs.push_back(boost::asio::buffer(s2));
    mbufs.push_back(boost::asio::buffer(s3));

    std::string src("redgreenblue"); 

    boost::asio::buffer_copy(mbufs, boost::asio::buffer(src)); 

    // somehow very tempting to do the below, which doesnt complain, but doesnt work  
    //     boost::asio::buffer_copy(boost::asio::buffer(mbufs), boost::asio::buffer(src)); 

    std::cout << "s1 " << s1 << std::endl ; 
    std::cout << "s2 " << s2 << std::endl ; 
    std::cout << "s3 " << s3 << std::endl ; 

    assert( s1.compare("red") == 0 );  
    assert( s2.compare("green") == 0 );  
    assert( s3.compare("blue") == 0 );  
}


int stream_server()
{
    std::cout << "stream_server" << std::endl ; 
    std::string msg = "0123456789ab" ; 
    assert( msg.length() == 12 ); 
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
                std::cout << "server sending msg via stream " << std::endl ; 
                stream << msg  ;
            }   
        }   
    }   
    catch (std::exception& e)
    {   
        std::cerr << e.what() << std::endl;
    }   
    return 0 ; 
}

int sock_server()
{
    std::cout << "sock_server" << std::endl ; 
    std::string msg = "0123456789ab" ; 
    assert( msg.length() == 12 ); 

    std::string s1("red") ; 
    std::string s2("green") ; 
    std::string s3("blue") ; 
    std::vector<char> s4 ; 

    s4.resize(msg.length()) ; 
    memcpy( s4.data(), msg.data(), msg.length() ); 

    std::vector<boost::asio::const_buffer> bufs;
    bufs.push_back(boost::asio::buffer(s1));
    bufs.push_back(boost::asio::buffer(s2));
    bufs.push_back(boost::asio::buffer(s3));
    bufs.push_back(boost::asio::buffer(s4));

    try 
    {   
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), atoi(getport()));
        tcp::acceptor acceptor(io_context, endpoint);
        std::cout << "server startup" << std::endl; 
        for (;;)
        {   
            tcp::socket socket(io_context);
            boost::system::error_code ec; 
            acceptor.accept(socket, ec);
            if (!ec)
            {   
                std::cout << "server sending msg via socket " << std::endl ; 
                boost::asio::write(socket, bufs, ec);
                if(ec) std::cout << "write error" << std::endl ; 
            }   
        }   
    }   
    catch (std::exception& e)
    {   
        std::cerr << e.what() << std::endl;
    }   
    return 0 ; 
}


int stream_client()
{
    std::cout << "stream_client" << std::endl ; 
    try 
    {   
        tcp::iostream stream(gethost(), getport());
        if (!stream)
        {
            std::cout << "Unable to connect: " << stream.error().message() << std::endl;
            return 1;
        }
        std::cout << "client recv msg from stream " << std::endl ;
        std::string msg ; 
        stream >> msg  ;
        std::cout << msg << std::endl ;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0 ;
}

int sock_client()
{
    std::cout << "sock_client" << std::endl ; 
    std::string s1(3,'\0') ; 
    std::string s2(5,'\0') ; 
    std::string s3(4,'\0') ; 

    std::vector<char> s4 ; 
    s4.resize(12) ; 

    std::vector<boost::asio::mutable_buffer> mbufs;
    mbufs.push_back(boost::asio::buffer(s1));
    mbufs.push_back(boost::asio::buffer(s2));
    mbufs.push_back(boost::asio::buffer(s3));
    mbufs.push_back(boost::asio::buffer(s4));

    std::cout << "sock_client" << std::endl ; 
    try 
    {   
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(gethost(), getport());
        tcp::socket socket(io_context);  
        boost::asio::connect(socket, endpoints);
        std::cout << "connected" << std::endl ; 

        size_t num_bytes = socket.receive(mbufs);
        std::cout << "received " << num_bytes << std::endl ; 
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "s1:[" << s1 << "]" << std::endl ; 
    std::cout << "s2:[" << s2 << "]" << std::endl ; 
    std::cout << "s3:[" << s3 << "]" << std::endl ; 

    std::string _s4(s4.data(), s4.size()) ; 
    std::cout << "_s4:[" << _s4 << "]" << std::endl ; 

    return 0 ;
}


int main(int argc, char** argv)
{
     return argc > 1 && argv[1][0] == 's' ? sock_server() : sock_client() ;
    //test_copy_gather(); 
    //test_copy_scatter(); 
    //return 0 ; 
}

