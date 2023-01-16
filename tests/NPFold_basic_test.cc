// name=NPFold_basic_test ; export FOLD=/tmp/$name ; mkdir -p $FOLD ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name && $FOLD/$name

#include "NPFold.h"

const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    NPFold* f0 = new NPFold ; 

    NP* a = NP::Linspace<int>(0, 100, 101) ; 
    NP* b = NP::Linspace<double>(0, 100, 101) ; 

    std::cout << " a " << a->repr<int>() << std::endl ; 
    std::cout << " b " << b->repr<double>() << std::endl ; 

    f0->add("a", a ); 
    f0->add("b", b ); 

    f0->save(FOLD); 


    NPFold* f1 = NPFold::Load(FOLD); 

    const NP* a1 = f1->get("a"); 
    const NP* b1 = f1->get("b"); 

    std::cout << " a1 " << a1->repr<int>() << std::endl ; 
    std::cout << " b1 " << b1->repr<double>() << std::endl ; 



    return 0 ; 
}



