/**
~/np/tests/NPFold_stamps_test.sh 

See ~/opticks/sysrap/tests/sstampfold_test.cc for an encapsulation of this 

**/

#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 
    U::SetEnvDefaultExecutableSiblingPath("FOLD", argv[0], dirp );
 
    NPFold* f = NPFold::LoadNoData(dirp); 

    bool noload = f == nullptr ; 
    if(noload) std::cerr
       << argv[0]
       << " : " 
        << "NPFold_stamps_test"
        << "\n"
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << " noload " << ( noload ? "YES" : "NO " )
        << "\n"
       ; 

    if(noload) return 0 ; 

    std::cout
        << "f.desc\n" 
        << ( f ? f->desc() : "-" ) 
        << "\n"
        ; 

    const char* keyname = "substamp" ; 
    const char* delta_keyname = U::FormName("delta_", keyname, nullptr); 

    const char* akey = "a://A" ; 
    const char* bkey = "b://B" ; 

    NPFold* ab = f->subfold_summary(keyname, akey, bkey ); 

    bool ab_null = ab == nullptr ; 

    std::cout 
        << "NPFold_stamps_test.main"
        << " ab_null " << ( ab_null ? "YES" : "NO " )
        << " akey " << ( akey ? akey : "-" )
        << " bkey " << ( bkey ? bkey : "-" )
        << " delta_keyname " << ( delta_keyname ? delta_keyname : "-" )
        << " dirp " << ( dirp ? dirp : "-" ) 
        << "\n"
       ;
    

    const NP* adt = ab ? ab->find_array("a", delta_keyname) : nullptr  ; 
    const NP* bdt = ab ? ab->find_array("b", delta_keyname) : nullptr ; 

    std::cout 
        << "NPFold* ab = NPFold::subfold_summary(\"" 
        << keyname 
        << "\", \"" 
        << akey 
        << "\", \"" 
        << bkey 
        << "\")"
        << " ; ab->desc() "
        << std::endl 
        << ( ab ? ab->desc() : "ab-is-nullptr" )
        << std::endl 
        << "adt"
        << std::endl 
        << ( adt ? adt->descTable<int64_t>(8) : "adt-is-nullptr" )
        << std::endl 
        << "bdt"
        << std::endl 
        << ( bdt ? bdt->descTable<int64_t>(8) : "bdt-is-nullptr" )
        << std::endl 
        ;

    if(ab) ab->save("$FOLD"); 
    return 0 ; 
} 


