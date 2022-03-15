// name=NPBigTest ; gcc $name.cc -I.. -DDEBUG -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<double>(24, 4096, 4096) ; 
    assert(a); 

/**

In [8]: (4096*4096*24*8)/0x7fffffff                                                                                                                                                                       
Out[8]: 1.500000000698492

**/


    return 0 ; 
}
