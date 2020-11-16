// gcc net_hdr_test.cc -std=c++11 -I.. -lstdc++ -o /tmp/net_hdr_test && /tmp/net_hdr_test 

#include <iostream> 
#include "net_hdr.hh"

void net_hdr_test(const std::vector<unsigned>& items0  )
{
    std::string hdr = net_hdr::pack(items0);
    assert( hdr.length() == items0.size()*4 );

    std::vector<unsigned> items1 ;
    net_hdr::unpack( hdr, items1 );

    assert( items0.size() == items1.size() );

    for(unsigned i=0 ; i < items0.size() ; i++)
    {
        assert( items0[i] == items1[i] ); 
    }
}

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl ;

    std::vector<unsigned> items = { 0x12345678, 0xdeadbeef, 0xf0f0f0f0 } ;
    net_hdr_test(items);

    return 0 ;
}

