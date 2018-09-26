
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <complex>


union u16c2_t 
{
   uint16_t u16 ; 
   char     c[2] ;  
}; 

struct Endian
{
    static const char LITTLE ; 
    static const char BIG ; 
    static char detect(); 
};

const char Endian::LITTLE = '<' ; 
const char Endian::BIG = '>' ; 

char Endian::detect()
{
    u16c2_t one ;
    one.u16 = 1 ;   // use the union to detect endianness and do the split 
 
    bool little_endian = one.c[0] == 1 && one.c[1] == 0 ; 
    bool big_endian = one.c[0] == 0 && one.c[1] == 1 ; 
    assert( little_endian ^ big_endian ); 

    return little_endian ? LITTLE : BIG ;  
}


template<typename T>
struct Desc 
{
    static const char code ; 
    static std::string descr(); 
};

template<> const char Desc<float>::code = 'f' ; 
template<> const char Desc<double>::code = 'f' ; 

template<> const char Desc<char>::code = 'i' ; 
template<> const char Desc<short>::code = 'i' ; 
template<> const char Desc<int>::code = 'i' ; 
template<> const char Desc<long>::code = 'i' ; 
template<> const char Desc<long long>::code = 'i' ; 

template<> const char Desc<unsigned char>::code = 'u' ; 
template<> const char Desc<unsigned short>::code = 'u' ; 
template<> const char Desc<unsigned int>::code = 'u' ; 
template<> const char Desc<unsigned long>::code = 'u' ; 
template<> const char Desc<unsigned long long>::code = 'u' ; 

template<> const char Desc<std::complex<float> >::code = 'c' ; 
template<> const char Desc<std::complex<double> >::code = 'c' ; 


template<typename T>
std::string Desc<T>::descr()
{
    std::stringstream ss ; 
    ss 
       << Endian::detect()
       << code 
       << sizeof(T)        
       ;
    return ss.str(); 
}


struct NPS
{
    NPS(std::vector<int>& shape_ ) : shape(shape_) {}  ; 

    void set_shape(int ni, int nj=-1, int nk=-1, int nl=-1, int nm=-1)
    {
        if(ni > 0) shape.push_back(ni); 
        if(nj > 0) shape.push_back(nj); 
        if(nk > 0) shape.push_back(nk); 
        if(nl > 0) shape.push_back(nl); 
        if(nm > 0) shape.push_back(nm); 
    }

    static std::string desc(const std::vector<int>& shape)
    {
        std::stringstream ss ; 
        ss << "("  ; 
        for(int i=0 ; i < shape.size() ; i++) ss << shape[i] << ", " ; 
        ss << ")"  ; 
        return ss.str(); 
    } 

    static int size(const std::vector<int>& shape)
    {
        int sz = 1;
        for(int i=0; i<shape.size(); ++i) sz *= shape[i] ;
        return sz ;  
    }

    std::string desc() const { return desc(shape) ; }
    int size() const { return size(shape) ; }

    static int ni_(const std::vector<int>& shape) { return shape.size() > 0 ? shape[0] : 1 ;  }
    static int nj_(const std::vector<int>& shape) { return shape.size() > 1 ? shape[1] : 1 ;  }
    static int nk_(const std::vector<int>& shape) { return shape.size() > 2 ? shape[2] : 1 ;  }
    static int nl_(const std::vector<int>& shape) { return shape.size() > 3 ? shape[3] : 1 ;  }
    static int nm_(const std::vector<int>& shape) { return shape.size() > 4 ? shape[4] : 1 ;  }

    int ni_() const { return ni_(shape) ; }
    int nj_() const { return nj_(shape) ; }
    int nk_() const { return nk_(shape) ; }
    int nl_() const { return nl_(shape) ; }
    int nm_() const { return nm_(shape) ; }

    int idx(int i, int j, int k, int l, int m)
    {
        int ni = ni_() ;
        int nj = nj_() ; 
        int nk = nk_() ; 
        int nl = nl_() ;
        int nm = nm_() ;

        return  i*nj*nk*nl*nm + j*nk*nl*nm + k*nl*nm + l*nm + m ;
    }


    std::vector<int>& shape ; 
};




struct NPU
{
    static const char* MAGIC ; 

    template<typename T>
    static std::string make_header(const std::vector<int>& shape );

    template<typename T>
    static int parse_header(std::vector<int>& shape, const std::string& hdr );

    static void _parse_tuple(std::vector<int>& shape, const std::string& sh );

    static const bool fortran_order ;  
    static std::string _make_preamble( int major=1, int minor=0 );
    static std::string _make_header(const std::vector<int>& shape, const char* descr="<f4" );
    static std::string _little_endian_short_string( uint16_t dlen ) ; 
    static std::string _make_tuple(const std::vector<int>& shape );
    static std::string _make_dict(const std::vector<int>& shape, const char* descr );
    static std::string _make_header(const std::string& dict);

    static std::string check(const char* path); 


};


const char* NPU::MAGIC = "\x93NUMPY" ; 
const bool NPU::fortran_order = false ; 

template<typename T>
std::string NPU::make_header(const std::vector<int>& shape )
{
    std::string descr = Desc<T>::descr() ; 
    return _make_header( shape, descr.c_str() ) ; 
}

template<typename T>
int NPU::parse_header(std::vector<int>& shape, const std::string& hdr )
{
    std::string preamble = hdr.substr(0,8) ;  
    std::string PREAMBLE = _make_preamble(); 
    assert( preamble.compare(PREAMBLE) == 0 );  

    char hlen_lsb = hdr[8] ;  
    char hlen_msb = hdr[9] ;  
    int hlen = hlen_msb << 8 | hlen_lsb ; 
    assert( (hlen+10) % 16 == 0 ) ;  

    std::string dict = hdr.substr(10,10+hlen) ; 
    assert( dict[dict.size()-1] == '\n' ) ;   
    dict[dict.size()-1] = '\0' ; 

    std::string::size_type p0 = dict.find("(") + 1; 
    std::string::size_type p1 = dict.find(")"); 
    assert( p0 != std::string::npos ); 
    assert( p1 != std::string::npos ); 

    std::string sh = dict.substr( p0, p1 - p0 ) ;  

    _parse_tuple( shape, sh ); 

#ifdef NPU_DEBUG
    std::cout 
        << " parse_header " << hdr << std::endl 
        << " preamble " << preamble << std::endl 
        << " hlen_lsb " << int(hlen_lsb) << std::endl 
        << " hlen_msb " << int(hlen_msb) << std::endl 
        << " hlen " << hlen << std::endl 
        << " dict [" << dict << "]"<< std::endl 
        << " p0 " << p0 << std::endl
        << " p1 " << p1 << std::endl
        << " sh " << sh << std::endl
        ; 
#endif

    return 0 ; 
}

void NPU::_parse_tuple(std::vector<int>& shape, const std::string& sh )
{
    std::istringstream f(sh);
    std::string s;

    char delim = ',' ; 
    const char* trim = " " ;  

    int ival(0) ; 

    while (getline(f, s, delim)) 
    {
       s.erase(0, s.find_first_not_of(trim));  // left trim
       s.erase(s.find_last_not_of(trim) + 1);   // right trim 
       if( s.size() == 0 ) continue ; 

       std::istringstream ic(s) ;
       ic >> ival ; 

       shape.push_back(ival) ; 
 
#ifdef NPU_DEBUG
       std::cout << "[" << s << "] -> " << ival << std::endl ;
#endif

    }

#ifdef NPU_DEBUG
    std::cout << " parse_tuple " 
              << " sh  [" << sh << "]" 
              << " shape " << shape.size()
              << std::endl
              ;

#endif
}
 

std::string NPU::check(const char* path) 
{
    std::stringstream ss ; 
    ss << "python -c \"import numpy as np ; print np.load('" ; 
       << path 
       << "') \" && xxd " 
       << path 
       ; 
    return ss.str(); 
}


std::string NPU::_make_header(const std::vector<int>& shape, const char* descr )
{
    std::string dict = _make_dict( shape, descr ); 
    std::string header = _make_header( dict ); 
    return header ; 
}

std::string NPU::_make_tuple( const std::vector<int>& shape )
{
    int ndim = shape.size() ;

    std::stringstream ss ; 
    ss << "(" ; 

    if( ndim == 1 )
        ss << shape[0] << "," ; 
    else
        for(int i=0 ; i < ndim ; i++ ) ss << shape[i] << ", " ; 

    ss << "), " ;
    return ss.str(); 
}

std::string NPU::_make_dict(const std::vector<int>& shape, const char* descr )
{
    std::stringstream ss ; 
    ss << "{" ; 
    ss << "'descr': '" << descr << "', " ; 
    ss << "'fortran_order': " << ( fortran_order ? "True" : "False" ) << ", " ; 
    ss << "'shape': " ; 
    ss << _make_tuple( shape ) ; 


    ss << "}" ;  

    return ss.str(); 
} 

std::string NPU::_little_endian_short_string( uint16_t dlen )
{
    // https://github.com/numpy/numpy/blob/master/doc/neps/nep-0001-npy-format.rst
    // The next 2 bytes form a little-endian unsigned short int: the length of the header data HEADER_LEN

    u16c2_t len ; 
    len.u16 = dlen ; 

    char e = Endian::detect() ; 
    std::string hlen(2, ' ') ;
    hlen[0] = e == Endian::LITTLE ? len.c[0] : len.c[1] ;  
    hlen[1] = e == Endian::LITTLE ? len.c[1] : len.c[0] ; 

#ifdef NPU_DEBUG
    std::cout << " dlen " << dlen << std::endl ; 
    std::cout << " len.c[0] " << len.c[0] << std::endl ; 
    std::cout << " len.c[1] " << len.c[1] << std::endl ; 
    std::cout << ( e == Endian::LITTLE ? "little_endian" : "big_endian" ) << std::endl ; 
#endif

    return hlen ; 
}


std::string NPU::_make_preamble( int major, int minor )
{
    std::string preamble(MAGIC) ; 
    preamble.push_back((char)major); 
    preamble.push_back((char)minor); 
    return preamble ; 
}

std::string NPU::_make_header(const std::string& dict)
{
    uint16_t dlen = dict.size() ;
    uint16_t padding = 16 - ((10 + dlen ) % 16 ) - 1 ;
    padding += 3*16 ; // adhoc extra padding for bit-perfect matching to NumPy (for test array anyhow)
    uint16_t hlen = dlen + padding + 1 ; 

#ifdef NPU_DEBUG
    std::cout 
        << " dlen " << dlen 
        << " padding " << padding
        << " hlen " << hlen 
        << std::endl 
        ; 
#endif

    assert( (hlen + 10) % 16 == 0 );  
    std::stringstream ss ; 
    ss << _make_preamble() ;  
    ss << _little_endian_short_string( hlen ) ; 
    ss << dict ; 
 
    for(int i=0 ; i < padding ; i++ ) ss << " " ; 
    ss << "\n" ;  

    return ss.str(); 
}


