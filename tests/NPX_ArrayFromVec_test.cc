/**

~/np/tests/NPX_ArrayFromVec_test.sh 

**/

#include "NPFold.h"
#include "NPX.h"
#include <array>

struct Compound
{
    int ii[16] ; 
    std::string desc() const ; 
}; 

inline std::string Compound::desc() const
{
    std::stringstream ss ; 
    ss << "Compound::desc" ; 
    ss << "ii[0:16] [" ; 
    for(int i=0 ; i < 16 ; i++) ss << ii[i] << " " ; 
    ss << "]" ; 
    std::string str = ss.str(); 
    return str ; 
}


struct Compound2
{
    int ii[1] ;
    std::array<int,3> aa ; 
    std::array<int,3> bb ; 
    std::array<int,9> cc ; 
    std::string desc() const ; 
}; 


inline std::string Compound2::desc() const
{
    std::stringstream ss ; 
    ss << "Compound2::desc "  
       << " ii[0] " << ii[0]
       << " aa[0:3] [" << aa[0] << "," << aa[1] << "," << aa[2] << "]"
       << " bb[0:3] [" << bb[0] << "," << bb[1] << "," << bb[2] << "]"
       ;
    
    ss << "cc[0:9] [" ; 
    for(int i=0 ; i < 9 ; i++) ss << cc[i] << " " ; 
    ss << "]" ;

    std::string str = ss.str(); 
    return str ; 
}


/**
struct Compound3
{
    int ii[8] ;
    std::vector<int> aa ; 
}; 
**/



template<typename T>
int test_ArrayFromVec()
{
    std::cout << "test_ArrayFromVec: sizeof(T)" << sizeof(T) << "\n" ;  
    std::vector<T> v = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }} ; 

    const T& t = v[0] ; 
    std::cout << " t.desc\n " << t.desc() << "\n" ; 

    NP* a = NPX::ArrayFromVec<int,T>( v, 4, 4) ; 
    NPFold* f = new NPFold ; 
    f->add("a_args", NPX::ArrayFromVec<int,T>(  v, 4, 4  )) ; 
    f->add("a_str",  NPX::ArrayFromVec_<int,T>( v, "4,4" )) ; 
    f->save("$FOLD") ;
    return 0 ;  
}




int main()
{
    int rc = 0 ; 
    //rc +=  test_ArrayFromVec<Compound>(); 
    rc +=  test_ArrayFromVec<Compound2>(); 
    //rc +=  test_ArrayFromVec<Compound3>(); 
    return rc ; 
}
