// ./NP_LoadFromString_Test.sh

#include "NPX.h"

int main(int argc, char** argv)
{
    const char* a_str = "10\n20\n30" ; 
    const char* b_str = "10,20,30" ; 

    NP* a = NP::LoadFromString<int>(a_str) ; 
    std::cout << a->sstr() ; 
    std::cout << a->desc() ; 
    a->save("$FOLD/a.npy") ; 

    NP* b = NPX::FromString<int>(b_str,',') ; 
    std::cout << b->sstr() ; 
    std::cout << b->desc() ; 
    b->save("$FOLD/b.npy") ; 


    return 0 ; 
}
