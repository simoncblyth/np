// name=NPmetaTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <vector>
#include <iostream>
#include "NP.hh"


void test_meta_0()
{
    NP* a = NP::Make<double>( 10, 5 ); 
    a->fill<double>(1.); 
    a->meta = "one\ntwo\nthree\n" ; 
    a->dump(); 

    // std::cout << "a.meta [" << a->meta << "]" << std::endl ; 

    const char* path = "/tmp/NPmetaTest/meta_0.npy" ; 
    a->save(path); 

    NP* b = NP::Load(path); 
    b->dump(); 

    // std::cout << "b.meta [" << b->meta << "]" << std::endl ; 

    if( not a->meta.empty() )
    {
        assert( strcmp( a->meta.c_str(), b->meta.c_str() ) == 0 ) ; 
    }
}



void test_meta_1()
{
    std::vector<std::string> names = {"red", "green", "blue", "cyan", "magenta", "yellow" } ; 

    NP* a = NP::Make<double>( 10, 5 ); 
    a->fill<double>(1.); 
    a->set_meta(names) ;  
    a->dump(); 

    // std::cout << "a.meta [" << a->meta << "]" << std::endl ; 

    const char* path = "/tmp/NPmetaTest/meta_1.npy" ; 
    a->save(path); 

    NP* b = NP::Load(path); 
    b->dump(); 

    // std::cout << "b.meta [" << b->meta << "]" << std::endl ; 

    if( not a->meta.empty() )
    {
        assert( strcmp( a->meta.c_str(), b->meta.c_str() ) == 0 ) ; 
    }
}







int main(int argc, char** argv)
{
    test_meta_0();
    test_meta_1();

 
    return 0 ;
}

