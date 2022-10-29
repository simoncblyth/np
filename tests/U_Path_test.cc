// name=U_Path_test ; gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name
// name=U_Path_test ; gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o /tmp/$name && lldb__ /tmp/$name

#include "NPU.hh"
#include <iostream>

int main(int argc, char** argv)
{
    const char* path = U::Path(nullptr, "red", "green" ) ; 
    std::cout << path << std::endl ;
    return 0 ;
}




