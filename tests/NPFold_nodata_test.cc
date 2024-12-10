#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 

    const char* prefix = "//A" ; 
    std::vector<const NPFold*> subs ; 
    std::vector<std::string> subpaths ; 
    int maxdepth = 1 ; 
    f->find_subfold_with_prefix(subs, &subpaths,  prefix, maxdepth );  
    assert( subs.size() == subpaths.size() ); 

    std::cout 
        << " find_subfold_with_prefix " << prefix
        << " subs.size " << subs.size()
        << std::endl
        ;

    for(int i=0 ; i < int(subs.size()) ; i++) std::cout << subs[i]->loaddir << std::endl ; 
    for(int i=0 ; i < int(subs.size()) ; i++) std::cout << subs[i]->desc() << std::endl ; 

    // moved further dev to NPFold_stamps_test.cc  

    return 0 ; 
} 



