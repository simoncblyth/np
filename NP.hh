#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "NPU.hh"

template<typename T>
struct NP
{
    static NP<T>* Load(const char* path); 

    NP(int ni=-1, int nj=-1, int nk=-1, int nl=-1, int nm=-1 ); 

    void load(const char* path);   
    void save(const char* path);   
    void dump(int i0, int i1) const ;   
    std::string desc() const ; 

    std::vector<T> data ; 
    std::vector<int> shape ; 
};

template<typename T>
NP<T>::NP(int ni, int nj, int nk, int nl, int nm )
{
    NPS sh(shape); 
    sh.set_shape( ni, nj, nk, nl, nm ); 
    data.resize( sh.size() ) ; 
    std::fill( data.begin() , data.end(), T(0) ) ;     
}

template<typename T>
std::string NP<T>::desc() const 
{
    std::stringstream ss ; 
    ss << "NP " << NPS::desc(shape) ;
    return ss.str(); 
}


template<typename T>
NP<T>* NP<T>::Load(const char* path)
{
    NP<T>* a = new NP<T>() ; 
    a->load(path) ; 
    return a ; 
}


template<typename T>
void NP<T>::load(const char* path)
{
    std::ifstream stream(path, std::ios::in|std::ios::binary);

    std::string header(128, ' '); 
    stream.read(&header[0], 128 ); 

#ifdef NP_DEBUG
    std::cout << "NP::load " << path << std::endl ; 
    std::cout << header << std::endl ; 
#endif

    shape.clear(); 
    int rc = NPU::parse_header<T>( shape, header ) ; 
    assert( rc == 0 ) ; 

    NPS sh(shape) ; 

    size_t total_items = sh.size() ;  
    size_t total_bytes = total_items*sizeof(T) ; 

    data.resize(total_items);

    stream.read(reinterpret_cast<char*>(&data[0]), total_bytes );
}

template<typename T>
void NP<T>::save(const char* path)
{
    NPS sh(shape) ; 
    int sz = sh.size(); 
    assert( sz == data.size() ); 

    std::string hdr = NPU::make_header<T>( shape ) ; 

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << hdr ; 
    stream.write(reinterpret_cast<const char*>(data.data()), sizeof(T)*sz);

#ifdef NP_DEBUG
    std::cout << hdr << std::endl ; 
    std::cout << " writing " << path << std::endl ; 
#endif
}

template<typename T>
void NP<T>::dump(int i0, int i1) const 
{
    int ni = NPS::ni_(shape) ;
    int nj = NPS::nj_(shape) ;
    int nk = NPS::nk_(shape) ;
    std::cout 
       << " ni " << ni 
       << " nj " << nj 
       << " nk " << nk
       << std::endl ;  


    for(int i=i0 ; i < i1 ; i++){
        std::cout << "[" << i  << "]" << std::endl ;  
        for(int j=0 ; j < nj ; j++){
            for(int k=0 ; k < nk ; k++)
            {
                int index = i*nj*nk + j*nk + k ; 
                std::cout << " " << std::fixed << data[index] ;      
            }
            //std::cout << std::endl ; 
        }
        std::cout << std::endl ; 
    }
}

