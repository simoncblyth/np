// name=NPFold_has_all_keys_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPFold.h"

int main(int argc, char** argv)
{
    NPFold* f0 = new NPFold ; 
    f0->add("red", NP::Linspace<int>(0, 100, 101) ); 
    f0->add("green", NP::Linspace<double>(0, 100, 101) ); 
    f0->add("blue", NP::Linspace<double>(0, 100, 101) ); 

    assert( f0->has_all_keys("red") == true ); 
    assert( f0->has_all_keys("red,green") == true ); 
    assert( f0->has_all_keys("red,green,blue") == true ); 
    assert( f0->has_all_keys("red,green,blue,cyan") == false ); 

    NPFold* f1 = new NPFold ; 
    f1->add("red", NP::Linspace<int>(0, 100, 101) ); 
    f1->add("green", NP::Linspace<double>(0, 100, 101) ); 
     
    NPFold* f2 = new NPFold ; 
    f2->add("red", NP::Linspace<int>(0, 100, 101) ); 
   

    NPFold* ff = new NPFold ; 
    ff->add_subfold( "f0", f0 ); 
    ff->add_subfold( "f1", f1 ); 
    ff->add_subfold( "f2", f2 ); 


    std::vector<const NPFold*> subs0 ; 
    ff->find_subfold_with_all_keys(subs0,  "red" ); 
    assert( subs0.size() == 3 ); 

    std::vector<const NPFold*> subs0_ ; 
    std::vector<std::string> names0 ; 
    ff->find_subfold_with_all_keys(subs0_, names0,  "red" ); 
    assert( subs0_.size() == subs0.size() ); 
    assert( subs0_.size() == names0.size() ); 
    assert( subs0_.size() == 3 ); 
    


    std::vector<const NPFold*> subs1 ; 
    ff->find_subfold_with_all_keys( subs1, "red,green" ); 
    assert( subs1.size() == 2 ); 

    std::vector<const NPFold*> subs2 ; 
    ff->find_subfold_with_all_keys( subs2, "red,green,blue" ); 
    assert( subs2.size() == 1 ); 

    return 0 ; 
}



