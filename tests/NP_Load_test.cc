// name=NP_Load_test ; export FOLD=/tmp/$name ; mkdir -p $FOLD ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"
const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    NP* a = NP::Make<int>(10,4) ; 
    a->fillIndexFlat(); 
    a->save(FOLD, "a.npy") ; 
    std::cout << " a " << a->repr<int>() << std::endl ;  

    NP* b = NP::Load("$FOLD/a.npy") ; 
    std::cout << " b " << b->repr<int>() << std::endl ;  

    NP* c = NP::Load("$FOLD/c.npy") ; 
    std::cout << " c " << ( c ? c->sstr() : "-" ) << std::endl ; 

    NP* d = NP::Load("$UNDEFINED/d.npy") ; 
    std::cout << " d " << ( d ? d->sstr() : "-" ) << std::endl ; 

    NP* e = NP::Load("$UNDEFINED") ; 
    std::cout << " e " << ( e ? e->sstr() : "-" ) << std::endl ; 


    return 0 ; 
}
