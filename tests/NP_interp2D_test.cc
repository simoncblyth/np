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

    for(int i=0 ; i < ni*fac ; i++)
    for(int j=0 ; j < nj*fac ; j++) 
    {
        T x = T(i)/T(fac) ; 
        T y = T(j)/T(fac) ; 
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
