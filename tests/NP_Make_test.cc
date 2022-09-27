// ./NP_Make_test.sh

#include "NP.hh"

const char* FOLD = "/tmp/NP_Make_test" ; 

void test_Make()
{
    std::cout << "test_Make" << std::endl ; 
    NP* a4 = NP::Make<float>(4, 4, 4); 
    NP* a1 = NP::Make<float>(1, 4, 4); 
    NP* a0 = NP::Make<float>(0, 4, 4); 

    std::cout << " a4 " << a4->sstr() << " a4.dtype " << a4->dtype << std::endl ; 
    std::cout << " a1 " << a1->sstr() << " a1.dtype " << a1->dtype << std::endl ; 
    std::cout << " a0 " << a0->sstr() << " a0.dtype " << a0->dtype << std::endl ; 
}

void test_ctor_zero()
{
    std::cout << "test_ctor_zero" << std::endl ; 
    const char* dtype = "<f4" ; 
    NP* a4 = new NP(dtype, 4, 4, 4); 
    NP* a1 = new NP(dtype, 1, 4, 4); 
    NP* a0 = new NP(dtype, 0, 4, 4); 

    a4->fill(4.f); 
    a1->fill(1.f); 
    a0->fill(0.f); 

    std::cout << " a4 " << a4->sstr() << " a4.dtype " << a4->dtype << std::endl ; 
    std::cout << " a1 " << a1->sstr() << " a1.dtype " << a1->dtype << std::endl ; 
    std::cout << " a0 " << a0->sstr() << " a0.dtype " << a0->dtype << std::endl ; 

    a4->save(FOLD, "a4.npy");
    a1->save(FOLD, "a1.npy");
    a0->save(FOLD, "a0.npy");
}



int main()
{
    //test_Make(); 
    test_ctor_zero(); 

    return 0 ; 
}



