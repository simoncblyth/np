// name=NP_all_zero_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name
#include "NP.hh"

template<typename T>
void test_is_allzero()
{
    NP* a = NP::Make<T>(10,4,4) ; 
    assert( a->is_allzero<T>() == true );  

    T* vv = a->values<T>(); 

    vv[10] = T(1) ; 
    assert( a->is_allzero<T>() == false ); 

    vv[10] = T(0) ; 
    assert( a->is_allzero<T>() == true ); 
}


int main()
{
    test_is_allzero<float>(); 
    test_is_allzero<int>(); 
    test_is_allzero<unsigned>(); 

    return 0 ; 
}
