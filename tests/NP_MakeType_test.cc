// name=NP_MakeType_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::MakeFlat<double>(10,4,4) ; 
    NP* b = NP::MakeType<double>( a ); 
    NP* c = NP::MakeType<float>( a ); 

    c->dump(); 

    return 0 ; 
}


