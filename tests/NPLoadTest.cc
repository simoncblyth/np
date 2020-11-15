// gcc NPLoadTest.cc -I.. -lstdc++ -o /tmp/NPLoadTest && /tmp/NPLoadTest

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

    //typedef float FPType ; 
    typedef double FPType ; 

    NP<FPType>* b = NP<FPType>::Load(path) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump(0,9); 

    return 0 ; 
}
