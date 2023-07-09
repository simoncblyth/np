// ./NPFold_Load_test.sh

#include "NPFold.h"

const char* BASE = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim" ;    

void test_Load()
{
    const char* name = "LS" ; 
    NPFold* ls = NPFold::Load(BASE,"stree/material",name) ;   
    std::cout << ls->desc() ; 
}

void test_find_subfold(const NPFold* top, const char* path)
{
    const NPFold* sub = top->find_subfold(path) ; 
    std::cout << "top->find_subfold(\"" << path  << "\")" << std::endl ; 
    std::cout << ( sub ? sub->desc() : "-" ) << std::endl ; 
}
void test_find_subfold()
{
    NPFold* top = NPFold::Load(BASE) ;   
    std::cout << top->desc() ; 

    test_find_subfold(top, "/stree/standard" );  // gives nullptr 
    test_find_subfold(top,  "stree/standard" ); 
}


void test_find_array(const NPFold* top, const char* path)
{
    assert(top); 
    const NP* a = top->find_array(path) ; 
    std::cout << "top->find_array(\"" << path  << "\")" << std::endl ; 
    std::cout << ( a ? a->sstr() : "-" ) << std::endl ; 
}
void test_find_array()
{
    NPFold* top = NPFold::Load(BASE) ;   

    test_find_array(top,  "stree/standard/bnd.npy" ); 
    test_find_array(top,  "GGeo/bnd.npy" ); 
}

int main()
{
    /*
    test_find_subfold(); 
    */
    test_find_array(); 

    return 0 ; 
}
