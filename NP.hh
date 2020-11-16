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

**/

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
    std::string _net_hdr ; 

    // _net_hdr related 
    unsigned nh_item_size(unsigned index) const ;     
    std::string network_hdr() const ; 

    bool decode_net_header() ; // also resizes buffers ready for reading in 
    void update_headers();     

    bool decode_arr_header() ; // sets shape based on arr header


};

/**
NP<T> operator<<
-------------------

Write array into output stream 

**/

template<typename T>
std::ostream& operator<<(std::ostream &os,  const NP<T>& a) 
{ 
    os << a.network_hdr() ; // hmm not using _net_hdr 
    os << a._hdr ; 
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
    is.read( (char*)a._net_hdr.data(), net_hdr::LENGTH ) ; 

    unsigned hdr_bytes_nh = a.nh_item_size(0); 
    unsigned arr_bytes_nh = a.nh_item_size(1); 
    unsigned meta_bytes_nh = a.nh_item_size(2);  

    std::string hdr ; 
    std::getline( is, hdr );  
    hdr += '\n' ;  // getline consumes newline ending header but does not return it 

    unsigned hdr_bytes_h = hdr.length() ; 
    assert( hdr_bytes_h == hdr_bytes_nh ); 

    a.shape.clear();   // hmm note that only the shape is used from the header
    int rc = NPU::parse_header<T>( a.shape, hdr ) ; 
    assert( rc == 0 ) ; 

    NPS sh(a.shape) ; 
    unsigned arr_items_h = sh.size() ;  
    unsigned arr_bytes_h = arr_items_h*sizeof(T) ; 

    std::cout 
        << " hdr_bytes_nh " << hdr_bytes_nh 
        << " arr_bytes_nh " << arr_bytes_nh 
        << " meta_bytes_nh " << meta_bytes_nh 
        << " hdr_bytes_h " << hdr_bytes_h 
        << " arr_bytes_h " << arr_bytes_h 
        << " arr_items_h " << arr_items_h 
        << " shape " << NPS::desc(a.shape)
        << std::endl
        ;

    assert( arr_bytes_h == arr_bytes_nh ); 

    a.data.resize(arr_items_h);
    is.read(reinterpret_cast<char*>(&a.data[0]), arr_bytes_h );

    std::string meta(meta_bytes_nh, '\0' ); 
    is.read( (char*)meta.data(), meta_bytes_nh );
    a.meta = meta ; 
 
    //is.setstate(std::ios::failbit);
    return is;
}

template<typename T> std::string NP<T>::network_hdr() const 
{
    std::vector<unsigned> parts = { hdr_bytes(), arr_bytes(), meta_bytes() } ;  
    std::string net_hdr = net_hdr::pack( parts ); 
    return net_hdr ; 
}



/**
NP::update_headers
-------------------

The header descriptions of the object are updated.
Hmm : do this automatically in setters that change shape or metadata ?

**/

template<typename T> void NP<T>::update_headers()
{
    std::string net_hdr = network_hdr(); 
    _net_hdr.assign(net_hdr.data(), net_hdr.length()); 

    std::string hdr =  NPU::make_header<T>( shape ) ;
    _hdr.resize(hdr.length()); 
    _hdr.assign(hdr.data(), hdr.length()); 
}

/**
NP::decode_net_header
-----------------------

This must be called after reading the net header to 
resize buffers prior to reading them in.

NB assumes T is the correctly sized type for the content 
about to be received. Could do this more carefully by 
parsing the array hdr to extract type and shape 
prior to resizing the array.

**/
template<typename T> bool NP<T>::decode_net_header()  
{
    unsigned hdr_bytes_nh = nh_item_size(0); 
    unsigned arr_bytes_nh = nh_item_size(1); 
    unsigned meta_bytes_nh = nh_item_size(2);  

    std::cout 
        << "NP::decode_net_header"
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
template<typename T> unsigned NP<T>::nh_item_size(unsigned index) const { return net_hdr::unpack(_net_hdr, index); }  

/**
NP::decode_arr_header
-----------------------

Array header is parsed to set the array shape.

Note that currently only the shape is used from the header, 
other properties are currently ignored.

descr 
    endianness, type and element byte size 
fortran_order
    row/column major ?

Example in json form::

    {
        "descr": "<f4", 
        "fortran_order": false, 
        "shape": [10, 4] 
    }

**/

template<typename T> bool NP<T>::decode_arr_header()  
{
    shape.clear();  
    int rc = NPU::parse_header<T>( shape, _hdr ) ; 
    bool valid = rc == 0 ; 
    assert(valid) ; 
    return valid ; 
}



template<typename T> T*  NP<T>::values() { return data.data() ;  } 
template<typename T> unsigned NP<T>::num_values() const { return data.size() ;  }

template<typename T> char*  NP<T>::bytes() { return (char*)data.data() ;  } 
template<typename T> const char*  NP<T>::bytes() const { return (char*)data.data() ;  } 

template<typename T> unsigned NP<T>::hdr_bytes() const { return _hdr.length() ; }
template<typename T> unsigned NP<T>::arr_bytes() const { return data.size()*sizeof(T)  ;  }   // formerly num_bytes
template<typename T> unsigned NP<T>::meta_bytes() const { return meta.length() ; }

template<typename T> bool NP<T>::ONLY_HEADER = false ; 



template<typename T>
NP<T>::NP(int ni, int nj, int nk, int nl, int nm )
{
    NPS sh(shape); 
    sh.set_shape( ni, nj, nk, nl, nm ); 
    data.resize( sh.size() ) ; 
    std::fill( data.begin() , data.end(), T(0) ) ;     
    _hdr = NPU::make_header<T>( shape ); 
    _net_hdr.assign(net_hdr::LENGTH, '\0' ); 
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
       << " shape.size " << shape.size() 
       << " data.size " << data.size()
       << " meta.size " << meta.size() 
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

    std::cout 
        << "meta:[" 
        << std::endl
        << meta
        << std::endl
        << "]"
        << std::endl
        ; 

}

