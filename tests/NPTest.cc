// gcc NPTest.cc -I.. -lstdc++ -o /tmp/NPTest && /tmp/NPTest

#include "NP.hh"


NP<float>* make_test_array(int ni, int nj)
{
    NP<float>* a = new NP<float>(ni, nj)  ;  

    std::cout << "a " << a->desc() << std::endl; 

    for(int i=0 ; i < ni ; i++ )
    {
        for(int j=0 ; j < nj ; j++ )
        {
            int index = i*nj + j ;           // 2d indices -> 1d 
            a->data[index] = float(index) ;   // fill vector with dummy value  
        }        
    }
    return a ; 
}


int main(int argc, char** argv)
{
    const char* path1 = argc > 1 ? argv[1] : "/tmp/c.npy" ; 
    const char* path2 = argc > 2 ? argv[2] : "/tmp/c.nph" ; 
    const char* path3 = argc > 3 ? argv[2] : "/tmp/c.npj" ; 

    NP<float>* a = make_test_array(10, 4 ); 
    a->save(path1) ; 

    std::cout << NPU::check(path1) << std::endl ; 

    NP<float>* b = NP<float>::Load(path1) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump(0,9); 


    NP<float>::ONLY_HEADER = true ; 
    std::cout << "ONLY_HEADER" << std::endl ; 
    NP<float>* h = NP<float>::Load(path1) ; 
    h->dump(0,9); 

    h->save(path2) ; 


    h->savejsonhdr(path3);


    return 0 ; 
}
