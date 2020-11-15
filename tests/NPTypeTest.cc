// gcc NPTypeTest.cc -I.. -lstdc++ -o /tmp/NPTypeTest && /tmp/NPTypeTest

#include <string>
#include <iostream>
#include "NP.hh"

union u_f4_c16
{
    float f[4] ; 
    char  c[16] ; 
};

int main(int argc, char** argv)
{
    const char* path = "/tmp/a.npy" ;  
    NP<float>* a = NP<float>::Load(path) ; 
    std::cout << "a " << path << " " << a->desc() << std::endl; 

    u_f4_c16 fc ; 
    fc.f[0] = a->data[0] ;  
    fc.f[1] = a->data[1] ;  
    fc.f[2] = a->data[2] ;  
    fc.f[3] = a->data[3] ;  

    for(int i=0 ; i < 8 ; i++)
    {
        char* p = fc.c + i*2 ; 
        if(*p == 0) continue ;
        //std::cout << *p << *(p+1) << std::endl ; 
        std::string cmd(p, 2 );
        std::cout << cmd << std::endl ; 
    }
    return 0 ; 
}


