// ~/np/tests/NPCombineTest.sh

#include "NP.hh"

template <typename T>
struct NPCombineTest
{
    static NP* MakeSrc(unsigned ni, unsigned nj) ; 


    const std::vector<const NP*>& aa ; 
    int na ; 
    NP*  com ;  

    int ndom ; 
    NP* dom ; 
    T* dd ; 

    NP* scan ; 
    T* rr ; 

    NPCombineTest(const std::vector<const NP*>& aa_, T x0, T x1, int ndom);

    void dump() const ; 
    void scan_(); 
    void save(); 

}; 

template <typename T>
void NPCombineTest<T>::save() 
{
    dom->save("$FOLD/dom.npy"); 
    com->save("$FOLD/com.npy"); 
    scan->save("$FOLD/scan.npy");
} 

template <typename T>
NPCombineTest<T>::NPCombineTest(const std::vector<const NP*>& aa_, T x0, T x1, int ndom_)
    :
    aa(aa_),
    na(aa.size()),
    com(NP::Combine(aa)),
    ndom(ndom_), 
    dom(NP::Linspace(x0,x1,ndom)),
    dd(dom->values<T>()),
    scan(NP::Make<T>(aa.size(), ndom)),     
    rr(scan->values<T>())
{
    dump(); 
    scan_(); 
    save(); 
}

template <typename T>
void NPCombineTest<T>::dump() const 
{
    std::cout 
        << "NPCombineTest::dump"
        << " na " << na 
        << " ndom " << ndom 
        << "\n"
        << " dom " << ( dom ? dom->desc() : "-" )
        << "\n"
        << " com " << ( com ? com->desc() : "-" )
        << "\n"
        << " scan " << ( scan ? scan->desc() : "-" )
        << "\n"
        ;

    if(1)
    {
        for(int i=0 ; i < na ; i++) 
        {
            std::cout << " i " << std::setw(3) << i << std::endl ; 

            for(int j=0 ; j < std::min(ndom,16) ; j++)
            {
                std::cout 
                    << " j " << std::setw(3) << j 
                    << " rr[ndom*i+j] " << std::setw(10) << std::setprecision(4) << std::fixed << rr[ndom*i+j] 
                    << std::endl 
                    ; 
            }
        }
    }

}

/**
NPCombineTest<T>::scan
-----------------------

CAUTION : be explicit with the type, or risk scrambling the array content.

**/

template <typename T>
void NPCombineTest<T>::scan_() 
{
    T eps = 1e-6 ; 
    //T eps = 0. ; 

    for(NP::INT i=0 ; i < na ; i++ )
    {
        const NP* a = aa[i] ; 
        std::cout << "NPCombineTest::scan " << a->desc() << std::endl ; 

        for(int j=0 ; j < ndom ; j++)
        {
            T x = dd[j] ; 
            T y0 = a->interp<T>(x) ;     // non-combined interpolation 
            //T y1 = com->interp<T>(i, x) ;  // interpolation from the combined array 
            T y1 = com->combined_interp_3<T>(i, x) ;  // interpolation from the combined array 

            T dy = std::abs( y0 - y1 ); 
            bool match = dy <= eps ; 

            if(!match) std::cout 
                << "NPCombineTest::scan"
                << " i " << std::setw(3) << i 
                << " j " << std::setw(3) << j 
                << " x " << std::setw(10) << std::setprecision(4) << std::fixed << x 
                << " y0 " << std::setw(10) << std::setprecision(4) << std::fixed << y0
                << " y1 " << std::setw(10) << std::setprecision(4) << std::fixed << y1
                << " dy " << std::setw(10) << std::setprecision(4) << std::fixed << dy
                << " dy " << std::setw(10) << std::scientific << dy 
                << " eps " << std::setw(10) << std::setprecision(4) << std::fixed << eps
                << " eps " << std::setw(10) << std::scientific << eps 
                << " match " << ( match ? "YES" : "NO " ) 
                << std::endl
                ;
            assert(match ); 

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
    std::cout << "test_RINDEX ndom " << ndom << " narrow " << narrow << "\n"; 

    const char* matdir = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/stree/material" ; 
    NP* a = NP::Load(matdir, "LS/RINDEX.npy") ;
    NP* b = NP::Load(matdir, "LS/RINDEX.npy") ;
    NP* c = NP::Load(matdir, "LS/RINDEX.npy") ;

    std::cout << "test_RINDEX a :" << ( a ? a->sstr() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX b :" << ( b ? b->sstr() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX c :" << ( c ? c->sstr() : "-" ) << "\n" ; 

    std::cout << "test_RINDEX a.repr :" << ( a ? a->repr<double>() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX b.repr :" << ( b ? b->repr<double>() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX c.repr :" << ( c ? c->repr<double>() : "-" ) << "\n" ; 


    a->pscale<double>(1e6, 0u); 
    b->pscale<double>(1e6, 0u); 
    c->pscale<double>(1e6, 0u); 

    a->pscale<double>(1.0,  1u); 
    b->pscale<double>(1.05, 1u); 
    c->pscale<double>(0.95, 1u); 

    std::cout << "test_RINDEX a.repr :" << ( a ? a->repr<double>() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX b.repr :" << ( b ? b->repr<double>() : "-" ) << "\n" ; 
    std::cout << "test_RINDEX c.repr :" << ( c ? c->repr<double>() : "-" ) << "\n" ; 


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

        std::cout << "test_RINDEX an.repr :" << ( an ? an->repr<float>() : "-" ) << "\n" ; 
        std::cout << "test_RINDEX bn.repr :" << ( bn ? bn->repr<float>() : "-" ) << "\n" ; 
        std::cout << "test_RINDEX cn.repr :" << ( cn ? cn->repr<float>() : "-" ) << "\n" ; 

        std::vector<const NP*> aa = { an, bn, cn } ; 
        NPCombineTest<float> t(aa, 1.f, 16.f, ndom ); 
    }
}



int main(int argc, char** argv)
{
    //test_simple(); 
    test_RINDEX(1000, true); 
    return 0 ;
}

