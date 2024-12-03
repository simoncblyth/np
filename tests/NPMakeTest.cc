// ~/np/tests/NPMakeTest.sh

#include "NP.hh"

void test_MakeRindexArray(double rindex=1.5)  // static
{
    NP* a = NP::Make<double>( 1.55/1e6, rindex, 15.5/1e6, rindex ) ; 

    a->change_shape(-1, 2); 
    a->pdump("MakeRindexArray" , 1e6 );  

    unsigned nv = a->num_values() ; 
    const double* aa = a->cvalues<double>(); 
        
    for(unsigned i=0 ; i < nv ; i++) std::cout << i << " : " << aa[i] << std::endl ; 
    assert(a) ; 
}

void test_MakeFromValues()
{
    NP* a = NP::Make<double>( 10. , 100., 20.,  100. );  

    unsigned nv0 = a->num_values() ; 
    std::cout << " nv0 " << nv0 << std::endl ; 

    a->change_shape(-1,2); 
    a->pdump<double>("test_MakeFromValues"); 

    unsigned nv1 = a->num_values() ; 
    std::cout << " nv1 " << nv1 << std::endl ; 
    
    assert( nv0 == nv1 ); 

    std::vector<double> d, v ; 

    a->psplit<double>( d, v ); 

    assert( d.size() == v.size() ); 
    assert( d.size() == 2 ); 
    assert( v.size() == 2 ); 


    for(unsigned i=0 ; i < d.size() ; i++)
    {
        std::cout 
            << " d " << std::setw(10) << d[i] 
            << " v " << std::setw(10) << v[i] 
            << std::endl
            ; 
    }
}

void test_Make6()
{
    NP* a = NP::Make<float>(3, 2, 2, 10, 10, 4); 
    a->fillIndexFlat(); 
    a->save("$FOLD/a6.npy"); 
}



int main(int argc, char** argv)
{
    //test_MakeRindexArray(); 
    //test_MakeFromValues(); 
    test_Make6(); 
    
    return 0 ; 
}
