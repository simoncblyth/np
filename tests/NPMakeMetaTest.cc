// gcc NPMakeMetaTest.cc -I.. -lstdc++ -o /tmp/NPMakeMetaTest && /tmp/NPMakeMetaTest 

/**

::

    cat /tmp/c.npj
    {"descr": "<f4", "fortran_order": false, "shape": [10, 4] }


**/

#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/c.npy" ; 

    NP<float>* h = NP<float>::Load(path) ; 
    h->dump(0,9); 

    h->save_jsonhdr();


    return 0 ; 
}
