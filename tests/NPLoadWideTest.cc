// name=NPLoadWideTest ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name
// -DNPU_DEBUG

#include <cstdlib>
#include "NP.hh"

int main(int argc, char** argv)
{
    const char* dpath = "/usr/local/opticks/opticksaux/refractiveindex/tmp/glass/schott/F2.npy" ; 
    const char* npath = getenv("NPATH"); 
    const char* path = argc > 1 ? argv[1] : (npath ? npath :  dpath ) ;  

    bool readable = NPU::is_readable(path) ; 
    if(!readable) 
    {
        std::cout << " non-readable path " << path << std::endl ; 
        return 0 ; 
    }

    std::cout << "loading " << path << std::endl ; 

    NP* a = NP::LoadWide(path) ; 

    assert( a->ebyte == 8 ); 

    a->dump(); 


    return 0 ; 
}


