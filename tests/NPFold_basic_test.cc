// ~/np/tests/NPFold_basic_test.sh

#include "NPFold.h"

void test_save_load()
{
    NPFold* f0 = new NPFold ; 

    NP* a = NP::Linspace<int>(0, 100, 101) ; 
    NP* b = NP::Linspace<double>(0, 100, 101) ; 

    std::cout << " a " << a->repr<int>() << std::endl ; 
    std::cout << " b " << b->repr<double>() << std::endl ; 

    f0->add("a", a ); 
    f0->add("b", b ); 

    f0->save("$FOLD"); 


    NPFold* f1 = NPFold::Load("$FOLD"); 

    const NP* a1 = f1->get("a"); 
    const NP* b1 = f1->get("b"); 

    std::cout << " a1 " << a1->repr<int>() << std::endl ; 
    std::cout << " b1 " << b1->repr<double>() << std::endl ; 
}

void test_save_load_empty()
{
    NPFold* f0 = new NPFold ; 
    f0->save("$FOLD/empty"); 

    NPFold* f1 = NPFold::Load("$FOLD/empty"); 

}



int main(int argc, char** argv)
{
    /*
    test_save_load(); 
    */
    test_save_load_empty(); 

    return 0 ; 
}



