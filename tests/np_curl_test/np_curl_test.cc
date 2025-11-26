/**
np_curl_test.cc
=================

::

    ~/np/tests/np_curl_test/np_curl_test.sh

**/


#include <vector>
#include <iostream>

#include "NP.hh"

#ifdef WITH_CURL
#include "NP_CURL.h"
#endif


template<typename T>
void arr_dump(const NP* x, const char* sym, const char* name )
{
    std::cout << name << "\n" ;
    std::cout << " " << sym << ".sstr " << ( x ? x->sstr() : "-" ) << "\n" ;
    std::cout << " " << sym << ".desc " << ( x ? x->desc() : "-" ) << "\n" ;
    std::cout << " " << sym << ".repr " << ( x ? x->repr<T>() : "-" ) << "\n" ;
}


int main(void)
{

#ifdef WITH_CURL
    NP* gs = NP::Load("$FOLD/gs.npy");
    if(!gs)
    {
        std::cerr << "FAILED TO LOAD gs \n";
        return 1 ;
    }

    arr_dump<float>(gs, "gs", "init");

    for(int i=0 ; i < 10 ; i++)
    {
       std::cout << "[-------------------- " << i << "\n" ;
       gs->set_meta<int>("metacheck", i*100) ;

       NP* ht = NP_CURL::TransformRemote(gs,i);
       std::cout << "ht.meta\n" << ht->meta << "]\n" ;

       const char* htname = U::Format("$FOLD/ht%0.3d.npy", i );
       ht->save(htname);

       arr_dump<float>(ht, "ht", htname);
       std::cout << "]-------------------- " << i << "\n" ;
    }

    NP_CURL::Clear();

    return 0;
#else
    std::cerr << "NOT:WITH_CURL - YOU NEED TO REBUILD WITH NEW ENOUGH LIBCURL FOR THIS\n" ;
    return 1;
#endif

}



