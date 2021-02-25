// name=NPUMultiInclude ; gcc $name.cc NPUOtherInclude.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name 
// name=NPUMultiInclude ; gcc $name.cc NPUOtherInclude.cc -std=c++1z  -I.. -lstdc++ -o /tmp/$name 

#include <iostream>
#include "NPU.hh"

int main(int argc, char** argv)
{
    std::cout 
        << argv[0] 
        << " main endian::detect() " << endian::detect()
        << std::endl
         ; 
    return 0 ; 
}


