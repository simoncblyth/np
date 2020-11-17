#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "NPU.hh"
#include "net_hdr.hh"

/**
NB : non-template experimental variant of NP 
=======================================================

This aims to replace NP.

Templating is not convenient for transport because you 
dont know the type until parsing the hdr. 
Plus most methods do not depend on the type... so 
try to have some templated methods rather than 
a templated struct ?

**/

struct NB
{
    NB(const char* dtype_="<f4", int ni=-1, int nj=-1, int nk=-1, int nl=-1, int nm=-1 ); 

    static NB* Load(const char* path); 
    static NB* Load(const char* dir, const char* name); 

    template<typename T> T*       values() ; 
    template<typename T> const T* values() const  ; 
    template<typename T> void fill(T value); 
    template<typename T> void fillIndexFlat(T offset=0); 
    template<typename T> void dump(int i0=-1, int i1=-1) const ;   


    int load(const char* path);   
    int load(const char* dir, const char* name);   
    static std::string form_path(const char* dir, const char* name);   

    void save(const char* path);   
    void save(const char* dir, const char* name);   

    void save_jsonhdr();    
    void save_jsonhdr(const char* path);   
    void save_jsonhdr(const char* dir, const char* name);   

    std::string desc() const ; 

    char*       bytes();  
    const char* bytes() const ;  

    unsigned num_values() const ; 
    unsigned arr_bytes() const ;   // formerly num_bytes
    unsigned hdr_bytes() const ;  
    unsigned meta_bytes() const ;
  
    // primary data members 
    std::vector<char> data ; 
    std::vector<int>  shape ; 
    std::string       meta ; 

    // transient
    std::string lpath ; 

    // headers used for transport 
    std::string _hdr ; 
    std::string _prefix ; 

    // results from parsing _hdr
    const char* dtype ; 
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
operator<< NB : NOT a member function
---------------------------------------

Write array into output stream 

**/

std::ostream& operator<<(std::ostream &os,  const NB& a) 
{ 
    os << a.make_prefix() ; 
    os << a.make_header() ; 
    os.write(a.bytes(), a.arr_bytes());
    os << a.meta ; 
    return os ; 
}

/**
operator>> NB : NOT a member function
---------------------------------------

Direct input stream into NB array

**/

std::istream& operator>>(std::istream& is, NB& a)     
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
NB::update_headers
-------------------

The header descriptions of the object are updated.
Hmm : do this automatically in setters that change shape or metadata ?
OR just invoke this before streaming  

**/

void NB::update_headers()
{
    std::string net_hdr = make_prefix(); 
    _prefix.assign(net_hdr.data(), net_hdr.length()); 

    std::string hdr =  make_header(); 
    _hdr.resize(hdr.length()); 
    _hdr.assign(hdr.data(), hdr.length()); 

    // assert( num_values() == data.size() );  //NO
}


std::string NB::make_header() const 
{
    std::string hdr =  NPU::_make_header( shape, dtype ) ;
    return hdr ; 
}
std::string NB::make_prefix() const 
{
    std::vector<unsigned> parts = { hdr_bytes(), arr_bytes(), meta_bytes() } ;  
    std::string net_hdr = net_hdr::pack( parts ); 
    return net_hdr ; 
}
std::string NB::make_jsonhdr() const 
{
    std::string json = NPU::_make_jsonhdr( shape, dtype ) ; 
    return json ; 
}  



/**
NB::decode_prefix
-----------------------

This must be called after reading the net header to 
resize buffers prior to reading them in.

NB assumes T is the correctly sized type for the content 
about to be received. Could do this more carefully by 
parsing the array hdr to extract type and shape 
prior to resizing the array.

TODO: avoid relying on T, the type info is in the header


**/
bool NB::decode_prefix()  
{
    unsigned hdr_bytes_nh = prefix_size(0); 
    unsigned arr_bytes_nh = prefix_size(1); 
    unsigned meta_bytes_nh = prefix_size(2);  

    std::cout 
        << "NB::decode_prefix"
        << " hdr_bytes_nh " << hdr_bytes_nh
        << " arr_bytes_nh " << arr_bytes_nh
        << " meta_bytes_nh " << meta_bytes_nh
        << std::endl
        ;

    bool valid = hdr_bytes_nh > 0 ; 
    if(valid)
    {
        _hdr.resize(hdr_bytes_nh);
        data.resize(arr_bytes_nh);   // data now chars 
        meta.resize(meta_bytes_nh);
    }
    return valid ; 
}
unsigned NB::prefix_size(unsigned index) const { return net_hdr::unpack(_prefix, index); }  

/**
NB::decode_header
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

bool NB::decode_header()  
{
    shape.clear();  
    NPU::parse_header( shape, uifc, ebyte, _hdr ) ; 
    size = NPS::size(shape); 
    data.resize(size*ebyte) ; // data is now just char 
    return true  ; 
}

// former approach assumed data is already sized : but shape comes first 

unsigned NB::hdr_bytes() const { return _hdr.length() ; }
unsigned NB::num_values() const { return NPS::size(shape) ;  }
unsigned NB::arr_bytes()  const { return NPS::size(shape)*ebyte ; }
unsigned NB::meta_bytes() const { return meta.length() ; }



char*        NB::bytes() { return (char*)data.data() ;  } 
const char*  NB::bytes() const { return (char*)data.data() ;  } 



NB::NB(const char* dtype_, int ni, int nj, int nk, int nl, int nm )
    :
    dtype(strdup(dtype_)),
    size(NPS::set_shape(shape, ni,nj,nk,nl,nm )),
    uifc(NPU::_dtype_uifc(dtype)),
    ebyte(NPU::_dtype_ebyte(dtype))
{
    data.resize( size*ebyte ) ; 
    std::fill( data.begin(), data.end(), 0 );     

    _prefix.assign(net_hdr::LENGTH, '\0' ); 
    _hdr = make_header(); 
}




template<typename T> T*  NB::values() { return (T*)data.data() ;  } 

template<typename T> void NB::fill(T value)
{
    T* vv = values<T>(); 
    for(unsigned i=0 ; i < size ; i++) *(vv+i) = value ; 
}

template<typename T> void NB::fillIndexFlat(T offset)
{
    T* vv = values<T>(); 
    for(unsigned i=0 ; i < size ; i++) *(vv+i) = T(i) + offset ; 
}


std::string NB::desc() const 
{
    std::stringstream ss ; 
    ss << "NB " 
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

NB* NB::Load(const char* path)
{
    NB* a = new NB() ; 
    int rc = a->load(path) ; 
    return rc == 0 ? a  : NULL ; 
}

NB* NB::Load(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    return Load(path.c_str());
}

std::string NB::form_path(const char* dir, const char* name)
{
    std::stringstream ss ; 
    ss << dir << "/" << name ; 
    return ss.str(); 
}

int NB::load(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    return load(path.c_str()); 
}

/**
NB::load
----------

Formerly read an arbitrary initial buffer size, 
now reading up to first newline, which marks the 
end of the header, then adding the newline to the 
header string for correctness as getline consumes the 
newline from the stream without returning it. 

**/

int NB::load(const char* path)
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

    decode_header(); 

    fp.read(bytes(), arr_bytes() );

    return 0 ; 
}

void NB::save(const char* path)
{
    update_headers(); 
    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << _hdr ; 
    stream.write( bytes(), arr_bytes() );
}

void NB::save(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    save(path.c_str()); 
}

void NB::save_jsonhdr(const char* path)
{
    std::string json = make_jsonhdr(); 
    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << json ; 
}

void NB::save_jsonhdr(const char* dir, const char* name)
{
    std::string path = form_path(dir, name); 
    save_jsonhdr(path.c_str()); 
}

void NB::save_jsonhdr()
{
    assert( lpath.empty() == false ); 
    assert( U::EndsWith(lpath.c_str(), ".npy" ) ); 

    std::string path = U::ChangeExt(lpath.c_str(), ".npy", ".npj"); 
    std::cout << "NB::save_jsonhdr to " << path << std::endl  ; 

    save_jsonhdr(path.c_str()); 
}




template <typename T>
void NB::dump(int i0_, int i1_) const 
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

    const T* vv = values<T>(); 

    for(int i=i0 ; i < i1 ; i++){
        std::cout << "[" << i  << "]" << std::endl ;  
        for(int j=0 ; j < nj ; j++){
            for(int k=0 ; k < nk ; k++)
            {
                int index = i*nj*nk + j*nk + k ; 
                std::cout << " " << std::fixed << *(vv + index)  ;      
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


template const float* NB::values() const ;
//template float*       NB::values<float>() ;


