// name=NP_write_Test ; mkdir /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<float>( 10.f, 100.f, 20.f, 200.f ); 

    unsigned ni = a->shape[0] ; 
    assert( ni == 4 ); 

    std::vector<float> v(ni) ; 
    a->write<float>(v.data()); 

    for(unsigned i=0 ; i < ni ; i++ ) std::cout << v[i] << std::endl ; 

    return 0 ; 
}
