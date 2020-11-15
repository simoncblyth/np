// gcc NPMakeMetaTest.cc -I.. -lstdc++ -o /tmp/NPMakeMetaTest && /tmp/NPMakeMetaTest 

#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/c.npy" ; 

    NP<float>::ONLY_HEADER = true ; 
    NP<float>* h = NP<float>::Load(path) ; 
    h->dump(0,9); 

    h->savemeta();


    return 0 ; 
}
