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
    std::cout << "[arr_dump " << name << "\n" ;
    std::cout << " " << sym << ".sstr " << ( x ? x->sstr() : "-" ) << "\n" ;
    std::cout << " " << sym << ".desc " << ( x ? x->desc() : "-" ) << "\n" ;
    std::cout << " " << sym << ".repr " << ( x ? x->repr<T>() : "-" ) << "\n" ;
    std::cout << "]arr_dump\n" ;
}

#ifdef WITH_CURL
int main()
{
    NP* gs = NP::Load("$FOLD/gs.npy");
    if(!gs)
    {
        std::cerr << "FAILED TO LOAD gs \n";
        return 1 ;
    }

    arr_dump<float>(gs, "gs", "init");


    NP_CURL* nc = NP_CURL::Get();

    if(nc->level > 0) std::cout << nc->desc();


    for(int i=0 ; i < 10 ; i++)
    {
       if(nc->level > 0) std::cout << U::Log("[--------------------\n") ;
       //gs->set_meta<int>("metacheck", i*100) ;

       size_t index = i ;
       size_t count = 100 ; // dummy value, could extract from gs but not easily at this level

       NP* ht = nc->transformRemote(gs,index,count);
       if(!ht)
       {
           std::cerr << "NP_CURL::TransformRemote returned nullptr ht - is the server running ? \n" ;
           return 1 ;
       }

       if(nc->level > 0) std::cout << "ht.meta\n" << ht->meta << "]\n" ;

       const char* htname = U::Format("$FOLD/ht%0.3d.npy", i );
       ht->save(htname);

       arr_dump<float>(ht, "ht", htname);
       if(nc->level > 0) std::cout << U::Log("]--------------------\n") ;
    }

    NP_CURL::Clear();

    return 0;
}
#else
int main()
{
    std::cerr << "NOT:WITH_CURL - YOU NEED TO REBUILD WITH NEW ENOUGH LIBCURL FOR THIS\n" ;
    return 1;
}
#endif


