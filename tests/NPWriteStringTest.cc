// name=NPWriteStringTest ; mkdir -p /tmp/$name ; gcc $name.cc -g -std=c++11 -I.. -lstdc++ -o /tmp/$name/$name && lldb__ /tmp/$name/$name

#include <iostream>
#include "NP.hh" 



void test_WriteString_ReadString_(const char* str0)
{

    std::cout << "str0" << std::endl << ( str0 ? str0 : "null" ) << std::endl ; 

    const char* path = "/tmp/NPWriteStringTest/str.txt" ; 

    NP::WriteString(path, str0); 
  
    const char* str1 = NP::ReadString(path); 

    std::cout << "str1" << std::endl << ( str1 ? str1 : "null" ) << std::endl ; 

    if( str0 != nullptr )
    { 
        assert( strcmp( str0, str1) == 0 ); 
    }
}

void test_WriteString_ReadString()
{
    const char* str0 = R"(red
green
blue)" ; 

    test_WriteString_ReadString_(str0); 

    const char* str1 = "hello" ; 
    test_WriteString_ReadString_(str1); 

    const char* str2 = nullptr ; 
    test_WriteString_ReadString_(str2); 

}


void test_ReadString_NonExisting()
{
    const char* path = "/tmp/NPWriteStringTest/NonExisting.txt" ; 

    const char* str1 = NP::ReadString(path); 

    std::cout << "str1" << std::endl << ( str1 ? str1 : "null" ) << std::endl ; 
}




int main(int argc, char** argv)
{
    //test_WriteString_ReadString();     
    test_ReadString_NonExisting();     
    return 0 ; 
}

