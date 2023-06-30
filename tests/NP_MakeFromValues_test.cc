// name=NP_MakeFromValues_test ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"


int main(int argc, char** argv)
{
    const int N = 4 ; 
    double v[N] = {10., 20., 30., 40. } ; 

    NP* a = NP::MakeFromValues<double>(v, N);  

    std::cout << " a.sstr " << a->sstr() << std::endl ; 
    std::cout << " a.desc " << a->desc() << std::endl ; 
    std::cout << " a.repr"  << a->repr<double>() << std::endl ; 

    return 0 ; 
}
