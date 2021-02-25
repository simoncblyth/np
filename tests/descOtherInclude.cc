#include "descOtherInclude.hh"
#include "desc.hh"
#include <iostream>

descOtherInclude::descOtherInclude()
{
    std::cout 
        << "descOtherInclude" << std::endl << std::endl 
        << "descr<float>::dtype() " << descr<float>::dtype() << std::endl   
        << "descr<double>::dtype() " << descr<double>::dtype() << std::endl   

        << "descr<char>::dtype() " << descr<char>::dtype() << std::endl   
        << "descr<short>::dtype() " << descr<short>::dtype() << std::endl   
        << "descr<int>::dtype() " << descr<int>::dtype() << std::endl   
        << "descr<long>::dtype() " << descr<long>::dtype() << std::endl   
        << "descr<long long>::dtype() " << descr<long long>::dtype() << std::endl   

        << "descr<unsigned char>::dtype() " << descr<unsigned char>::dtype() << std::endl   
        << "descr<unsigned short>::dtype() " << descr<unsigned short>::dtype() << std::endl   
        << "descr<unsigned int>::dtype() " << descr<unsigned int>::dtype() << std::endl   
        << "descr<unsigned long>::dtype() " << descr<unsigned long>::dtype() << std::endl   
        << "descr<unsigned long long>::dtype() " << descr<unsigned long long>::dtype() << std::endl   

        << "descr<std::complex<float> >::dtype() " << descr<std::complex<float> >::dtype() << std::endl   
        << "descr<std::complex<double> >::dtype() " << descr<std::complex<double> >::dtype() << std::endl   
        << std::endl 
        << std::endl 
        ; 
}
