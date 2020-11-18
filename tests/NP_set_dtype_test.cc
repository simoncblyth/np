// gcc NP_set_dtype_test.cc -I.. -lstdc++ -o /tmp/NP_set_dtype_test && /tmp/NP_set_dtype_test

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
    u_f4_c16 fc ; 
    for(int i=0 ; i < 16 ; i++) fc.c[i] = 'a' + i ; 
 
    NP* a = new NP("|u1", 16); 
    for(int i=0 ; i < a->size ; i++ ) a->data[i] = 'a' + i ; 
    a->dump(); 

    const char* path = "/tmp/a.npy" ;  
    a->save(path); 

    NP* b = NP::Load(path); 

    b->set_dtype("<f4");   

    b->dump(); 


    float* vv = b->values<float>(); 

    for(int i=0 ; i < 4 ; i++)
    {
         float f = *(vv+i) ; 
         std::cout << f << " " << fc.f[i] << std::endl ;
         assert( fc.f[i] == f ); 
    }


    return 0 ; 
}


