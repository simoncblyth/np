#pragma once

/**
net_hdr
---------

Packing and unpacking of simple network header
composed of a small number of 32bit unsigned ints 
expressed in big endian "network order". 

**/

#include <cstdint>
#include <cassert>
#include <vector>
#include <string>


struct net_hdr
{
    union uc4_t {
        uint32_t          u    ;   
        char              c[4] ; 
    };  
    static std::string pack(const std::vector<unsigned> items);
    static void unpack( const std::string& hdr         , std::vector<unsigned>& items );
    static void unpack( char* data, unsigned num_bytes , std::vector<unsigned>& items );
};

std::string net_hdr::pack(const std::vector<unsigned> items) // static 
{
    assert( 4 == sizeof(unsigned)); 
    unsigned ni = items.size(); 

    uc4_t uc4 ; 
    std::string hdr(ni*4, '\0' );  
    for(unsigned i=0 ; i < ni ; i++)
    {   
        uc4.u = htonl(items[i]) ;   // to big endian or "network order"
        memcpy( (void*)(hdr.data() + i*4), &(uc4.c[0]), 4 );  
    }   
    return hdr ; 
}

void net_hdr::unpack( const std::string& hdr, std::vector<unsigned>& items ) // static
{
    unpack((char*)hdr.data(), hdr.length(), items );
}

void net_hdr::unpack( char* data, unsigned num_bytes, std::vector<unsigned>& items ) // static
{
    assert( 4 == sizeof(unsigned)); 
    unsigned ni = num_bytes/sizeof(unsigned); 

    items.clear(); 
    items.resize(ni); 

    uc4_t uc4 ; 
    for(unsigned i=0 ; i < ni ; i++)
    {   
        memcpy( &(uc4.c[0]), data + i*4, 4 );  
        items[i] = ntohl(uc4.u) ;   // from big endian to endian-ness of host  
    }   
}



