// ./NPFold_Load_test.sh

#include "NPFold.h"

int main()
{
    const char* BASE = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry" ;    
    const char* name = "LS" ; 
    NPFold* ls = NPFold::Load(BASE,"SSim/stree/material",name) ;   
    std::cout << ls->desc() ; 

    return 0 ; 
}
