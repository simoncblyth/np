// gcc charsTest.cc -std=c++11 -I.. -lstdc++ -o /tmp/charsTest && /tmp/charsTest

#include "NP.hh"


int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "/tmp/s.npy" ; 


    NP<unsigned char>* s = new NP<unsigned char>(4) ; 
    s->data[0] = 'x' ;  
    s->data[1] = 'y' ;  
    s->data[2] = 'z' ;  
    s->data[3] = 's' ;  
    s->save(path) ; 

    std::cout << NPU::check(path) << std::endl ; 


    NP<unsigned char>* s1 = NP<unsigned char>::Load(path) ; 
    std::cout << "s1 " << s1->desc() << std::endl; 

    s1->dump(0,4); 

    return 0 ; 
}
