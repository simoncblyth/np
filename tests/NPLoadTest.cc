// gcc NPLoadTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/NPLoadTest && /tmp/NPLoadTest

#include "NP.hh"


int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/b.npy" ;  

    bool readable = NPU::is_readable(path) ; 
    if(!readable) 
    {
        std::cout << " non-readable path " << path << std::endl ; 
        return 0 ; 
    }


    NP* b = NP::Load(path) ; 
    b->dump(); 

    return 0 ; 
}
