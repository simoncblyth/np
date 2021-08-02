// name=NPTrapzTest ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name
#include <vector>
#include <iostream>
#include "NP.hh"

void test_trapz()
{
    unsigned ni = 10 ; 
    NP* prop = NP::Make<double>(ni,2) ;  
    double* vv = prop->values<double>(); 
    for(unsigned i=0 ; i < ni ; i++)
    {
        vv[2*i+0] = double(i) ; 
        vv[2*i+1] = double(i*i) ; 
    }

    double integral = prop->trapz<double>(); 
    std::cout 
        << " NP::trapz " 
        << std::fixed << std::setw(10) << std::setprecision(5) << integral 
        << std::endl 
       ;

   double x_integral = 244.5 ; 
   assert( integral == x_integral ); 

}

/**

In [11]: a = np.arange(0,10, dtype=np.float64)                                                                                                                                                   
In [12]: a                                                                                                                                                                                       
Out[12]: array([0., 1., 2., 3., 4., 5., 6., 7., 8., 9.])

In [14]: np.trapz( a*a, a )                                                                                                                                                                      
Out[14]: 244.5

**/

int main(int argc, char** argv)
{
    test_trapz(); 
    return 0 ;
}

