// name=NPMultiTest ; gcc $name.cc NPOneUse.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name 
// name=NPMultiTest ; gcc $name.cc NPOneUse.cc -std=c++1z  -I.. -lstdc++ -o /tmp/$name 

#include <iostream>
#include "NP.hh"
#include "NP.hh"

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl ; 
    return 0 ; 
}



