// ~/np/tests/NP_minmax2D_reshaped_test.sh

#include <array>
#include "NP.hh"

std::array<double, 20> src {{ 
     1.,   10., 
     2.,   20., 
     3.,   30., 
     4.,   40., 
     5.,   50.,

     -100., -1000., 
     -200., -2000., 
     -300., -3000., 
     -400., -4000., 
     -500., -5000.,

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

    double* aa = a->values<double>(); 
    for(int i=0 ; i < a->size ; i++) aa[i] += 100. ; 

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


void test_minmax2D_reshaped_striding()
{
    std::cout << "test_minmax2D_reshaped_striding" << std::endl ;

    std::array<double, 96> arr {{ 
        
         1., 1., 1., 1., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 

         2., 2., 2., 2., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 

         3., 3., 3., 3., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0.,

        -1., -1., -1., -1., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 

        -2., -2., -2., -2., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 

        -3., -3., -3., -3., 
         0., 0., 0., 0., 
         0., 0., 0., 0., 
         0., 0., 0., 0.,
 }} ; 


    NP* a = NP::Make<double>(2, 3, 4, 4);  
    a->read( arr.data() ); 

    int ni = a->shape[0] ; 
    int nj = a->shape[1] ; 
    int nk = a->shape[2] ; 
    int nl = a->shape[3] ; 

    double* aa = a->values<double>(); 

    for(int i=0 ; i < ni ; i++)
    for(int j=0 ; j < nj ; j++)
    for(int k=0 ; k < nk ; k++)
    for(int l=0 ; l < nl ; l++)
    {
        int idx = i*nj*nk*nl + j*nk*nl + k*nl + l ; 
        if( k == 0 ) aa[idx] += 1000. ; 
    }


    static const int N = 4 ; 

    double mn[N] = {} ; 
    double mx[N] = {} ; 

    std::cout << "bef a.sstr " << a->sstr() << std::endl ; 

    int item_stride = 4 ;  // THIS IS A DIFFERENT 4 TO N 
    int item_offset = 0 ; 

    a->minmax2D_reshaped<N, double>(mn, mx, item_stride, item_offset ) ; 

    for(int j=0 ; j < N ; j++) std::cout 
        << " mn[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mn[j] 
        << " mx[" << j <<" ] " << std::setw(10) << std::fixed << std::setprecision(4) << mx[j]
        << std::endl
        ; 

    std::cout << "aft a.sstr " << a->sstr() << std::endl ; 
}






int main(int argc, char** argv)
{
    //test_minmax2D(); 
    //test_minmax2D_reshaped(); 
    test_minmax2D_reshaped_striding(); 

    return 0 ; 
}
