#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "NPU.hh"

template<typename T>
struct NP
{
    static bool ONLY_HEADER ;  
 
    static NP<T>* Load(const char* path); 
    static NP<T>* Load(const char* dir, const char* name); 

    NP(int ni=-1, int nj=-1, int nk=-1, int nl=-1, int nm=-1 ); 

    int load(const char* path);   
    int load(const char* dir, const char* name);   
    static std::string form_path(const char* dir, const char* name);   

    void save(const char* path);   
    void save(const char* dir, const char* name);   

    void savemeta();    
    void savemeta(const char* path);   
    void savemeta(const char* dir, const char* name);   

    void dump(int i0=-1, int i1=-1) const ;   
    std::string desc() const ; 

    T* values() ; 
    int num_values() const ; 
    int num_bytes() const ; 

    std::vector<T> data ; 
    std::vector<int> shape ; 
    std::string lpath ; 
};

template<typename T> T*  NP<T>::values() { return data.data() ;  } 
template<typename T> int NP<T>::num_bytes() const { return data.size()*sizeof(T)  ;  }
template<typename T> int NP<T>::num_values() const { return data.size() ;  }

template<typename T> bool NP<T>::ONLY_HEADER = false ; 


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
    int rc = a->load(path) ; 
    return rc == 0 ? a  : NULL ; 
}

template<typename T>
NP<T>* NP<T>::Load(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    return Load(path.c_str());
}

template<typename T>
std::string NP<T>::form_path(const char* dir, const char* name)
{
    std::stringstream ss ; 
    ss << dir << "/" << name ; 
    return ss.str(); 
}

template<typename T>
int NP<T>::load(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    return load(path.c_str()); 
}


template<typename T>
int NP<T>::load(const char* path)
{
    lpath = path ;  // loadpath 

    std::ifstream fp(path, std::ios::in|std::ios::binary);
    if(fp.fail())
    {
        std::cerr << "Failed to load from path " << path << std::endl ; 
        return 1 ; 
    }

    // formerly read an arbitrary initial buffer size, 
    // now reading up to first newline, which marks the 
    // end of the header, then adding the newline to the 
    // header string for neatness  

    std::string header ; 
    std::getline(fp, header );   
    header += '\n' ; 

#ifdef NP_DEBUG
    std::cout << "NP::load " << path << std::endl ; 
    std::cout << header << std::endl ; 
    if(ONLY_HEADER) std::cout << "ONLY_HEADER" << std::endl ; 
#endif

    shape.clear(); 
    int rc = NPU::parse_header<T>( shape, header ) ; 
    assert( rc == 0 ) ; 

    // parsing of the header gives the shape of the
    // data, so together with the size of the type
    // know how many bytes can read from the remainder of the stream
    // following the header

    if(ONLY_HEADER == false)
    {
        NPS sh(shape) ; 

        size_t total_items = sh.size() ;  
        size_t total_bytes = total_items*sizeof(T) ; 

        data.resize(total_items);

        fp.read(reinterpret_cast<char*>(&data[0]), total_bytes );
    }
    return 0 ; 
}

template<typename T>
void NP<T>::save(const char* path)
{
    NPS sh(shape) ; 
    int sz = sh.size(); 

    std::string hdr = NPU::make_header<T>( shape ) ; 

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << hdr ; 

    if(ONLY_HEADER == false)
    {
        assert( sz == data.size() ); 
        stream.write(reinterpret_cast<const char*>(data.data()), sizeof(T)*sz);
    }    


#ifdef NP_DEBUG
    std::cout << hdr << std::endl ; 
    std::cout << " writing " << path << std::endl ; 
    if(ONLY_HEADER) std::cout << "ONLY_HEADER" << std::endl ; 
#endif
}
template<typename T>
void NP<T>::save(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    save(path.c_str()); 
}



template<typename T>
void NP<T>::savemeta(const char* path)
{
    NPS sh(shape) ; 
    int sz = sh.size(); 

    std::string json = NPU::make_metadata<T>( shape ) ; 

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << json ; 
}

template<typename T>
void NP<T>::savemeta(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    savemeta(path.c_str()); 
}

template<typename T>
void NP<T>::savemeta()
{
    assert( lpath.empty() == false ); 
    assert( U::EndsWith(lpath.c_str(), ".npy" ) ); 

    std::string path = U::ChangeExt(lpath.c_str(), ".npy", ".npj"); 
    std::cout << "NP::savemeta to " << path << std::endl  ; 

    savemeta(path.c_str()); 
}






template<typename T>
void NP<T>::dump(int i0_, int i1_) const 
{
    int ni = NPS::ni_(shape) ;
    int nj = NPS::nj_(shape) ;
    int nk = NPS::nk_(shape) ;

    int i0 = i0_ == -1 ? 0 : i0_ ;  
    int i1 = i1_ == -1 ? std::min(ni, 10) : i1_ ;  

    std::cout 
       << " array dimensions " 
       << " ni " << ni 
       << " nj " << nj 
       << " nk " << nk
       << " item range i0:i1 "
       << " i0 " << i0 
       << " i1 " << i1 
       << std::endl 
       ;  

    if(ONLY_HEADER == true)
    {
        std::cout << "ONLY_HEADER" << std::endl ;   
    } 
    else
    { 
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

}

