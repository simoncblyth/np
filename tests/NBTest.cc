// gcc NBTest.cc -std=c++11  -I.. -lstdc++ -o /tmp/NBTest && /tmp/NBTest

#include "NB.hh"


NB* make_array(const char* dtype, int ni, int nj)
{
    NB* a = new NB(dtype, ni, nj)  ;  
    std::cout << "a " << a->desc() << std::endl; 

    if(a->uifc == 'f' && a->ebyte == 4 )
    {
        a->fillIndexFlat<float>() ;
    }

    return a ; 
}


int main(int argc, char** argv)
{
    const char* path1 = argc > 1 ? argv[1] : "/tmp/c.npy" ; 
    const char* path2 = argc > 2 ? argv[2] : "/tmp/c.nph" ; 
    const char* path3 = argc > 3 ? argv[2] : "/tmp/c.npj" ; 

    NB* a = make_array("f4", 10, 4 ); 
    a->save(path1) ; 

    std::cout << NPU::check(path1) << std::endl ; 

    NB* b = NB::Load(path1) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump<float>(0,9); 


    NB* h = NB::Load(path1) ; 
    h->dump<float>(0,9); 

    h->save(path2) ; 


    h->save_jsonhdr(path3);


    return 0 ; 
}
