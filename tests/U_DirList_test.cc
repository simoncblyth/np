// name=U_DirList_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPU.hh"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    const char* root = getenv("NP_PROP_BASE") ; 
    if(!root) return 0 ; 

    const char* base = U::Path(root, "PMTProperty") ;  

    std::vector<std::string> names ; 
    U::DirList(names, base) ; 

    for(unsigned i=0 ; i < names.size() ; i++) 
    {
         const char* name = names[i].c_str(); 

         int pt = U::PathType( base, name ); 

         std::cout << std::setw(3) << pt << ":" << name << std::endl; 
    }


    return 0 ; 
}


