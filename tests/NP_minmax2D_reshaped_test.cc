// ~/np/tests/NP_minmax2D_reshaped_test.sh

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




void test_minmax2D()
{
    std::cout << "test_minmax2D" << std::endl ;
    NP* a = NP::Make<double>(10, 2);  
    a->read( src.data() ); 

    double mn[2] = {} ; 
    double mx[2] = {} ; 

    a->minmax2D<double>(mn,mx) ; 

    for(int j=0 ; j < 2 ; j++) std::cout 
        << " mn[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mn[j] 
        << " mx[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mx[j]
        << std::endl
        ; 

}

void test_minmax2D_reshaped()
{
    std::cout << "test_minmax2D_reshaped" << std::endl ;
    NP* a = NP::Make<double>(2, 5, 2);  
    a->read( src.data() ); 

    double mn[2] = {} ; 
    double mx[2] = {} ; 

    std::cout << "bef a.sstr " << a->sstr() << std::endl ; 

    a->minmax2D_reshaped<2, double>(mn,mx) ; 

    for(int j=0 ; j < 2 ; j++) std::cout 
        << " mn[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mn[j] 
        << " mx[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mx[j]
        << std::endl
        ; 

    std::cout << "aft a.sstr " << a->sstr() << std::endl ; 
}

int main(int argc, char** argv)
{
    test_minmax2D(); 
    test_minmax2D_reshaped(); 
    return 0 ; 
}
