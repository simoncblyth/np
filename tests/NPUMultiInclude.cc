// name=NPUMultiInclude ; gcc $name.cc NPUOtherInclude.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name

/**
testing header-only multiple inclusions

* inlining all functions to make header-only usable with multiple inclusions not tripping up 
  duplicate symbols doesnt work for constants in c++11 (although it does on c++1z)

**/

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


