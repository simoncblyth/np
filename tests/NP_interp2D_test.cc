#include "NP.hh"


template<typename T>
struct NP_interp2D_test
{
    static int flat(); 
    static int main(); 
}; 

template<typename T>
int NP_interp2D_test<T>::flat()
{
    T flat = T(1.) ; 

    int ni = 10 ; 
    int nj = 10 ; 
 
    NP* a = NP::Make<T>(ni, nj) ; 
    float* aa = a->values<T>() ; 
 
    for(int i=0 ; i < ni ; i++) 
    for(int j=0 ; j < nj ; j++) 
    aa[i*nj+j] = flat ; 

    int fac = 10 ; 

    T dmax = T(0.) ; 

    // NB: the i_dim = 10, so the i range need to be [0, 90] when the frac = 10.
    // thus the  i should range from 0 to (ni-1)*frac
    //
    // And we need to convert i to x : [0, (ni-1)*frac] --> [ 0.5,  (i_dim-1)+0.5 ]
    for(int i=0 ; i < (ni-1)*fac ; i++)
    for(int j=0 ; j < (nj-1)*fac ; j++) 
    {
        T x = T(i)/T(fac)+T(0.5) ; 
        T y = T(j)/T(fac)+T(0.5) ; 
        T v = a->interp2D( x, y ) ; 
        T d = std::abs( v - flat ) ; 

        std::cout 
           << " i " << std::setw(2) << i 
           << " j " << std::setw(2) << j 
           << " x " << std::fixed << std::setw(10) << std::setprecision(3) << x  
           << " y " << std::fixed << std::setw(10) << std::setprecision(3) << y
           << " d " << std::fixed << std::setw(10) << std::setprecision(3) << d
           << std::endl 
           ;

        if(d > dmax) dmax = d  ; 
    }


    T dmax_limit = sizeof(T) == 4 ? 1e-5 : 1e-8 ; 
    std::cout 
        << " dmax : " << dmax 
        << " dmax_limit : " << dmax_limit 
        << std::endl
        ; 

    assert( dmax < dmax_limit ); 


    return 0 ; 
}

template<typename T>
int NP_interp2D_test<T>::main()
{
    int rc = 0 ; 
    rc += flat(); 
    return rc ; 
}


int main(int argc, char** argv)
{
    return NP_interp2D_test<float>::main(); 
}
