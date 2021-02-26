// name=descTest ; gcc $name.cc descOtherInclude.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name
// testing multiple inclusion of header only desc.hh

#include <iostream>
#include "descOtherInclude.hh"
#include "NPU.hh"

void descTest()
{
    std::cout 
        << "descTest " << std::endl << std::endl  
        << "desc<float>::code "     << desc<float>::code << std::endl
        << "desc<float>::size "     << desc<float>::size << std::endl
        << "desc<double>::code "    << desc<double>::code << std::endl
        << "desc<double>::size "    << desc<double>::size << std::endl
        << "desc<char>::code "      << desc<char>::code << std::endl
        << "desc<char>::size "      << desc<char>::size << std::endl
        << "desc<short>::code "     << desc<short>::code << std::endl
        << "desc<short>::size "     << desc<short>::size << std::endl
        << "desc<int>::code "       << desc<int>::code << std::endl
        << "desc<int>::size "       << desc<int>::size << std::endl
        << "desc<long>::code "      << desc<long>::code << std::endl
        << "desc<long>::size "      << desc<long>::size << std::endl
        << "desc<long long>::code " << desc<long long>::code << std::endl
        << "desc<long long>::size " << desc<long long>::size << std::endl
        << "desc<unsigned char>::code "      << desc<unsigned char>::code << std::endl
        << "desc<unsigned char>::size "      << desc<unsigned char>::size << std::endl
        << "desc<unsigned short>::code "     << desc<unsigned short>::code << std::endl
        << "desc<unsigned short>::size "     << desc<unsigned short>::size << std::endl
        << "desc<unsigned int>::code "       << desc<unsigned int>::code << std::endl
        << "desc<unsigned int>::size "       << desc<unsigned int>::size << std::endl
        << "desc<unsigned long>::code "      << desc<unsigned long>::code << std::endl
        << "desc<unsigned long>::size "      << desc<unsigned long>::size << std::endl
        << "desc<unsigned long long>::code " << desc<unsigned long long>::code << std::endl
        << "desc<unsigned long long>::size " << desc<unsigned long long>::size << std::endl
        << "desc<std::complex<float> >::code " << desc<std::complex<float> >::code << std::endl
        << "desc<std::complex<float> >::size " << desc<std::complex<float> >::size << std::endl
        << "desc<std::complex<double> >::code " << desc<std::complex<double> >::code << std::endl
        << "desc<std::complex<double> >::size " << desc<std::complex<double> >::size << std::endl
        << std::endl
        << std::endl
        ; 
}

void descr_Test()
{
    std::cout 
        << "descr_Test " << std::endl << std::endl  
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

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl ;

    descOtherInclude doi ; 
    descTest(); 
    descr_Test(); 

    return 0 ; 
}


