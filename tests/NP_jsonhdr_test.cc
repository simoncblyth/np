// gcc NP_jsonhdr_test.cc -std=c++11 -I.. -lstdc++ -o /tmp/NP_jsonhdr_test && /tmp/NP_jsonhdr_test 
/**
NP_jsonhdr_test.cc
====================

1. loads NP array from path provided in argument
2. saves jsonhdr to load path with .npy changed to .npj
3. system call cat the .npj 

::

    cat /tmp/c.npj
    {"descr": "<f4", "fortran_order": false, "shape": [10, 4] }

**/

#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/s.npy" ; 
    NP* a = NP::Load(path) ; 
    if( a == NULL ) return 0 ; 


    a->dump(0,9); 
    a->save_jsonhdr();

    std::string json = a->make_jsonhdr();
    std::cout << json << std::endl ; 


    std::string npj = a->get_jsonhdr_path(); 
    std::string cmd("cat "); 
    cmd += npj ; 
    int rc = system(cmd.c_str()); 
    std::cout << std::endl ; 

    return rc  ; 
}
