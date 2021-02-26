#include "descOtherInclude.hh"
#include "NPU.hh"
#include <iostream>

descOtherInclude::descOtherInclude()
{
    std::cout 
        << "descOtherInclude" << std::endl << std::endl 
        << "descr_<float>::dtype() " << descr_<float>::dtype() << std::endl   
        << "descr_<double>::dtype() " << descr_<double>::dtype() << std::endl   

        << "descr_<char>::dtype() " << descr_<char>::dtype() << std::endl   
        << "descr_<short>::dtype() " << descr_<short>::dtype() << std::endl   
        << "descr_<int>::dtype() " << descr_<int>::dtype() << std::endl   
        << "descr_<long>::dtype() " << descr_<long>::dtype() << std::endl   
        << "descr_<long long>::dtype() " << descr_<long long>::dtype() << std::endl   

        << "descr_<unsigned char>::dtype() " << descr_<unsigned char>::dtype() << std::endl   
        << "descr_<unsigned short>::dtype() " << descr_<unsigned short>::dtype() << std::endl   
        << "descr_<unsigned int>::dtype() " << descr_<unsigned int>::dtype() << std::endl   
        << "descr_<unsigned long>::dtype() " << descr_<unsigned long>::dtype() << std::endl   
        << "descr_<unsigned long long>::dtype() " << descr_<unsigned long long>::dtype() << std::endl   

        << "descr_<std::complex<float> >::dtype() " << descr_<std::complex<float> >::dtype() << std::endl   
        << "descr_<std::complex<double> >::dtype() " << descr_<std::complex<double> >::dtype() << std::endl   
        << std::endl 
        << std::endl 
        ; 
}
