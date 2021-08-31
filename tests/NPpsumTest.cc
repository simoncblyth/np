// name=NPpsumTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <iostream>
#include "NP.hh"

void test_psum()
{
    NP* vals = NP::Linspace<double>( 1., 10., 10 ); 
    double sum = vals->psum<double>(0u) ; 

    std::cout 
        << " vals " << vals->desc()
        << " sum " << std::setw(10) << std::fixed << std::setprecision(4) << sum
        << std::endl 
        ;
}
/**
In [11]: np.linspace(1, 10, 10).sum()
Out[11]: 55.0
**/

int main(int argc, char** argv)
{
    test_psum(); 
    return 0 ;
}

