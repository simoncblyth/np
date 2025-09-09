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


NP* arr_make()
{
    NP* a = NP::Make<float>( 10, 4, 4); 
    a->fillIndexFlat();
    a->set_meta<float>( "red", 1.f );  
    a->set_meta<float>( "green", 2.f );  
    a->set_meta<float>( "blue", 3.f );  
    a->set_meta<std::string>( "msg", "np_curl_test" );  
    return a ; 
}


template<typename T>
void arr_dump(const NP* x, char sym)
{
    std::cout << " " << sym << ".sstr " << ( x ? x->sstr() : "-" ) << "\n" ;
    std::cout << " " << sym << ".desc " << ( x ? x->desc() : "-" ) << "\n" ;
    std::cout << " " << sym << ".repr " << ( x ? x->repr<T>() : "-" ) << "\n" ;
}


int main(void) 
{
    NP* a = arr_make()                 ; arr_dump<float>(a, 'a');
    NP* b = NP_CURL::TransformRemote(a); arr_dump<float>(b, 'b');
    NP* c = NP_CURL::TransformRemote(b); arr_dump<float>(c, 'c');
    NP* d = NP_CURL::TransformRemote(c); arr_dump<float>(d, 'd');
    NP* e = NP_CURL::TransformRemote(d); arr_dump<float>(e, 'e');
    NP* f = NP_CURL::TransformRemote(e); arr_dump<float>(f, 'f');
    NP* g = NP_CURL::TransformRemote(f); arr_dump<float>(g, 'g');

    NP_CURL::Clear(); 

    return 0;
}



