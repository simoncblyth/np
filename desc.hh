#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <complex>

template<typename T>
struct desc 
{
    static constexpr char code = '?' ; 
    static constexpr unsigned size = 0 ; 
};

template<> struct desc<float>  { static constexpr char code = 'f' ; static constexpr unsigned size = sizeof(float)  ; };
template<> struct desc<double> { static constexpr char code = 'f' ; static constexpr unsigned size = sizeof(double) ; };

template<> struct desc<char> {   static constexpr char code = 'i' ; static constexpr unsigned size = sizeof(char)   ; };
template<> struct desc<short> {  static constexpr char code = 'i' ; static constexpr unsigned size = sizeof(short)  ; };
template<> struct desc<int> {    static constexpr char code = 'i' ; static constexpr unsigned size = sizeof(int)    ; };
template<> struct desc<long> {   static constexpr char code = 'i' ; static constexpr unsigned size = sizeof(long)   ; };
template<> struct desc<long long> {  static constexpr char code = 'i' ; static constexpr unsigned size = sizeof(long long)   ;  };

template<> struct desc<unsigned char> {   static constexpr char code = 'u' ; static constexpr unsigned size = sizeof(unsigned char) ;  };
template<> struct desc<unsigned short> {  static constexpr char code = 'u' ; static constexpr unsigned size = sizeof(unsigned short) ;   };
template<> struct desc<unsigned int> {    static constexpr char code = 'u' ; static constexpr unsigned size = sizeof(unsigned int) ;  };
template<> struct desc<unsigned long> {   static constexpr char code = 'u' ; static constexpr unsigned size = sizeof(unsigned long) ;   };
template<> struct desc<unsigned long long> {  static constexpr char code = 'u' ; static constexpr unsigned size = sizeof(unsigned long long) ;  };

template<> struct desc<std::complex<float> > {   static constexpr char code = 'c' ; static constexpr unsigned size = sizeof(std::complex<float>)  ; } ; 
template<> struct desc<std::complex<double> > {  static constexpr char code = 'c' ; static constexpr unsigned size = sizeof(std::complex<double>) ; } ; 

template<typename T>
struct descr 
{
    static char detect() { unsigned one = 1u ; return (*(char *)&one == 1) ? '<' : '>' ; } ;

    static std::string dtype()
    {
        std::stringstream ss ; 
        ss << detect() << desc<T>::code << desc<T>::size ;
        return ss.str(); 
    }
};

template struct descr<float> ;  
template struct descr<double> ;
  
template struct descr<char> ;  
template struct descr<short> ;  
template struct descr<int> ;  
template struct descr<long> ;  
template struct descr<long long> ;  
 
template struct descr<unsigned char> ;  
template struct descr<unsigned short> ;  
template struct descr<unsigned int> ;  
template struct descr<unsigned long> ;  
template struct descr<unsigned long long> ;  

template struct descr<std::complex<float> > ;  
template struct descr<std::complex<double> > ;  


