// clang NPTest.cc -lc++ -o /tmp/NPTest && /tmp/NPTest
// gcc NPTest.cc -lstdc++ -o /tmp/NPTest && /tmp/NPTest

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
    const char* path = argc > 1 ? argv[1] : "/tmp/c.npy" ; 

    NP<float>* a = make_test_array(10, 4 ); 
    a->save(path) ; 

    std::cout << NPU::check(path) << std::endl ; 

    NP<float>* b = NP<float>::Load(path) ; 
    std::cout << "b " << b->desc() << std::endl; 

    b->dump(0,9); 

    return 0 ; 
}
