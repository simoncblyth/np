// gcc UTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/UTest && /tmp/UTest

#include <string>
#include "NPU.hh"

int main(int argc, char** argv)
{
 
    const char* path = "/tmp/c.npy" ; 
    const char* xpath = "/tmp/c.npj" ; 
    std::string st = U::ChangeExt(path, ".npy", ".npj") ; 

    std::cout << st << std::endl ; 

    assert( strcmp(st.c_str(), xpath) == 0 ); 

    return 0 ; 
}
