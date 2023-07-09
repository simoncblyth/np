// ./NPX_Holder_test.sh 

#include "NPFold.h"
#include "NPX.h"

int main()
{
    std::vector<std::string> nn = {"red","green", "blue" } ; 
    NP* a = NPX::Holder(nn); 

    NP* b = NP::Make<int>(1) ; 

    std::cout << " a " << a->sstr() << std::endl ; 

    std::cout << " a.is_empty " << a->is_empty() << std::endl ; 
    std::cout << " b.is_empty " << b->is_empty() << std::endl ; 

    NPFold* fold = new NPFold ; 
    fold->add("a.txt", a ); 
    fold->add("b", b ); 
    fold->save("$FOLD"); 

    return 0 ; 
}


