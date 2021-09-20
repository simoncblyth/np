// name=s2integralTest ; gcc /tmp/s2integral.c -c -o /tmp/s2integral.o ;  gcc $name.cc /tmp/s2integral.o -I/tmp -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

/**
s2integralTest.cc
====================

Testing integration with generated C code for an Piecewise s2 integral exported 
from ana/piecewise.py using sympy codegen. 

Currently are restricted to a fixed BetaInverse (using 1.55) 
because the sympy integration does not work when it is left as a symbol.  
That limits usefulness. 

**/

#include "NP.hh"

//#include "s2integral.h"
extern "C" double s2integral(double e);

int main(int argc, char** argv)
{
    unsigned ni = 1000 ; 
    NP* ee = NP::Linspace<double>(1.55, 15.5, ni) ; 

    NP* s2i = NP::Make<double>( ni, 2 ) ; 
    double* s2i_v = s2i->values<double>(); 

    for(unsigned i=0 ; i < ni ; i++ )
    {
        double e =  ee->get<double>(i) ; 
        double s2i = s2integral(e) ; 

        s2i_v[2*i+0 ]= e ; 
        s2i_v[2*i+1 ]= s2i ; 
        
        std::cout 
            << " e " << std::setw(10) << std::fixed << std::setprecision(4) << e 
            << " s2i " << std::setw(10) << std::fixed << std::setprecision(4) << s2i
            << std::endl 
            ; 
    }
    s2i->save("/tmp/s2integralTest.npy"); 

    return 0 ; 

}
