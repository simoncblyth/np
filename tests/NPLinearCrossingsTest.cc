// name=NPLinearCrossingsTest ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name
#include <vector>
#include <iostream>
#include "NP.hh"

void test_RINDEX()
{
    const char* keydir = getenv("OPTICKS_KEYDIR") ; 
    assert( keydir ); 

    NP* a = NP::Load(keydir, "GScintillatorLib/LS_ori/RINDEX.npy"); 
    a->pscale<double>(1e6, 0u); 
    a->pscale<double>(1.0, 1u); 

    double mn, mx ; 
    a->minmax(mn,mx); 
    std::cout
        <<  " mn " << std::fixed << std::setw(10) << std::setprecision(4) << mn 
        <<  " mx " << std::fixed << std::setw(10) << std::setprecision(4) << mx 
        << std::endl 
        ;

    unsigned nx = 100 ; 
    NP* bi = NP::Linspace<double>(mn, mx, nx ) ;  
    const double* biv = bi->cvalues<double>(); 

    for(unsigned i=0 ; i < nx ; i++)
    {
        double BetaInverse = biv[i] ;
        std::vector<double> crossings ; 
        a->linear_crossings( BetaInverse, crossings ); 

        std::cout 
            << " BetaInverse "
            <<  std::fixed << std::setw(10) << std::setprecision(4) << BetaInverse
            << " crossings " << crossings.size()
            ;

        for(unsigned i=0 ; i < crossings.size() ; i++)
            std::cout <<  std::fixed << std::setw(10) << std::setprecision(4) << crossings[i] ; 

        std::cout << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_RINDEX(); 
    return 0 ;
}

