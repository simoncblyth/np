// clang NPTest.cc -lc++ -o /tmp/NPTest && /tmp/NPTest
// gcc NPTest.cc -lstdc++ -o /tmp/NPTest && /tmp/NPTest

#include "NP.hh"

int main(int argc, char** argv)
{
    // define float array shape (10,4)   (up to 5 dimensions implemented)

    int ni = 10 ; 
    int nj = 4 ; 

    NP<float> a(ni, nj)  ;  
    std::cout << "a " << a.desc() << std::endl; 

    for(int i=0 ; i < ni ; i++ )
    {
        for(int j=0 ; j < nj ; j++ )
        {
            int index = i*nj + j ;           // 2d indices -> 1d 
            a.data[index] = float(index) ;   // fill vector with dummy value  
        }        
    }

    const char* path = "/tmp/c.npy" ; 

    a.save(path) ; 
    std::cout << NPU::check(path) << std::endl ; 


    NP<float> b ; 
    b.load(path); 

    std::cout << "b " << b.desc() << std::endl; 

    b.dump(0,9); 


    return 0 ; 
}
