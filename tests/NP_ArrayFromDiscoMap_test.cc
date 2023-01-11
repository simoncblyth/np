// ./NP_ArrayFromDiscoMap_test.sh
#include "NP.hh"

const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    std::map<int, int> m0 ; 
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

    std::cout << "m0" << std::endl << NP::DescDiscoMap(m0) ; 


    NP* a = NP::ArrayFromDiscoMap<int>( m0 ); 

    std::map<int, int> m1 ; 
    NP::DiscoMapFromArray<int>( m1, a ); 

    std::cout << "m1" << std::endl << NP::DescDiscoMap(m1) ; 

    a->save(FOLD, "a.npy" ); 


    return 0 ; 
}

