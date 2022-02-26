// name=NPDumpTest ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<int>(20, 6, 4);  
    a->fillIndexFlat(); 

    int i0=0 ; 
    int i1=20 ; 
    int j0=4 ; 
    int j1=6 ; 

    a->dump(i0,i1,j0,j1); 

    return 0 ; 
}

