/**
~/np/tests/NPFold_stamps_test.sh 

**/

#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 
    U::SetEnvDefaultExecutableSiblingPath("FOLD", argv[0], dirp );
 
    NPFold* f = NPFold::LoadNoData(dirp); 
    std::cout 
        << "NPFold_stamps_test"
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        << f->desc() 
        << std::endl 
        ; 

    const char* keyname = "substamp" ; 
    const char* delta_keyname = U::FormName("delta_", keyname, nullptr); 
    NPFold* ab = f->subfold_summary(keyname, "a://p", "b://n"); 
    const NP* adt = ab->find_array("a", delta_keyname) ; 
    const NP* bdt = ab->find_array("b", delta_keyname) ; 

    std::cout 
        << "NPFold* ab = NPFold::subfold_summary(\"" << keyname << "\", \"a://p\", \"b://n\") ; ab->desc() "
        << std::endl 
        << ab->desc()
        << std::endl 
        << "adt"
        << std::endl 
        << ( adt ? adt->descTable<int64_t>(8) : "-" )
        << std::endl 
        << "bdt"
        << std::endl 
        << ( bdt ? bdt->descTable<int64_t>(8) : "-" )
        << std::endl 
        ;

    ab->save("$FOLD"); 
    return 0 ; 
} 



