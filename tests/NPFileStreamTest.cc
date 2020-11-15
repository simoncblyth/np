// gcc NPFileStreamTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/NPFileStreamTest && /tmp/NPFileStreamTest && xxd /tmp/a.npy.transport

/**
NPFileStreamTest.cc
====================
**/

#include <vector>
#include <string>
#include <fstream>

#include "NP.hh"


NP<float>* make_array()
{
    NP<float>* a = new NP<float>(10,4) ; 
    a->fillIndexFlat();  
    a->meta = "{}" ; 
    return a ; 
}

void test_stream_out(const NP<float>* a, const char* path)
{
    std::ofstream out(path, std::ios::out|std::ios::binary);
    out << *a ; 

    std::cout 
        << " test_stream_out "
        << " path " << path 
        << std::endl
        ; 
}

NP<float>* test_stream_in( const char* path )
{
    std::ifstream in(path, std::ios::in|std::ios::binary);

    NP<float>* a = new NP<float>(); 
    in >> *a  ; 

    std::cout 
        << " test_stream_in "
        << " path " << path 
        << std::endl
        ; 

    a->dump(); 

    std::cout << " a.meta " << a->meta << std::endl ; 

    return  a; 
}


void test_file_stream()
{
    NP<float>* a = make_array(); 
    const char* path = "/tmp/a.npy.transport" ; 
    test_stream_out(a, path); 
    NP<float>* b = test_stream_in(path); 
}


int main(int argc, char** argv)
{
    test_file_stream(); 
    return 0 ; 
}


