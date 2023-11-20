#include "NPFold.h"

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl ; 
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    std::cout << "NPFold::Load(\"" << path << "\")" << std::endl ; 

    NPFold* ab = f->subprofile_ab("//p", "//n"); 
    ab->save("$FOLD"); 
    std::cout << "NPFold::subprofile_ab created and saved subprofile symmary NPFold to $FOLD " << std::endl ; 

    return 0 ; 
}




