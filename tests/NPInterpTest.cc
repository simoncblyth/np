// ./NPInterpTest.sh

#include <vector>
#include <iostream>
#include "NP.hh"

template <typename T>
struct NPInterpTest
{
    static const char* FOLD ; 
    static NP* MakeSrc() ; 
    static NP* MakeSrc(const std::vector<T>& vals) ; 

    const NP* a ;
    unsigned na ; 
    const T* aa ; 
    const T amn ; 
    const T amx ; 
    const T x0 ; 
    const T x1 ; 
    const T dx ; 

    unsigned nb ; 
    NP* b ; 
    T* bb ; 

    NPInterpTest(const NP* a, unsigned nstep);
    void dump() const ; 
    void scan(); 
    void save(); 

}; 

template <typename T>
const char* NPInterpTest<T>::FOLD = "/tmp/NPInterpTest" ; 


template <typename T>
NPInterpTest<T>::NPInterpTest(const NP* a_, unsigned nstep)
    :
    a(a_),
    na(a->shape[0]),
    aa(a->cvalues<T>()),
    amn(aa[2*0+0]),       // assumes input array is 2d with 2nd dimension 2, ie of shape (n,2)  
    amx(aa[2*(na-1)+0]),
    x0(amn - (amx-amn)*0.1f),  // picking domain range 
    x1(amx + (amx-amn)*0.1f),  
    dx((amx-amn)/float(nstep)),
    nb(NP::NumSteps(x0,x1,dx)),
    b(NP::Make<T>(nb,2)),     
    bb(b->values<T>())
{
    dump(); 
    scan(); 
    save(); 
}

template <typename T>
void NPInterpTest<T>::dump() const 
{
    std::cout 
        << " na " << na 
        << " a " << ( a ? a->desc() : "-" )
        << std::endl  
        << " amn " << std::setw(10) << std::setprecision(4) << std::fixed << amn
        << " amx " << std::setw(10) << std::setprecision(4) << std::fixed << amx
        << std::endl  
        << " x0 " << std::setw(10) << std::setprecision(4) << std::fixed << x0
        << " x1 " << std::setw(10) << std::setprecision(4) << std::fixed << x1
        << " dx " << std::setw(10) << std::setprecision(4) << std::fixed << dx
        << std::endl
        << " nb " << nb 
        << " b " << ( b ? b->desc() : "-" )
        << std::endl
        ;
    for(unsigned i=0 ; i < na ; i++) 
        std::cout 
            << " i " << std::setw(3) << i 
            << " aa[2*i+0] " << std::setw(10) << std::setprecision(4) << std::fixed << aa[2*i+0] 
            << " aa[2*i+1] " << std::setw(10) << std::setprecision(4) << std::fixed << aa[2*i+1]
            << std::endl 
            ; 

     a->pdump<T>("a.dump.pdump"); 

}

/**
NPInterpTest<T>::scan
-----------------------

CAUTION : be explicit with the type, or risk scrambling the array content.

**/

template <typename T>
void NPInterpTest<T>::scan() 
{
    unsigned ib = 0 ; 
    for(T x=x0 ; x <= x1 ; x+=dx )
    {
        T y = a->interp<T>(x) ;    

        std::cout 
            << "NPInterpTest::scan"
            << " ib " << std::setw(3) << ib 
            << " x " << std::setw(10) << std::setprecision(4) << std::fixed << x 
            << " y " << std::setw(10) << std::setprecision(4) << std::fixed << y
            << std::endl
            ;

        assert( ib < nb );  
        bb[2*ib+0] = x ; 
        bb[2*ib+1] = y ;
        ib += 1 ; 
    }
}

template <typename T>
void NPInterpTest<T>::save() 
{
    a->save(FOLD, "src.npy"); 
    b->save(FOLD, "dst.npy");
} 

template <typename T>
NP* NPInterpTest<T>::MakeSrc()   // static 
{
    std::vector<T> vals = { 
        T(0.), T(10.), 
        T(1.), T(20.), 
        T(2.), T(30.)
     };  
    return MakeSrc(vals);
}

template <typename T>
NP* NPInterpTest<T>::MakeSrc(const std::vector<T>& vals)  // static 
{
    NP* a = NP::Make<T>( vals.size()/2, 2 ); 
    float* vv = a->values<float>(); 
    for( unsigned v=0 ; v < a->num_values() ; v++ ) vv[v] = vals[v] ; 
    a->dump(); 
    return a ; 
} 

void test_simple()
{
    NP* a = NPInterpTest<float>::MakeSrc(); 
    NPInterpTest<float> t(a, 50); 
}

void test_RINDEX(unsigned nstep)
{
    const char* keydir = getenv("OPTICKS_KEYDIR") ; 
    assert( keydir ); 
    NP* a = NP::Load(keydir, "GScintillatorLib/LS_ori/RINDEX.npy"); 
    a->pscale<double>(1e6, 0u); 
    a->pdump<double>("test_RINDEX.pdump"); 

    NPInterpTest<double> t(a, nstep); 
}

int main(int argc, char** argv)
{
    test_simple(); 
    test_RINDEX(1000); 
    return 0 ;
}


