// name=NPWriteStringTest ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name

#include <iostream>
#include "NP.hh" 


int main(int argc, char** argv)
{
    const char* str0 = R"(red
green
blue)" ; 

    std::cout << "str0" << std::endl << str0 << std::endl ; 

    const char* path = "/tmp/NPWriteStringTest/str.txt" ; 

    NP::WriteString(path, str0); 
  
    const char* str1 = NP::ReadString(path); 

    std::cout << "str1" << std::endl << str1 << std::endl ; 

    assert( strcmp( str0, str1) == 0 ); 

    return 0 ; 
}

