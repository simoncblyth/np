// ~/np/tests/NP_ArrayFromVec_test.sh


#include "NPX.h"

struct Demo
{
    int idx ; 
    int pad ; 
    double a ; 
    double b ; 
    double c ; 
};

inline std::ostream& operator<<(std::ostream& os, const Demo& v)
{
    int w = 10 ; 
    os   
       << "("  
       << std::setw(w) << v.idx  
       << ";"  
       << std::setw(w) << v.a 
       << ","  
       << std::setw(w) << v.b  
       << ","  
       << std::setw(w) << v.c  
       << ") "  
       ;        
    return os;  
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<Demo>& v)
{
    os << std::endl ; 
    for(unsigned i=0 ; i < v.size() ; i++) os << v[i] << std::endl ; 
    os << std::endl ; 
    return os;  
}


inline std::ostream& operator<<(std::ostream& os, const std::map<int, Demo>& m)
{
    typename std::map<int,Demo>::const_iterator it = m.begin()  ;
    os << std::endl ; 
    for(unsigned i=0 ; i < m.size() ; i++) 
    {
        os << std::setw(10) << it->first << " : " << it->second << std::endl  ; 
        std::advance(it, 1); 
    }
    os << std::endl ; 
    return os;  
}



const char* FOLD = getenv("FOLD"); 


void test_PopulateVec(std::vector<Demo>& dd )
{
    Demo d0 = { 0,0, 10. , 20. , 30.  }; 
    Demo d1 = { 1,0, 100., 200., 300. }; 
    Demo d2 = { 2,0, 1000., 2000., 3000. }; 
    
    dd.push_back(d0);    
    dd.push_back(d1);    
    dd.push_back(d2);    

    std::cout << "test_PopulateVec  dd " << dd ; 
}

void test_PopulateMap(std::map<int,Demo>& mm )
{
    Demo d0 = { 0,0, 10. , 20. , 30.  }; 
    Demo d1 = { 1,0, 100., 200., 300. }; 
    Demo d2 = { 2,0, 1000., 2000., 3000. }; 

    mm[100] = d0 ; 
    mm[101] = d1 ; 
    mm[102] = d2 ; 

    std::cout << "test_PopulateMap  mm " << mm ; 
}





void test_MapFromVec(const std::vector<Demo>& dd)
{
    std::cout << "test_MapFromVec" << std::endl ; 
    std::map<int, Demo> mm ; 
    NPX::MapFromVec(mm, dd) ; 
    std::cout << " mm " << mm ; 
}
void test_ArrayFromVec_VecFromArray(const std::vector<Demo>& dd)
{
    std::cout << "test_ArrayFromVec_VecFromArray" << std::endl ; 

    NP* a = NPX::ArrayFromVec<double, Demo>( dd, 2, 2) ; 
    a->save(FOLD, "a.npy") ; 

    NP* b = NPX::ArrayFromVec<double, Demo>( dd ) ; 
    b->save(FOLD, "b.npy") ; 

    std::vector<Demo> a_dd ; 
    NPX::VecFromArray( a_dd, a ); 
    std::cout << " a_dd " << a_dd ; 

    std::vector<Demo> b_dd ; 
    NPX::VecFromArray( b_dd, b ); 
    std::cout << " b_dd " << b_dd ; 
}


void test_ArrayFromMap_MapFromArray(const std::map<int, Demo>& mm)
{
    NP* a = NPX::ArrayFromMap<double,Demo>(mm, true); 

    const char* name = "mfa.npy" ; 
    a->save(FOLD,name) ; 
    NP* b = NP::Load(FOLD,name);  

    std::map<int, Demo> nn ; 
    NPX::MapFromArray(nn, b ); 

    std::cout << " test_ArrayFromMap_MapFromArray nn " << nn << std::endl ;
}



int main(int argc, char** argv)
{
    std::vector<Demo> v ; 
    test_PopulateVec(v); 
    test_MapFromVec(v); 
    test_ArrayFromVec_VecFromArray(v); 

    std::map<int, Demo> m ; 
    test_PopulateMap(m); 
    test_ArrayFromMap_MapFromArray(m); 

    return 0 ; 
}  
