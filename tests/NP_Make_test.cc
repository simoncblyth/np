/**
NP_Make_test.cc
================

~/np/tests/NP_Make_test.sh 

**/

#include "NP.hh"


struct NP_Make_test
{
    static int Make(); 
    static int ctor(); 
    static int Large(); 

    static int Main(); 
};

int NP_Make_test::Make()
{
    std::cout << "NP_Make_test" << std::endl ; 
    NP* a4 = NP::Make<float>(4, 4, 4); 
    NP* a1 = NP::Make<float>(1, 4, 4); 
    NP* a0 = NP::Make<float>(0, 4, 4); 

    std::cout << " a4 " << a4->sstr() << " a4.dtype " << a4->dtype << std::endl ; 
    std::cout << " a1 " << a1->sstr() << " a1.dtype " << a1->dtype << std::endl ; 
    std::cout << " a0 " << a0->sstr() << " a0.dtype " << a0->dtype << std::endl ; 

    a4->save("$FOLD/a4.npy");
    a1->save("$FOLD/a1.npy");
    a0->save("$FOLD/a0.npy");

    return 0 ; 
}

int NP_Make_test::ctor()
{
    std::cout << "NP_Make_test::ctor_zero" << std::endl ; 
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

    a4->save("$FOLD/a4.npy");
    a1->save("$FOLD/a1.npy");
    a0->save("$FOLD/a0.npy");

    return 0 ; 
}

int NP_Make_test::Large()
{
    std::cout << "NP_Make_test::Large" << std::endl ; 

    int M = 1000000 ; 
    int ni = M*100 ; 
    int nj = 16 ; 

    NP* a = NP::Make<int>(ni, nj );
 
    a->save("$FOLD/Large.npy" ); 

    return 0 ; 
}


int NP_Make_test::Main()
{
    const char* TEST = U::GetEnv("TEST", "ALL") ; 
    bool ALL = strcmp(TEST, "ALL") == 0 ; 
    int rc = 0 ; 
    if(ALL||strcmp(TEST,"Make")==0) rc += Make();    
    if(ALL||strcmp(TEST,"ctor")==0) rc += ctor();    
    if(ALL||strcmp(TEST,"Large")==0) rc += Large();    
    return rc ; 
}

int main(){ return NP_Make_test::Main() ; }


