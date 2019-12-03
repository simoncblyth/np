// gcc NPMinimal.cc -lstdc++ && ./a.out /tmp/a.npy && rm a.out
#include "NP.hh"
int main(int argc, char** argv)
{
    assert( argc > 1 && argv[1] ) ; 
    NP<long>* a = NP<long>::Load(argv[1]) ; 
    a->dump(); 
    return 0 ; 
}
