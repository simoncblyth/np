// gcc NPTest.cc -std=c++11  -I.. -lstdc++ -o /tmp/NPTest && /tmp/NPTest

#include "NP.hh"


NP<float>* make_array(int ni, int nj)
{
    NP<float>* a = new NP<float>(ni, nj)  ;  
    std::cout << "a " << a->desc() << std::endl; 
    a->fillIndexFlat() ;
    return a ; 
}


int main(int argc, char** argv)
{
    const char* path1 = argc > 1 ? argv[1] : "/tmp/c.npy" ; 
    const char* path2 = argc > 2 ? argv[2] : "/tmp/c.nph" ; 
    const char* path3 = argc > 3 ? argv[2] : "/tmp/c.npj" ; 

    NP<float>* a = make_array(10, 4 ); 
    a->save(path1) ; 

    std::cout << NPU::check(path1) << std::endl ; 

    NP<float>* b = NP<float>::Load(path1) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump(0,9); 


    NP<float>* h = NP<float>::Load(path1) ; 
    h->dump(0,9); 

    h->save(path2) ; 


    h->save_jsonhdr(path3);


    return 0 ; 
}