// ./NPX_ArrayFromMapUnordered_test.sh 
/**
NPX_ArrayFromMapUnordered_test.cc
===================================

Roundtrip exercise::

    std::unordered_map<int,int>  m0 
    NP*                         _m0
    std::unordered_map<int,int>  m1
    NP*                         _m1


**/

#include "NPX.h"

int main(int argc, char** argv)
{
    std::unordered_map<int, int> m0, m1  ; 

    m0[100] = 1 ; 
    m0[101] = 2 ; 
    m0[102] = 24 ; 

    std::vector<int> key_order = { 100, 101 , 102 } ; 

    NP* _m0 = NPX::ArrayFromMapUnordered<int,int>(m0, key_order ) ; 

    NPX::MapUnorderedFromArray<int>(m1, _m0 ); 

    NP* _m1 = NPX::ArrayFromMapUnordered<int,int>(m1, key_order ) ; 


    bool match = m0 == m1 ; 
    std::cout << " match " << ( match ? "YES" : "NO " ) << std::endl ; 


    _m0->save("$FOLD/m0.npy"); 
    _m1->save("$FOLD/m1.npy"); 


    return 0 ; 
}
