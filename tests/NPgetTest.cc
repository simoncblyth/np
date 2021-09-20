// name=NPgetTest ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name

#include <array>
#include "NP.hh"

std::array<double, 20> src {{ 
     1.,   10., 
     2.,   20., 
     3.,   30., 
     4.,   40., 
     5.,   50.,

     100., 1000., 
     200., 2000., 
     300., 3000., 
     400., 4000., 
     500., 5000.,

}} ; 


void test_1d()
{
    std::cout << "test_1d" << std::endl ;
    NP* a = NP::Make<double>(20);  
    a->read( src.data() ); 

    for(unsigned i=0 ; i < a->shape[0] ; i++)
    {
        std::cout 
            << " i " << std::setw(3) << i 
            << " a[i] " << std::setw(10) << a->get<double>(i) 
            << std::endl
            ; 
    }
}

void test_2d()
{
    std::cout << "test_2d" << std::endl ;
    NP* a = NP::Make<double>(10, 2);  
    a->read( src.data() ); 

    for(unsigned i=0 ; i < a->shape[0] ; i++)
    {
        std::cout 
            << std::setw(10) << a->get<double>(i, 0) 
            << std::setw(10) << a->get<double>(i, 1) 
            << std::endl
            ; 
    }
}

void test_3d()
{
    std::cout << "test_3d" << std::endl ;
    NP* a = NP::Make<double>(2, 5, 2);  
    a->read( src.data() ); 

    for(unsigned i=0 ; i < a->shape[0] ; i++)
    { 
        std::cout << " i " << std::setw(5) << i << std::endl ; 
        for(unsigned j=0 ; j < a->shape[1] ; j++)
        {
            std::cout 
                << " j " << std::setw(5) << j 
                << " a[i,j,0] " << std::setw(10) << a->get<double>(i, j, 0) 
                << " a[i,j,1] " << std::setw(10) << a->get<double>(i, j, 1) 
                << std::endl
                ; 
        }
   }
}

int main(int argc, char** argv)
{
    test_1d(); 
    test_2d(); 
    test_3d(); 
    return 0 ; 
}
