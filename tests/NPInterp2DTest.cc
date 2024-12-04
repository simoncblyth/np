// ~/np/tests/NPInterp2DTest.sh

#include "NP.hh"

template <typename T>
struct NPInterp2DTest
{
    static T Ordinate(int idx, int nidx, T a0, T a1 ); 

    std::function<T(T,T)> fn ; 

    int ni ; 
    int nj ; 

    T x0 ; 
    T x1 ;

    T y0 ; 
    T y1 ;

    NP* a ;     // function evaluated at coarser coordinates
    T* aa ; 

    NP* b ;     // function interpolated values at all coordinates 
    T* bb ; 

    NP* c ;     // function evaluated at all coordinates (ground truth)
    T* cc ; 

    NPInterp2DTest(  std::function<T(T,T)> fn_, 
                     int ni, T y0, T y1, 
                     int nj, T x0, T x1 );

    void init(); 
    void interp(); 

    T y_(int i) const ;   // 1st dimension y 
    T x_(int j) const ; 
    T z_(int i, int j) const ; 

    void dump() const ; 
    void save() const ; 
}; 

template <typename T>
NPInterp2DTest<T>::NPInterp2DTest( std::function<T(T,T)> fn_, int ni_, T y0_, T y1_, int nj_, T x0_, T x1_ )
    :
    fn(fn_),
    ni(ni_),
    y0(y0_),
    y1(y1_),
    nj(nj_),
    x0(x0_),
    x1(x1_),
    a(NP::Make<T>(ni, nj )), 
    aa(a->values<T>()),
    b(NP::Make<T>(ni, nj )),     // b and c : were 2*ni, 2*nj but that giving OOR in NP::interp2D
    bb(b->values<T>()),
    c(NP::Make<T>(ni, nj )), 
    cc(c->values<T>())
{
    init(); 
}

/**
NPInterp2DTest::Ordinate
------------------------


**/
template <typename T> T NPInterp2DTest<T>::Ordinate(int idx, int nidx, T a0, T a1 ) 
{ 
    T av(0); 
    if(      idx == 0 )         av = a0 ; 
    else if( idx == nidx - 1  ) av = a1 ; 
    else if( idx > 0 && idx < nidx - 1 ) av = a0 + (a1-a0)*T(idx)/T(nidx-1) ; 
    else  assert(0) ;    
    return av ; 
} // static
template <typename T> T NPInterp2DTest<T>::y_(int i) const { return Ordinate( i, ni, y0, y1) ; }
template <typename T> T NPInterp2DTest<T>::x_(int j) const { return Ordinate( j, nj, x0, x1) ; }
template <typename T> T NPInterp2DTest<T>::z_(int i, int j) const { return fn(x_(j), y_(i) ) ; }

// fill *a* with values at every coordinate 
template <typename T> void NPInterp2DTest<T>::init()
{
    for(int i=0 ; i < ni ; i++) for(int j=0 ; j < nj ; j++) aa[i*nj + j] = z_(i, j) ; 
} 

template <typename T> void NPInterp2DTest<T>::interp()
{
    int b_ni = b->shape[0] ; 
    int b_nj = b->shape[1] ; 

    int c_ni = c->shape[0] ; 
    int c_nj = c->shape[1] ; 

    assert( c_ni == b_ni ); 
    assert( c_nj == b_nj ); 

    // caution (i,j) <=> (y,x)
    for(int i=0 ; i < b_ni ; i++) for(int j=0 ; j < b_nj ; j++) 
    {
        T y = Ordinate(i, b_ni, y0, y1 ); 
        T x = Ordinate(j, b_nj, x0, x1 ); 
        // x and y needs to be common currency between the two resolutions
        // HMM: but that means need some range metadata ? 

        bb[i*b_nj + j] = a->interp2D( x, y ) ; 
        cc[i*b_nj + j] = fn(x, y ); 

    }
}


template <typename T> void NPInterp2DTest<T>::dump() const 
{
    std::cout 
        << " a " << ( a ? a->desc() : "-" )
        << std::endl  
        << " b " << ( b ? b->desc() : "-" )
        << std::endl
        << " c " << ( c ? c->desc() : "-" )
        << std::endl
        ;
}

template <typename T>
void NPInterp2DTest<T>::save() const 
{
    if(a) a->save("$FOLD/a.npy"); 
    if(b) b->save("$FOLD/b.npy"); 
    if(c) c->save("$FOLD/c.npy"); 
} 

double func( double x, double y )
{
    //return  sqrt( (x-500.)*(x-500.) + (y-500.)*(y-500.) ) ; 
    return  x + y ; 
    //return  x  ; 
    //return  y  ; 
}

int main(int argc, char** argv)
{
    /*
    int y_ni = 768 ; 
    double y0 = 0. ; 
    double y1 = 1000. ; 

    int x_nj = 1024 ; 
    double x0 = 0. ; 
    double x1 = 1000. ; 
    */ 
    

    //                             y_ni  y0   y1   x_nj  x0  x1
    //NPInterp2DTest<double> t(func, 768, 0., 1000., 1024, 0., 1000. )  //  gives out of range in NP::interp2D 
    NPInterp2DTest<double> t(func, 768, 0., 767., 1024, 0., 1023. );  // stays in range : and a,b,c all look as expected
    //NPInterp2DTest<double> t(func, 768, 0., 768., 1024, 0., 1024. );    // stays in range : and b is messed up : uniform 

    t.interp(); 
    t.dump(); 
    t.save(); 

    return 0 ;
}


