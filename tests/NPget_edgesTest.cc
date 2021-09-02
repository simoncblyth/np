// name=NPget_edgesTest ; gcc $name.cc -std=c++11 -I.. -lstdc++  -o /tmp/$name && /tmp/$name

#include <iostream>
#include "NP.hh"

void test_get_edges()
{
    unsigned ni = 10 ; 
    NP* a = NP::Linspace<double>(1., 10., ni ); 

    double lo, hi ; 

    for(unsigned i=0 ; i <= ni ; i++) 
    {
        int ibin = i ;    
        a->get_edges<double>(lo,hi,0u,ibin);
        std::cout 
            << " ibin " << std::setw(4) << ibin
            << " lo " << std::setw(10) << std::fixed << std::setprecision(2) << lo 
            << " hi " << std::setw(10) << std::fixed << std::setprecision(2) << hi 
            << std::endl 
            ;
    }
}



int main(int argc, char** argv)
{
    test_get_edges(); 

    return 0 ; 
}
