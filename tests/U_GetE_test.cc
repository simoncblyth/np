// name=U_GetE_test ; gcc $name.cc -lstdc++ -std=c++11 -I.. -o /tmp/$name && /tmp/$name

#include <iostream>
#include "NPU.hh"

int main(int argc, char** argv)
{
    char C = U::GetE<char>("C", '?' ); 
    std::cout << " C [" << C << "]" << std::endl ; 
    return 0 ;  
}
