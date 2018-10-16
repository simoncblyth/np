// clang NPLoadTest.cc -lc++ -o /tmp/NPLoadTest && /tmp/NPLoadTest
// gcc NPLoadTest.cc -lstdc++ -o /tmp/NPLoadTest && /tmp/NPLoadTest

#include "NP.hh"


int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/b.npy" ;  

    //typedef float FPType ; 
    typedef double FPType ; 

    NP<FPType>* b = NP<FPType>::Load(path) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump(0,9); 

    return 0 ; 
}
