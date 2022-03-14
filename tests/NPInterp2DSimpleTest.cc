// ./NPInterp2DSimpleTest.sh

#include "NP.hh"

/**

The interpolation formulas used by CUDA textures are documented.

* https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#linear-filtering

::

    J.2. Linear Filtering
    In this filtering mode, which is only available for floating-point textures, the value returned by the texture fetch is

    tex(x)=(1−α)T[i]+αT[i+1] for a one-dimensional texture,

    tex(x,y)=(1−α)(1−β)T[i,j]+α(1−β)T[i+1,j]+(1−α)βT[i,j+1]+αβT[i+1,j+1] for a two-dimensional texture,

    tex(x,y,z) =
    (1−α)(1−β)(1−γ)T[i,j,k]+α(1−β)(1−γ)T[i+1,j,k]+
    (1−α)β(1−γ)T[i,j+1,k]+αβ(1−γ)T[i+1,j+1,k]+
    (1−α)(1−β)γT[i,j,k+1]+α(1−β)γT[i+1,j,k+1]+
    (1−α)βγT[i,j+1,k+1]+αβγT[i+1,j+1,k+1]

    for a three-dimensional texture,
    where:

    i=floor(xB), α=frac(xB), xB=x-0.5,
    j=floor(yB), β=frac(yB), yB=y-0.5,
    k=floor(zB), γ=frac(zB), zB= z-0.5,
    α, β, and γ are stored in 9-bit fixed point format with 8 bits of fractional value (so 1.0 is exactly represented).


About the reduced precision

* https://www.reedbeta.com/blog/texture-gathers-and-coordinate-precision/



**/

template <typename T>
T interp2D( const NP* a , T x, T y, bool dump )
{
    int ndim = a->shape.size();
    assert(ndim == 2 );
    int ni = a->shape[ndim-2];
    int nj = a->shape[ndim-1];

    const T* aa = a->cvalues<T>();  

    T xB = x - T(0.5) ; 
    T yB = y - T(0.5) ; 

    // decompose floating point value into integral and fractional parts 
    T xBint ; 
    T xBfra = std::modf(xB, &xBint);
    int j = int(xBint) ; 

    T yBint ; 
    T yBfra = std::modf(yB, &yBint);
    int i = int(yBint) ; 

    const T one(1.); 

    if(dump)
    {
        std::cout 
            << " y " << std::fixed << std::setw(10) << std::setprecision(4) << y 
            << " yB " << std::fixed << std::setw(10) << std::setprecision(4) << yB 
            << " yBint " << std::fixed << std::setw(10) << std::setprecision(4) << yBint
            << " yBfra " << std::fixed << std::setw(10) << std::setprecision(4) << yBfra
            << " i " << std::setw(4) << i  
            << std::endl 
            ;

        std::cout 
            << " x " << std::fixed << std::setw(10) << std::setprecision(4) << x 
            << " xB " << std::fixed << std::setw(10) << std::setprecision(4) << xB 
            << " xBint " << std::fixed << std::setw(10) << std::setprecision(4) << xBint
            << " xBfra " << std::fixed << std::setw(10) << std::setprecision(4) << xBfra
            << " j " << std::setw(4) << j  
            << std::endl 
            ;
    }

    assert( i < ni && i > -1 ); 
    assert( j < nj && j > -1 ); 

    // (i,j) => (y,x) 

    T v00 = aa[(i+0)*nj+(j+0)];  T v01 = aa[(i+0)*nj+(j+1)];   // v01 at j+1 (at large x than v00)    
    T v10 = aa[(i+1)*nj+(j+0)];  T v11 = aa[(i+1)*nj+(j+1)];     
    // v10 is i+1  

    // tex(x,y)=(1−α)(1−β)T[i,j]+α(1−β)T[i+1,j]+(1−α)βT[i,j+1]+αβT[i+1,j+1] 
    // hmm does this need a y-flip ?

    T z =  
            (one - xBfra)*(one - yBfra)*v00 +   
                    xBfra*(one - yBfra)*v01 +   
                    (one - xBfra)*yBfra*v10 +   
                            xBfra*yBfra*v11  ; 

    if(dump)
    {
        std::cout 
            << " z " << std::fixed << std::setw(10) << std::setprecision(4) << z
            << std::endl 
            ;
    }
 
    return z ; 
} 



/**

     i = 0 corresponds to the top row     
     (i,j) = (0,0) corresponds to top left corner

    * 1st dimension i spans y starting from top
    * 2nd dimension j spans x starting from left

     
           (i,j)
           (0,0)         (0,1)       (0,2)
            1.0          2.0          3.0
             +------------+------------+
             |            |            | 
             |            |            | 
             |            |            |    
             |            |            |
             |            |            |
             +------------+------------+ 
           (1,0)         (1,1)        (1,2)
            4.0          5.0           6.0  
             |            |            |
             |            |            |
             |            |            |
             |            |            |
             +------------+------------+ 
            (2,0)        (2,1)        (2,2)
             7.0         8.0           9.0
        
          Y
          |
          |
          +----> X

**/



struct NPInterp2DSimpleTest
{
    static const char* FOLD ; 
    static NP* Create(); 
    static NP* Interpolate(const NP* a, int scale); 
    static void test_0(); 
    static void test_1(); 
};


const char* NPInterp2DSimpleTest::FOLD = "/tmp/NPInterp2DSimpleTest" ; 

NP* NPInterp2DSimpleTest::Create()
{
    int ni = 3 ; 
    int nj = 3 ; 
    NP* a = NP::Make<double>(ni,nj) ;  
    double* aa = a->values<double>(); 

    int i ; 
    i = 0 ; aa[i*nj+0 ] =  1. ;  aa[i*nj+1 ] =  2. ;  aa[i*nj+2 ] = 3. ;  
    i = 1 ; aa[i*nj+0 ] =  4. ;  aa[i*nj+1 ] =  5. ;  aa[i*nj+2 ] = 6. ; 
    i = 2 ; aa[i*nj+0 ] =  7. ;  aa[i*nj+1 ] =  8. ;  aa[i*nj+2 ] = 9. ; 

    return a ; 
}

NP* NPInterp2DSimpleTest::Interpolate( const NP* a, int scale )
{
    assert( a->shape.size() == 2 ); 

    int ni_a = a->shape[0] ; 
    int nj_a = a->shape[0] ; 
    int ni_b = ni_a*scale ; 
    int nj_b = nj_a*scale ; 

    NP* b = NP::Make<double>(  ni_b, nj_b ); 
    double* bb = b->values<double>(); 
    for(int i=0 ; i < ni_b ; i++) 
    {
        double y = double(ni_a-1)*double(i)/double(ni_b-1)  ; 
        for(int j=0 ; j < nj_b ; j++) 
        {
            double x =  double(nj_a-1)*double(j)/double(nj_b-1) ; 
            bb[ i*nj_b + j ] = interp2D<double>( a, x, y, false ); 
        }
    }

    a->save(FOLD, "a.npy"); 
    b->save(FOLD, "b.npy"); 

    return b ; 
}

void NPInterp2DSimpleTest::test_0()
{
    const NP* a = Create(); 
    double x = 2.5 ; 
    double y = 0.5 ; 
    double z = interp2D<double>( a, x, y, true ); 
}

void NPInterp2DSimpleTest::test_1()
{
    NP* a = Create(); 
    NP* b = Interpolate(a, 2); 
    assert(b); 
}

int main(int argc, char** argv)
{
    //NPInterp2DSimpleTest::test_0(); 
    NPInterp2DSimpleTest::test_1(); 
    return 0 ; 
}


