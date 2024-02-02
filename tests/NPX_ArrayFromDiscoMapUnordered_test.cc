// ./NPX_ArrayFromDiscoMapUnordered_test.sh

#include "NPX.h"


int test_roundtrip_0()
{
    std::unordered_map<int, int> m0 ; 
    m0[0] = 0 ; 
    m0[1] = 1 ; 
    m0[2] = 2 ; 
    m0[3] = 0 ; 
    m0[4] = 1 ; 
    m0[5] = 2 ; 
    m0[10] = 3 ;  
    m0[11] = 3 ;  
    m0[12] = 3 ;  
    m0[13] = 3 ;  

    std::cout << "m0" << std::endl << NPX::DescDiscoMapUnordered(m0) ; 

    NP* a = NPX::ArrayFromDiscoMapUnordered<int>( m0 ); 
    if(a == nullptr) return 1 ; 

    std::unordered_map<int, int> m1 ; 
    NPX::DiscoMapUnorderedFromArray<int>( m1, a ); 

    std::cout << "m1" << std::endl << NPX::DescDiscoMapUnordered(m1) ; 

    a->save("$FOLD/a.npy" ); 

    return 0 ; 
}



int main(int argc, char** argv)
{
    int rc = test_roundtrip_0();
    if(rc != 0) std::cerr << argv[0] << " " << " FATAL " << std::endl ; 

    return 0 ; 
}

