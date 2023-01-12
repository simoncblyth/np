#pragma once
/**
NPX.h : NP.hh related extras such as static converters
=========================================================


**/

#include "NP.hh"

struct NPX
{


    template<typename S>
    static NP* ArrayFromDiscoMap( const std::map<int, S>& m ); 

    template<typename S>
    static void DiscoMapFromArray( std::map<int, S>& m, const NP* a ); 

    template<typename S>
    static std::string DescDiscoMap( const std::map<int, S>& m ); 

}; 


/**
NPX::ArrayFromDiscoMap
------------------------

How to handle maps with discontiguous keys ? 
For S:int and int keys can simply save as array of shape (10,2) 

  idx  key val 
   0    0   0
   1    1   1
   2    2   2
   3    3   0
   4    4   1
   5    5   2
   6   10   3
   7   11   3
   8   12   3
   9   13   3

**/

template<typename S>
inline NP* NPX::ArrayFromDiscoMap( const std::map<int, S>& m )
{
    return nullptr ;    
}
template<>
inline NP* NPX::ArrayFromDiscoMap( const std::map<int,int>& m )
{
    int ni = m.size() ; 
    int nj = 2 ; 
    NP* a = NP::Make<int>(ni, nj) ;  
    int* aa = a->values<int>(); 

    typedef std::map<int,int> MII ; 
    MII::const_iterator it = m.begin(); 

    for(int i=0 ; i < ni ; i++)
    {
        aa[i*nj+0] = it->first ;  
        aa[i*nj+1] = it->second ;  
        it++ ; 
    }
    return a ; 
}


template<typename S>
inline void NPX::DiscoMapFromArray( std::map<int, S>& m, const NP* a ){}

template<>
inline void NPX::DiscoMapFromArray( std::map<int, int>& m, const NP* a )
{
    assert( a && a->uifc == 'i' && a->ebyte == 4 && a->shape.size() == 2 ); 
    int ni = a->shape[0] ; 
    int nj = a->shape[1] ;
    assert( nj == 2 );  

    const int* aa = a->cvalues<int>(); 
    for(int i=0 ; i < ni ; i++)
    {
        int k = aa[i*nj+0] ;  
        int v = aa[i*nj+1] ;  
        m[k] = v ;  
    }
}

template<typename S>
inline std::string NPX::DescDiscoMap( const std::map<int, S>& m )
{
    std::stringstream ss ; 
    ss << "NPX::DescDiscoMap" << std::endl << " m.size " << m.size() ; 
    std::string s = ss.str();    
    return s ; 
}

template<>
inline std::string NPX::DescDiscoMap( const std::map<int,int>& m )
{
    int ni = m.size() ; 
    typedef std::map<int,int> MII ; 
    MII::const_iterator it = m.begin(); 
    std::stringstream ss ; 
    ss << "NPX::DescDiscoMap" << std::endl << " m.size " << ni << std::endl ; 
    for(int i=0 ; i < ni ; i++)
    {
        ss << "( " << it->first << " : " << it->second << " ) " << std::endl ;   
        it++ ; 
    }
    std::string s = ss.str();    
    return s ; 
}



