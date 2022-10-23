// gcc UTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/UTest && /tmp/UTest

#include <string>
#include "NPU.hh"

void test_ChangeExt()
{
    const char* path = "/tmp/c.npy" ; 
    const char* xpath = "/tmp/c.npj" ; 
    std::string st = U::ChangeExt(path, ".npy", ".npj") ; 
    std::cout << st << std::endl ; 
    assert( strcmp(st.c_str(), xpath) == 0 ); 
}

void test_GetE()
{
    float  f   = U::GetE<float>("F", 101.5f );  
    double d   = U::GetE<double>("D", 202.5  );  
    int    i   = U::GetE<int>("I",  -303 );  
    unsigned u = U::GetE<unsigned>("U", 404u  );  

    std::cout 
        << " F " << f << std::endl 
        << " D " << d << std::endl 
        << " I " << i << std::endl 
        << " U " << u << std::endl 
        ;
}

int main(int argc, char** argv)
{
    /*
    test_ChangeExt(); 
    */
    test_GetE(); 

    return 0 ; 
}
