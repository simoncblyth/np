#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "NPU.hh"
#include "net_hdr.hh"

/**
NP
==

Lightweight version of Opticks NPY that adds asyncio transport capabilities
based on boost::asio.

TODO: further reduce duplication between 

1. file read/write 
2. stream read/write 
3. non-stream read/write 

The templating is not convenient for transport because you 
dont know the type until parsing the hdr. 
Plus most of the class does not depend on the type... so 
perhaps try to have some templated methods rather than 
a templated class ?

**/

template<typename T>
struct NP
{
    NP(int ni=-1, int nj=-1, int nk=-1, int nl=-1, int nm=-1 ); 

    static NP<T>* Load(const char* path); 
    static NP<T>* Load(const char* dir, const char* name); 

    void fill(T value); 
    void fillIndexFlat(T offset=0); 
    T*   values() ; 

    int load(const char* path);   
    int load(const char* dir, const char* name);   
    static std::string form_path(const char* dir, const char* name);   

    void save(const char* path);   
    void save(const char* dir, const char* name);   

    void save_jsonhdr();    
    void save_jsonhdr(const char* path);   
    void save_jsonhdr(const char* dir, const char* name);   

    void dump(int i0=-1, int i1=-1) const ;   
    std::string desc() const ; 

    char*       bytes();  
    const char* bytes() const ;  

    unsigned num_values() const ; 
    unsigned arr_bytes() const ;   // formerly num_bytes
    unsigned hdr_bytes() const ;  
    unsigned meta_bytes() const ;
  
    // primary data members 
    std::vector<T>   data ; 
    std::vector<int> shape ; 
    std::string      meta ; 

    // transient
    std::string lpath ; 

    // headers used for transport 
    std::string _hdr ; 
    std::string _prefix ; 

    // results from parsing _hdr
    int  size ;    // number of elements from shape
    char uifc ;    // element type code 
    int  ebyte ;   // element bytes  


    void        update_headers();     

    std::string make_header() const ; 
    bool        decode_header() ; // sets shape based on arr header

    std::string make_prefix() const ; 
    bool        decode_prefix() ; // also resizes buffers ready for reading in 
    unsigned    prefix_size(unsigned index) const ;     

    std::string make_jsonhdr() const ;


};

/**
NP<T> operator<<
-------------------

Write array into output stream 

**/

template<typename T>
std::ostream& operator<<(std::ostream &os,  const NP<T>& a) 
{ 
    os << a.make_prefix() ; 
    os << a.make_header() ; 
    os.write(a.bytes(), a.arr_bytes());
    os << a.meta ; 
    return os ; 
}

/**
NP<T> operator>>
------------------

Direct input stream into NP array

**/

template<typename T>
std::istream& operator>>(std::istream& is, NP<T>& a)      // NB this is NOT a struct member function
{
    is.read( (char*)a._prefix.data(), net_hdr::LENGTH ) ; 

    unsigned hdr_bytes_nh = a.prefix_size(0); 
    unsigned arr_bytes_nh = a.prefix_size(1); 
    unsigned meta_bytes_nh = a.prefix_size(2);  

    std::cout 
        << " hdr_bytes_nh " << hdr_bytes_nh 
        << " arr_bytes_nh " << arr_bytes_nh 
        << " meta_bytes_nh " << meta_bytes_nh 
        << std::endl
        ;

    std::getline( is, a._hdr );  
    a._hdr += '\n' ;           // getline consumes newline ending header but does not return it 

    assert( hdr_bytes_nh == a._hdr.length() ); 

    a.decode_header();   // resizes data array 

    assert( a.arr_bytes() == arr_bytes_nh ); 
    is.read(a.bytes(), a.arr_bytes() );

    a.meta.resize(meta_bytes_nh);
    is.read( (char*)a.meta.data(), meta_bytes_nh );
 
    //is.setstate(std::ios::failbit);
    return is;
}

/**
NP::update_headers
-------------------

The header descriptions of the object are updated.
Hmm : do this automatically in setters that change shape or metadata ?
OR just invoke this before streaming  

**/

template<typename T> void NP<T>::update_headers()
{
    std::string net_hdr = make_prefix(); 
    _prefix.assign(net_hdr.data(), net_hdr.length()); 

    std::string hdr =  make_header(); 
    _hdr.resize(hdr.length()); 
    _hdr.assign(hdr.data(), hdr.length()); 

    assert( num_values() == data.size() ); 
}


template<typename T> std::string NP<T>::make_header() const 
{
    std::string hdr =  NPU::make_header<T>( shape ) ;
    return hdr ; 
}
template<typename T> std::string NP<T>::make_prefix() const 
{
    std::vector<unsigned> parts = { hdr_bytes(), arr_bytes(), meta_bytes() } ;  
    std::string net_hdr = net_hdr::pack( parts ); 
    return net_hdr ; 
}
template<typename T> std::string NP<T>::make_jsonhdr() const 
{
    std::string json = NPU::make_jsonhdr<T>( shape ) ; 
    return json ; 
}  



/**
NP::decode_prefix
-----------------------

This must be called after reading the net header to 
resize buffers prior to reading them in.

NB assumes T is the correctly sized type for the content 
about to be received. Could do this more carefully by 
parsing the array hdr to extract type and shape 
prior to resizing the array.

TODO: avoid relying on T, the type info is in the header


**/
template<typename T> bool NP<T>::decode_prefix()  
{
    unsigned hdr_bytes_nh = prefix_size(0); 
    unsigned arr_bytes_nh = prefix_size(1); 
    unsigned meta_bytes_nh = prefix_size(2);  

    std::cout 
        << "NP::decode_prefix"
        << " hdr_bytes_nh " << hdr_bytes_nh
        << " arr_bytes_nh " << arr_bytes_nh
        << " meta_bytes_nh " << meta_bytes_nh
        << std::endl
        ;

    bool valid = hdr_bytes_nh > 0 ; 
    if(valid)
    {
        _hdr.resize(hdr_bytes_nh);
        data.resize(arr_bytes_nh/sizeof(T)); 
        meta.resize(meta_bytes_nh);
    }
    return valid ; 
}
template<typename T> unsigned NP<T>::prefix_size(unsigned index) const { return net_hdr::unpack(_prefix, index); }  

/**
NP::decode_header
-----------------------

Array header _hdr is parsed setting the below and data is resized.

shape
    vector of int 
uifc
    element type code
ebyte 
    element number of bytes
size
    number of elements 


Decoding the header gives the shape of the
data, so together with the size of the type
know how many bytes can read from the remainder of the stream
following the header.

**/

template<typename T> bool NP<T>::decode_header()  
{
    shape.clear();  
    NPU::parse_header( shape, uifc, ebyte, _hdr ) ; 
    size = NPS::size(shape); 
    data.resize(size) ;  // assumes element type T is correctly sized for the data  
    return true  ; 
}

// former approach assumed data is already sized : but shape comes first 

template<typename T> unsigned NP<T>::hdr_bytes() const { return _hdr.length() ; }
template<typename T> unsigned NP<T>::num_values() const { return NPS::size(shape) ;  }
template<typename T> unsigned NP<T>::arr_bytes()  const { return NPS::size(shape)*sizeof(T) ; }
template<typename T> unsigned NP<T>::meta_bytes() const { return meta.length() ; }


template<typename T> T*  NP<T>::values() { return data.data() ;  } 
template<typename T> char*  NP<T>::bytes() { return (char*)data.data() ;  } 
template<typename T> const char*  NP<T>::bytes() const { return (char*)data.data() ;  } 



template<typename T>
NP<T>::NP(int ni, int nj, int nk, int nl, int nm )
    :
    size(NPS::set_shape(shape, ni,nj,nk,nl,nm )),
    uifc(Desc<T>::code),
    ebyte(sizeof(T))
{
    data.resize( size ) ; 
    fill( T(0) ) ;     

    _prefix.assign(net_hdr::LENGTH, '\0' ); 
    _hdr = make_header(); 
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
    ss << "NP " 
       << NPS::desc(shape) 
       << " size " << size 
       << " uifc " << uifc 
       << " ebyte " << ebyte 
       << " shape.size " << shape.size() 
       << " data.size " << data.size()
       << " meta.size " << meta.size() 
       << " _hdr " << _hdr 
       ;
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

/**
NP::load
----------

Formerly read an arbitrary initial buffer size, 
now reading up to first newline, which marks the 
end of the header, then adding the newline to the 
header string for correctness as getline consumes the 
newline from the stream without returning it. 

**/

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

    std::getline(fp, _hdr );   
    _hdr += '\n' ; 

    decode_header();  // resizes data as necessary, assuming T is correct 

    fp.read(bytes(), arr_bytes() );

    return 0 ; 
}

template<typename T>
void NP<T>::save(const char* path)
{
    update_headers(); 
    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << _hdr ; 
    stream.write( bytes(), arr_bytes() );
}

template<typename T>
void NP<T>::save(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    save(path.c_str()); 
}

template<typename T>
void NP<T>::save_jsonhdr(const char* path)
{
    std::string json = make_jsonhdr(); 
    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << json ; 
}

template<typename T>
void NP<T>::save_jsonhdr(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    save_jsonhdr(path.c_str()); 
}

template<typename T>
void NP<T>::save_jsonhdr()
{
    assert( lpath.empty() == false ); 
    assert( U::EndsWith(lpath.c_str(), ".npy" ) ); 

    std::string path = U::ChangeExt(lpath.c_str(), ".npy", ".npj"); 
    std::cout << "NP::save_jsonhdr to " << path << std::endl  ; 

    save_jsonhdr(path.c_str()); 
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
       << desc() 
       << std::endl 
       << " array dimensions " 
       << " ni " << ni 
       << " nj " << nj 
       << " nk " << nk
       << " item range i0:i1 "
       << " i0 " << i0 
       << " i1 " << i1 
       << std::endl 
       ;  

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


    std::cout 
        << "meta:[" 
        << std::endl
        << meta
        << std::endl
        << "]"
        << std::endl
        ; 

}

