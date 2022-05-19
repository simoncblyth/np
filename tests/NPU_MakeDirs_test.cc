// name=NPU_MakeDirs_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

int main()
{
    int rc ; 

    const char* dirpath = "/tmp/NPU_MakeDirs_test/some/deep/dirpath" ; 
    rc = U::MakeDirs(dirpath); 
    assert( rc == 0 ); 

    const char* filepath = "/tmp/NPU_MakeDirs_test/some/deep/filepath/name.npy" ; 
    rc = U::MakeDirsForFile(filepath); 
    assert( rc == 0 ); 

    NP* a = NP::Make<float>(1,4,4); 
    a->fillIndexFlat(); 
    a->save(filepath); 


    return 0 ; 
}
