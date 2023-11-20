#include "NPFold.h"


int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    std::cout << " path " << path << std::endl << f->desc() << std::endl ; 


    const char* prefix = "//p" ;  
    std::vector<const NPFold*> subs ; 
    f->find_subfold_with_prefix(subs, nullptr,  prefix );  

    std::vector<std::string> ukey ; 
    NPFold::Subkey( ukey, subs ); 

    std::vector<std::string> ckey ; 
    std::vector<std::string> cval ; 
    NPFold::SubCommonKV( ckey, cval, subs ); 

    std::cout << NPFold::DescCommonKV( ckey, cval ) << std::endl ; 

  
    return 0 ; 
}




