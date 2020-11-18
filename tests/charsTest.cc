// gcc charsTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/charsTest && /tmp/charsTest

#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/s.npy" ; 

    NP* a = new NP("|u1", 4) ; 

    a->data[0] = 'x' ; 
    a->data[1] = 'y' ; 
    a->data[2] = 'z' ; 
    a->data[3] = 's' ; 

    a->save(path); 

    int rc = NPU::check(path) ; 

    std::cout << rc << std::endl ; 

    NP* b = NP::Load(path) ; 
    b->dump(); 


    return 0 ; 
}
