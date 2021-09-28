// name=NPMakePropertyTest ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name 

#include "NP.hh"


void test_0()
{
    std::vector<double> src ;  
    for(unsigned i=0 ; i < 100 ; i++ ) src.push_back(double(i)); 
    NP* a = NP::Make<double>( src );  

    unsigned hd_factor = 0u ; 
    NP* p = NP::MakeProperty<double>(a, hd_factor ); 
    p->dump(); 
}

void test_10()
{
    unsigned ni = 100 ; 
    unsigned nj = 4 ; 

    std::vector<double> src ;  
    for(unsigned i=0 ; i < ni ; i++) for(unsigned j=0 ; j < nj ; j++) src.push_back(double(10*i+j));
 
    NP* a = NP::Make<double>( ni, nj );  
    a->read(src.data()); 

    unsigned hd_factor = 10u ; 
    NP* p = NP::MakeProperty<double>(a, hd_factor ); 
    p->dump(); 

    std::cout << " a " << a->sstr() << std::endl ; 
    std::cout << " p " << p->sstr() << std::endl ; 
}


int main(int argc, char** argv)
{
    //test_0(); 
    test_10();  

    return 0 ; 
}
