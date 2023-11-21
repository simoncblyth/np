#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 

    NPFold* ab = f->subfold_summary('S', "a://p", "b://n"); 
    ab->save("$FOLD"); 

    return 0 ; 
} 



