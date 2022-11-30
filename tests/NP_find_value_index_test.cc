// name=NP_find_value_index_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* u = NP::Make<double>(1000) ; 
    u->fillIndexFlat(); 

    double v = 100. ; 
    int idx = u->find_value_index<double>( v, 1e-6 ); 

    std::cout << " idx " << idx << std::endl ;  
    return 0 ; 
}
