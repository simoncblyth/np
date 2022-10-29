// name=U_PathType_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPU.hh"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

const char* PATHS = R"( 
/tmp
/tmp/hello
/tmp/hello/red
/tmp/hello/green
/tmp/hello/blue
/tmp/hello/blue/world
)" ; 

int main(int argc, char** argv)
{
    std::stringstream ss(PATHS);
    std::string path ;
    while(std::getline(ss, path))
    {
        int pt = U::PathType(path.c_str());
        std::cout << " pt " << std::setw(2) << pt  << " path [" << path << "] " ; 
        if(pt == U::FILE_PATH) std::cout << "U::FILE_PATH" ; 
        if(pt == U::DIR_PATH) std::cout << "U::DIR_PATH" ; 

        std::cout << std::endl ;

    }
    return 0 ;
}

/**
 pt -1 path [ ]
 pt  1 path [/tmp]
 pt  1 path [/tmp/hello]
 pt  2 path [/tmp/hello/red]
 pt  2 path [/tmp/hello/green]
 pt  1 path [/tmp/hello/blue]
 pt  2 path [/tmp/hello/blue/world]

**/






