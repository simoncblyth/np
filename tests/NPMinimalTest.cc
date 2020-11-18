// gcc NPMinimalTest.cc -I.. -lstdc++ -o /tmp/NPMinimalTest && /tmp/NPMinimalTest /tmp/a.npy 
#include "NP.hh"
int main(int argc, char** argv)
{
    assert( argc > 1 && argv[1] ) ; 
    NP* a = NP::Load(argv[1]) ; 
    a->dump(); 
    return 0 ; 
}
