/**
NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test.cc 
========================================================

~/np/tests/NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test.sh

**/

#include "NPX.h"

struct NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test
{

    template<typename T, int N>
    static std::string Desc(const std::vector<std::array<T,N>>& va); 

    static int Main(); 
}; 


template<typename T, int N>
inline std::string NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test::Desc(const std::vector<std::array<T,N>>& va )
{
    std::stringstream ss ;
    for(int i=0 ; i < int(va.size()); i++)
    {
        const std::array<double,3>& arr = va[i]; 
        for(int j=0 ; j < 3 ; j++) ss << std::setw(10) << arr[j] << " " ; 
        ss << "\n" ; 
    }
    std::string str = ss.str();
    return str ; 
}


inline int NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test::Main()
{
    std::vector<std::array<double,3>> va ;
    va.resize(4); 
    va[0] = {1,2,3} ; 
    va[1] = {4,5,6} ; 
    va[2] = {7,8,9} ;
    va[3] = {10,11,12} ;
 
    std::cout << "va\n" << Desc<double,3>(va) ; 

    NP* a = NPX::ArrayFromVecOfArrays<double,3>( va ); 

    std::vector<std::array<double,3>> vb ;
    NPX::VecOfArraysFromArray<double,3>( vb, a ); 

    std::cout << "vb\n" << Desc<double,3>(vb) ;  

    assert( va.size() == vb.size() );
    assert( va == vb ); 

    return 0 ; 
}


int main()
{
    return NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test::Main() ; 
}

