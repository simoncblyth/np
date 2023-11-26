// name=NPFold_LoadNoData_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 

    bool VERBOSE = getenv("VERBOSE") != nullptr ; 
 
    NPFold* f = NPFold::LoadNoData(dirp); 

    std::cout 
        << argv[0]
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        ;   

    if(VERBOSE || true) std::cout 
        << "[" << argv[0] << ".VERBOSE "
        << std::endl
        << ( f ? f->desc() : "-" )
        << std::endl
        << "]" << argv[0] << ".VERBOSE "
        << std::endl
        ;

    return 0 ; 
}
