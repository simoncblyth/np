// gcc NPUTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/NPUTest && /tmp/NPUTest

/**
NPUTest.cc
============

Writes "a.npy" array even without even using NP, just uses
NPU to form the header and writes that
to the stream followed by the array data.

This avoids duplicating memory.

**/


#include <vector>
#include <string>
#include <fstream>
#include "NPU.hh"


void test_make_header()
{

    std::vector<float> v ;
    for( int i=0 ; i < 10 ; i++ ) v.push_back(float(i)) ;

    std::vector<NPU::INT> shape ;
    shape.push_back(v.size()) ;


    std::string hdr = NPU::make_header<float>( shape ) ;
    int num_values = NPS::size(shape);

    const char* path = "/tmp/a.npy" ;

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << hdr ;
    stream.write(reinterpret_cast<const char*>(v.data()), sizeof(float)*num_values);

    std::cout
        << " writing "
        << " num_values " << num_values
        << " path " << path
        << " NPU::xxdisplay(hdr,16,'.') "
        << std::endl
        << std::endl
        << NPU::xxdisplay(hdr, 16, '.' )
        << std::endl
        ;

    /**
    np.save("/tmp/b.npy", np.linspace(0,9,10, dtype=np.float32) )
    **/
}

void test_endian_detect()
{
    std::cout << "endian::detect() " << endian::detect() << std::endl ;
}

void test_FormName()
{
    const char* prefix = "pfx" ;
    int idx = 10 ;
    const char* ext = ".npy" ;
    const char* body = "body" ;

    std::string s0 = U::FormName(prefix, idx, ext);
    std::cout << " U::FormName s0 : [" << s0 << "]" << std::endl ;

    std::string s1 = U::FormName(prefix, body, ext);
    std::cout << " U::FormName s1 : [" << s1 << "]" << std::endl ;
}

void test_FormatLog()
{
    for(int i=0 ; i < 100 ; i++) std::cout << U::FormatLog() << "\n" ;
}



int main(int argc, char** argv)
{
    //test_make_header();
    //test_endian_detect();
    //test_FormName();
    test_FormatLog();

    return 0 ;
}
