// name=NPU_UName_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPU.hh"

int main()
{
    UName un ; 

    un.add("red") ; 
    un.add("green") ; 
    un.add("blue") ; 
    un.add("blue"); 

    assert( un.get("red") == 0 ); 
    assert( un.get("green") == 1 ); 
    assert( un.get("blue") == 2 ); 
    assert( un.get("cyan") == -1 ); 

    std::cout << un.desc() ; 

    std::string str = un.as_str(); 

    std::cout << "[" << str << "]" << std::endl ; 

    return 0 ; 
}

