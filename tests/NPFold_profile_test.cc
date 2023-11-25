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
        << f->desc() 
        << std::endl 
        ; 

    NPFold* ab = f->subfold_summary("subprofile", "a://p", "b://n"); 
    std::cout 
        << "NPFold* ab = NPFold::subfold_summary('P', \"a://p\", \"b://n\") ; ab->desc() "
        << std::endl 
        << ab->desc()
        << std::endl 
        ;

    ab->save("$FOLD"); 

    return 0 ; 
}




