// name=NP_MakeWithType_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::MakeFlat<double>(10,4,4) ; 
    NP* b = NP::MakeWithType<double>( a ); 
    NP* c = NP::MakeWithType<float>(  a ); 

    std::cout << "NP::MakeWithType<double>( a )" << std::endl ; 
    b->dump(); 

    std::cout << "NP::MakeWithType<float>( a )" << std::endl ; 
    c->dump(); 

    return 0 ; 
}


