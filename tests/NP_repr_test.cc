// name=NP_repr_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<double>(1000 ); 
    a->fillIndexFlat(); 
    std::cout << a->repr<double>() << std::endl ; 

    return 0 ; 
}
