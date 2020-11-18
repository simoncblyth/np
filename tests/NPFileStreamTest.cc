// gcc NPFileStreamTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/NPFileStreamTest && /tmp/NPFileStreamTest && xxd /tmp/a.npy.transport

/**
NPFileStreamTest.cc
====================
**/

#include <vector>
#include <string>
#include <fstream>

#include "NP.hh"


NP* make_array()
{
    NP* a = new NP("<f4", 10,4) ; 
    a->fillIndexFlat();  
    a->meta = "{\"src\": \"NPFileStreamTest.cc\"}" ; 
    return a ; 
}

void test_stream_out(const NP* a, const char* path)
{
    std::ofstream out(path, std::ios::out|std::ios::binary);
    out << *a ; 

    std::cout 
        << " test_stream_out "
        << " path " << path 
        << std::endl
        ; 
}

NP* test_stream_in( const char* path )
{
    std::ifstream in(path, std::ios::in|std::ios::binary);

    NP* a = new NP(); 
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
    NP* a = make_array(); 
    const char* path = "/tmp/a.npy.transport" ; 
    test_stream_out(a, path); 
    NP* b = test_stream_in(path); 
}


int main(int argc, char** argv)
{
    test_file_stream(); 
    return 0 ; 
}


