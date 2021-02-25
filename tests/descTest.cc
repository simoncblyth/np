// name=descTest ; gcc $name.cc descOtherInclude.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name
// testing multiple inclusion of header only desc.hh

#include <iostream>
#include "descOtherInclude.hh"
#include "desc.hh"

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

void descrTest()
{
    std::cout 
        << "descrTest " << std::endl << std::endl  
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

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl ;

    descOtherInclude doi ; 
    descTest(); 
    descrTest(); 

    return 0 ; 
}


