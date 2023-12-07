/**
~/np/tests/NPFold_subcount_test.sh 
**/

#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 
    U::SetEnvDefaultExecutableSiblingPath("FOLD", argv[0], dirp );
 
    NPFold* f = NPFold::LoadNoData(dirp); 

    std::cout << "[NPFold_subcount_test.subcount" << std::endl ; 
    NP* count = f->subcount("//A") ; 
    std::cout << "]NPFold_subcount_test.subcount" << std::endl ; 

    std::cout 
        << "NPFold_stamps_test"
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        //<< f->desc() 
        << std::endl 
        << count->descTable<int>()
        << std::endl 
        ; 


    NPFold* out = new NPFold ; 
    out->add("count", count ); 
    out->save("$FOLD"); 
    return 0 ; 
} 


