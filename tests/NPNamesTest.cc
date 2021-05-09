// name=NPNamesTest ; gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name 

#include <cstring>
#include <string>
#include <vector>
#include "NP.hh"

int main()
{
    const char* path = "/tmp/NPNamesTest.txt" ; 

    std::vector<std::string> names = {"red", "green", "blue", "cyan", "magenta", "yellow" } ; 
    NP::WriteNames(path, names ); 

    std::vector<std::string> names2 ; 
    NP::ReadNames(path, names2 ); 
    assert( names2.size() == names.size() ); 

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const std::string& a = names[i]; 
        const std::string& b = names2[i]; 
        bool match = strcmp( a.c_str(), b.c_str() ) == 0 ; 

        std::cout 
            << std::setw(2) << match
            << std::setw(30) << a
            << " : "
            << std::setw(30) << b 
            << std::endl
            ;

        assert(match) ;
    }

    return 0 ; 
}
