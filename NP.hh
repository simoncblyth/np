#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "NPU.hh"
#include "net_hdr.hh"

template<typename T>
struct NP
{
    static bool ONLY_HEADER ;  
 
    static NP<T>* Load(const char* path); 
    static NP<T>* Load(const char* dir, const char* name); 

    NP(int ni=-1, int nj=-1, int nk=-1, int nl=-1, int nm=-1 ); 

    void fill(T value); 
    void fillIndexFlat(T offset=0); 

    int load(const char* path);   
    int load(const char* dir, const char* name);   
    static std::string form_path(const char* dir, const char* name);   

    void save(const char* path);   
    void save(const char* dir, const char* name);   

    void savejsonhdr();    
    void savejsonhdr(const char* path);   
    void savejsonhdr(const char* dir, const char* name);   

    void dump(int i0=-1, int i1=-1) const ;   
    std::string desc() const ; 

    T* values() ; 
    char* bytes();  
    const char* bytes() const ;  

    unsigned num_values() const ; 

    unsigned num_bytes() const ;   // just the array, not the header 
    unsigned hdr_bytes() const ;  
    unsigned meta_bytes() const ;  
    std::string network_hdr() const ; 

    std::vector<T> data ; 
    std::vector<int> shape ; 
    std::string lpath ; 

    std::string hdr ; 
    std::string meta ; 
};


template<typename T>
std::ostream& operator<<(std::ostream &os,  const NP<T>& a) 
{ 
    os << a.network_hdr() ; 
    os << a.hdr ; 
    os.write(a.bytes(), a.num_bytes());
    os << a.meta ; 

    return os ; 
}

template<typename T>
std::istream& operator>>(std::istream& is, NP<T>& a)
{
    std::string nethdr(2*4, '\0') ;  
    is.read( (char*)nethdr.data(), 8 ) ; 

    std::vector<unsigned> items ; 
    net_hdr::unpack(nethdr, items ); 
    assert( items.size() == 2 );     

    unsigned hdr_arr_bytes = items[0]; 
    unsigned meta_bytes = items[1]; 

    std::string hdr ; 
    std::getline(is, hdr );  
    hdr += '\n' ;  // getline consumes newline ending header but does not return it 
    unsigned hdr_bytes = hdr.length(); 
    unsigned arr_bytes0 = hdr_arr_bytes - hdr_bytes ; 

    a.shape.clear(); 
    int rc = NPU::parse_header<T>( a.shape, hdr ) ; 
    assert( rc == 0 ) ; 

    NPS sh(a.shape) ; 
    unsigned arr_items = sh.size() ;  
    unsigned arr_bytes = arr_items*sizeof(T) ; 

    std::cout 
        << " hdr_arr_bytes(items[0]) " << hdr_arr_bytes 
        << " meta_bytes(items[1]) " << meta_bytes 
        << " hdr_bytes " << hdr_bytes 
        << " arr_bytes0 " << arr_bytes0 
        << " arr_bytes " << arr_bytes 
        << " arr_items " << arr_items 
        << " shape " << NPS::desc(a.shape)
        << std::endl
        ;

    assert( arr_bytes == arr_bytes0 ); 

    a.data.resize(arr_items);
    is.read(reinterpret_cast<char*>(&a.data[0]), arr_bytes );

    std::string meta(meta_bytes, '\0' ); 
    is.read( (char*)meta.data(), meta_bytes );
    a.meta = meta ; 
 
    //is.setstate(std::ios::failbit);
    return is;
}





template<typename T> T*  NP<T>::values() { return data.data() ;  } 
template<typename T> unsigned NP<T>::num_values() const { return data.size() ;  }

template<typename T> char*  NP<T>::bytes() { return (char*)data.data() ;  } 
template<typename T> const char*  NP<T>::bytes() const { return (char*)data.data() ;  } 

template<typename T> unsigned NP<T>::num_bytes() const { return data.size()*sizeof(T)  ;  }
template<typename T> unsigned NP<T>::hdr_bytes() const { return hdr.length() ; }
template<typename T> unsigned NP<T>::meta_bytes() const { return meta.length() ; }


template<typename T> bool NP<T>::ONLY_HEADER = false ; 

template<typename T> std::string NP<T>::network_hdr() const 
{
    std::vector<unsigned> parts = { hdr_bytes() + num_bytes(), meta_bytes() } ;  
    std::string net_hdr = net_hdr::pack( parts ); 
    return net_hdr ; 
}


template<typename T>
NP<T>::NP(int ni, int nj, int nk, int nl, int nm )
{
    NPS sh(shape); 
    sh.set_shape( ni, nj, nk, nl, nm ); 
    data.resize( sh.size() ) ; 
    std::fill( data.begin() , data.end(), T(0) ) ;     
    hdr = NPU::make_header<T>( shape ); 
}

template<typename T>
void NP<T>::fill(T value)
{
    std::fill( data.begin() , data.end(), value ) ;     
}

template<typename T>
void NP<T>::fillIndexFlat(T offset)
{
    for(unsigned i=0 ; i < data.size() ; i++) data[i] = T(i) + offset ; 
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
void NP<T>::savejsonhdr(const char* path)
{
    NPS sh(shape) ; 
    int sz = sh.size(); 

    std::string json = NPU::make_jsonhdr<T>( shape ) ; 

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << json ; 
}

template<typename T>
void NP<T>::savejsonhdr(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    savejsonhdr(path.c_str()); 
}

template<typename T>
void NP<T>::savejsonhdr()
{
    assert( lpath.empty() == false ); 
    assert( U::EndsWith(lpath.c_str(), ".npy" ) ); 

    std::string path = U::ChangeExt(lpath.c_str(), ".npy", ".npj"); 
    std::cout << "NP::savejsonhdr to " << path << std::endl  ; 

    savejsonhdr(path.c_str()); 
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

