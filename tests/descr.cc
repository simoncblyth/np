// gcc descr.cc -I.. -std=c++11 -lstdc++ -o /tmp/descr && /tmp/descr
#include <cstring>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <vector>

#include "NPU.hh"

int main(int argc, char** argv)
{
    const char* dict = R"({'descr': '<f4', 'fortran_order': False, 'shape': (10, 4), })" ; 

    bool little_endian ; 
    char uifc ; 
    int  width ; 
    std::string descr ; 
    bool fortran_order ; 

    NPU::_parse_dict(little_endian, uifc, width, descr, fortran_order, dict);  

    std::cout 
        << dict 
        << std::endl      
        << " little_endian:[" << little_endian << "]" 
        << " uifc:[" << uifc << "]" 
        << " width:[" << width << "]" 
        << " descr:[" << descr << "]" 
        << " fortran_order:[" << fortran_order << "]" 
        << std::endl
        ; 

    return 0 ; 
}
