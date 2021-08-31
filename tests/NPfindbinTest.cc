// name=NPfindbinTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <iostream>
#include "NP.hh"

void test_pfindbin()
{
    NP* bins = NP::Linspace<double>( 1., 10., 10 ); 
    NP* fine = NP::Linspace<double>( 0., 11., 111 ); 

    const double* ff = fine->cvalues<double>(); 

    unsigned column = 0u ; 
    for(unsigned i=0 ; i < fine->shape[0] ; i++ )
    {
         double f = ff[i] ; 
         int ibin = bins->pfindbin<double>( f, column ); 

         std::cout 
             << " i " << std::setw(5) << i
             << " f " << std::setw(10) << std::fixed << std::setprecision(4) << f 
             << " ibin " <<  std::setw(5) << ibin
             << std::endl 
             ;
    }
}


int main(int argc, char** argv)
{
    test_pfindbin(); 
    return 0 ;
}

