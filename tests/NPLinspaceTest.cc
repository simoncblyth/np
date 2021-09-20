// name=NPLinspaceTest ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main()
{
    NP* a = NP::Linspace<double>(0., 5., 6); 
    std::cout << a->desc() << std::endl ; 
    a->dump(); 

    NP* b = NP::Linspace<double>(0., 5., 1); 
    std::cout << b->desc() << std::endl ; 
    b->dump(); 



    return 0 ; 
}
