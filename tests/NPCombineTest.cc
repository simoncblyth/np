// ./NPCombineTest.sh

#include <vector>
#include <iostream>
#include "NP.hh"

template <typename T>
struct NPCombineTest
{
    static const char* FOLD ; 
    static NP* MakeSrc(unsigned ni, unsigned nj) ; 


    const std::vector<const NP*>& aa ; 
    int na ; 
    NP*  c ;  

    unsigned ndom ; 
    NP* dom ; 
    T* dd ; 

    NP* r ; 
    T* rr ; 

    NPCombineTest(const std::vector<const NP*>& aa_, T x0, T x1, unsigned ndom);
    void dump() const ; 
    void scan(); 
    void save(); 

}; 

template <typename T>
const char* NPCombineTest<T>::FOLD = "/tmp/NPCombineTest" ; 


template <typename T>
NPCombineTest<T>::NPCombineTest(const std::vector<const NP*>& aa_, T x0, T x1, unsigned ndom_)
    :
    aa(aa_),
    na(aa.size()),
    c(NP::Combine(aa)),
    ndom(ndom_), 
    dom(NP::Linspace(x0,x1,ndom)),
    dd(dom->values<T>()),
    r(NP::Make<T>(aa.size(), ndom)),     
    rr(r->values<T>())
{
    dump(); 
    scan(); 
    save(); 
}

template <typename T>
void NPCombineTest<T>::dump() const 
{
    std::cout 
        << " na " << na 
        << " ndom " << ndom 
        << " dom " << ( dom ? dom->desc() : "-" )
        << " c " << ( c ? c->desc() : "-" )
        << " r " << ( r ? r->desc() : "-" )
        << std::endl
        ;

/*
    for(unsigned i=0 ; i < na ; i++) 
    {
        std::cout 
            << " i " << std::setw(3) << i 
            << std::endl 
            ;
 
        for( unsigned j=0 ; j < ndom ; j++)
        {
            std::cout 
                << " j " << std::setw(3) << j 
                << " rr[ndom*i+j] " << std::setw(10) << std::setprecision(4) << std::fixed << rr[ndom*i+j] 
                << std::endl 
                ; 
        }
    }
*/


}

/**
NPCombineTest<T>::scan
-----------------------

CAUTION : be explicit with the type, or risk scrambling the array content.

**/

template <typename T>
void NPCombineTest<T>::scan() 
{
    for(unsigned i=0 ; i < na ; i++ )
    {
        const NP* a = aa[i] ; 
        std::cout << "NPCombineTest::scan " << a->desc() << std::endl ; 

        for(unsigned j=0 ; j < ndom ; j++)
        {
            T x = dd[j] ; 
            T y0 = a->interp<T>(x) ;     // non-combined interpolation 
            //T y1 = c->interp<T>(i, x) ;  // interpolation from the combined array 
            T y1 = c->combined_interp_3<T>(i, x) ;  // interpolation from the combined array 
            assert( y0 == y1 ); 

/*
            std::cout 
                << "NPCombineTest::scan"
                << " i " << std::setw(3) << i 
                << " j " << std::setw(3) << j 
                << " x " << std::setw(10) << std::setprecision(4) << std::fixed << x 
                << " y0 " << std::setw(10) << std::setprecision(4) << std::fixed << y0
                << " y1 " << std::setw(10) << std::setprecision(4) << std::fixed << y1
                << std::endl
                ;
*/

            rr[ndom*i+j] = y1 ; 
        }
    }
}

template <typename T>
NP* NPCombineTest<T>::MakeSrc(unsigned ni, unsigned nj)   // static 
{
    NP* a = NP::Make<T>( ni, nj ); 
    T* vv = a->values<T>(); 
    for(unsigned i=0 ; i < ni ; i++)
    {
        for( unsigned j=0 ; j < nj ; j++)
        {
            switch(j)
            { 
                case 0:    vv[i*nj+j] = T(i)         ; break ; 
                case 1:    vv[i*nj+j] = T(10*i)      ; break ; 
                case 2:    vv[i*nj+j] = T(100*i)     ; break ; 
                default:   vv[i*nj+j] = T(1000*i)    ; break ; 
            }
        }
    }
    a->dump(); 
    return a ; 
}

template <typename T>
void NPCombineTest<T>::save() 
{
    dom->save(FOLD, "dom.npy"); 
    c->save(FOLD, "com.npy"); 
    r->save(FOLD, "scan.npy");
} 


void test_simple()
{
    // make 2D pshape property arrays 

    NP* a = NPCombineTest<float>::MakeSrc(7,2); 
    NP* b = NPCombineTest<float>::MakeSrc(6,2); 
    NP* c = NPCombineTest<float>::MakeSrc(5,2); 


    // scaling and offsets to make them distinct 

    unsigned col1 = 1u ; 
    a->pscale_add<float>(1.0f,  10.f, col1); 
    b->pscale_add<float>(1.05f, 20.f, col1); 
    c->pscale_add<float>(0.95f, 30.f, col1); 


    // change domain too, to demonstrate that there is 
    // no same domain requirement here 
     
    unsigned col0 = 0u ; 
    a->pscale_add<float>(1.0f,  0.5f, col0); 

    std::vector<const NP*> aa = { a, b, c } ; 

    NPCombineTest<float> t(aa, -1.f, 8.f, 91); 
}

void test_RINDEX(unsigned ndom, bool narrow)
{
    const char* keydir = getenv("OPTICKS_KEYDIR") ; 
    assert( keydir ); 

    NP* a = NP::Load(keydir, "GScintillatorLib/LS_ori/RINDEX.npy"); 
    a->pscale<double>(1e6, 0u); 
    a->pscale<double>(1.0, 1u); 

    NP* b = NP::Load(keydir, "GScintillatorLib/LS_ori/RINDEX.npy"); 
    b->pscale<double>(1e6, 0u); 
    b->pscale<double>(1.05, 1u); 

    NP* c = NP::Load(keydir, "GScintillatorLib/LS_ori/RINDEX.npy"); 
    c->pscale<double>(1e6, 0u); 
    c->pscale<double>(0.95, 1u); 

    if( narrow == false )
    { 
        std::vector<const NP*> aa = { a, b, c } ; 
        NPCombineTest<double> t(aa, 1., 16., ndom ); 
    }
    else
    {
        NP* an = NP::MakeNarrow( a ); 
        NP* bn = NP::MakeNarrow( b ); 
        NP* cn = NP::MakeNarrow( c ); 
        std::vector<const NP*> aa = { an, bn, cn } ; 
        NPCombineTest<float> t(aa, 1.f, 16.f, ndom ); 
    }
}



int main(int argc, char** argv)
{
    test_simple(); 
    //test_RINDEX(1000, true); 
    return 0 ;
}

