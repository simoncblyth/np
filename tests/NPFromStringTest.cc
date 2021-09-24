// name=NPFromStringTest ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"


void test_one()
{
    std::cout << " test_one " << std::endl ; 
    const char* str = "1" ; 
    NP* a = NP::FromString<double>(str); 
    a->dump(); 
}

void test_many()
{
    std::cout << " test_many " << std::endl ; 
    const char* str = "1 1.1 1.2 1.3 1.4" ; 
    NP* a = NP::FromString<double>(str); 
    a->dump(); 
}

int main(int argc, char** argv)
{
    test_one(); 
    test_many(); 
    return 0 ; 
}
