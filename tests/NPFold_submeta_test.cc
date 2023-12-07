// ~/np/tests/NPFold_submeta_test.sh 
#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::LoadNoData(path); 
    //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 

    NP* a = f->submeta("//A") ; 
    std::cout << a->descTable<int64_t>( 10 ) ; 
    a->save("$FOLD/a.npy"); 
  
    return 0 ; 
}




