// gcc NPFutureTest.cc -std=c++11  -I.. -pthread -lstdc++ -o /tmp/NPFutureTest && /tmp/NPFutureTest

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include "NP.hh"

NP* make_arr_0()
{
    std::cout << "make_arr_0" << std::endl ; 
    return NP::MakeDemo("<f4", 10, 4); 
}

NP* make_arr_1(const char* dtype)
{
    std::cout << "make_arr_1" << std::endl ; 
    return NP::MakeDemo(dtype, 10, 4); 
}

NP* make_arr_2(const char* dtype, int ni, int nj)
{
    std::cout << "make_arr_2" << std::endl ; 
    return NP::MakeDemo(dtype, ni, nj); 
}

NP* make_arr_3(const char* dtype, int ni, int nj, int nk, int nl, int nm )
{
    std::cout << "make_arr_3" << std::endl ; 
    return NP::MakeDemo(dtype, ni, nj, nk, nl, nm ); 
}





void make_future_arrays()
{
    std::future<NP*> future_a = std::async(std::launch::async, make_arr_0 );
    std::future<NP*> future_b = std::async(std::launch::async, make_arr_1, "<i4" );
    std::future<NP*> future_c = std::async(std::launch::async, make_arr_2, "<i4", 4, 4 );
    std::future<NP*> future_d = std::async(std::launch::async, make_arr_3, "<i4", 4, 4, -1, -1, -1 );

    NP* a = future_a.get() ; a->dump(); 
    NP* b = future_b.get() ; b->dump(); 
    NP* c = future_c.get() ; c->dump(); 
    NP* d = future_d.get() ; d->dump(); 
}

int main(int argc, char** argv)
{
    std::vector<std::future<NP*>> v ;    
    v.push_back( std::async(std::launch::async, make_arr_0 ) );
    v.push_back( std::async(std::launch::async, make_arr_1, "<i4" ) );
    v.push_back( std::async(std::launch::async, make_arr_2, "<i4", 4, 4 ) );
    v.push_back( std::async(std::launch::async, make_arr_3, "<i4", 4, 4, -1, -1, -1 ) ); 

    for(unsigned i=0 ; i < v.size() ; i++)
    {
        NP* a = v[i].get() ; 
        a->dump();  
    }
    return 0 ; 
}

