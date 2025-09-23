/**
np_curl_test.cc
=================

::

    ~/np/tests/np_curl_test/np_curl_test.sh

**/


#include <vector>
#include <iostream>

#include "NP.hh"
#include "NP_CURL.h"


template<typename T>
void arr_dump(const NP* x, const char* sym, int i)
{
    std::cout << " i " << i << "\n" ;
    std::cout << " " << sym << ".sstr " << ( x ? x->sstr() : "-" ) << "\n" ;
    std::cout << " " << sym << ".desc " << ( x ? x->desc() : "-" ) << "\n" ;
    std::cout << " " << sym << ".repr " << ( x ? x->repr<T>() : "-" ) << "\n" ;
}


int main(void)
{
    NP* gs = NP::Load("$FOLD/gs.npy");
    arr_dump<float>(gs, "gs", -1);

    for(int i=0 ; i < 10 ; i++)
    {
       std::cout << "[-------------------- " << i << "\n" ;
       NP* ht = NP_CURL::TransformRemote(gs,i);
       arr_dump<float>(ht, "ht", i);
       std::cout << "]-------------------- " << i << "\n" ;
    }

    NP_CURL::Clear();

    return 0;
}



