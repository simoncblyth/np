// name=NP_ARange_test ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"

void dump(const NP* a, const char* msg )
{
    std::cout << std::endl << msg << std::endl ; 
    std::cout << " a.sstr " << a->sstr() << std::endl ; 
    std::cout << " a.desc " << a->desc() << std::endl ; 

    const double* aa = a->cvalues<double>(); 
    for(int i=0 ;i < a->shape[0]; i++) std::cout << aa[i] << std::endl ; 
}


int main(int argc, char** argv)
{
    NP* a = NP::ARange<double>(10,100,10) ; 
    NP* b = NP::ARange<double>(10,100.01,10) ; 
    
    dump(a, "a NP::ARange<double>(10,100,10) "); 
    dump(b, "b NP::ARange<double>(10,100.01,10) ");           

    return 0 ; 
}
