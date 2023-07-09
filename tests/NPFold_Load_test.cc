// ./NPFold_Load_test.sh

#include "NPFold.h"

const char* BASE = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim" ;    

void test_LS()
{
    const char* name = "LS" ; 
    NPFold* ls = NPFold::Load(BASE,"stree/material",name) ;   
    std::cout << ls->desc() ; 
}


int main()
{
    NPFold* fold = NPFold::Load(BASE) ;   
    std::cout << fold->desc() ; 


    return 0 ; 
}
