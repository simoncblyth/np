// ~/np/tests/NPFold_LoadNoData_test.sh

#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 

    bool VERBOSE = getenv("VERBOSE") != nullptr ; 
 
    NPFold* f = NPFold::LoadNoData(dirp); 

    const NP* run = f->get("run"); 
    std::cout 
        << " run " << ( run ? run->sstr() : "-" ) 
        << std::endl 
        << ( run ? run->meta : "-" ) 
        << std::endl 
        << ( run ? run->descMetaKV() : "-" ) 
        << std::endl 
        << ( run ? run->descMetaKVS() : "-" ) 
        << std::endl 
        ; 


    std::cout 
        << argv[0]
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        ;   

    if(VERBOSE) std::cout 
        << "[" << argv[0] << ".VERBOSE "
        << std::endl
        << ( f ? f->desc() : "-" )
        << std::endl
        << "]" << argv[0] << ".VERBOSE "
        << std::endl
        ;

    return 0 ; 
}

// ~/np/tests/NPFold_LoadNoData_test.sh

