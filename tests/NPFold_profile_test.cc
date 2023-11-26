/**
NPFold_profile_test.cc
========================

::

   ~/np/tests/NPFold_profile_test.sh 

**/


#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 
    U::SetEnvDefaultExecutableSiblingPath("FOLD", argv[0], dirp );

    NPFold* f = NPFold::LoadNoData(dirp); 
    std::cout 
        << argv[0] 
        << std::endl
        << "NPFold_profile_test"
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        ;

    if(getenv("VERBOSE")!=nullptr) std::cout
        << "[NPFold_profile_test.VERBOSE" 
        << std::endl 
        << f->desc() 
        << std::endl 
        << "]NPFold_profile_test.VERBOSE" 
        << std::endl 
        ; 

    NPFold* smry = f->subfold_summary("subprofile", "a://p", "b://n"); 
    std::cout 
        << "NPFold* smry = NPFold::subfold_summary(\"subprofile\", \"a://p\", \"b://n\") ; smry->desc() "
        << std::endl 
        << (smry ? smry->desc() : "smry NULL" ) 
        << std::endl 
        ;

    if(smry) smry->save("$FOLD"); 

    return 0 ; 
}


