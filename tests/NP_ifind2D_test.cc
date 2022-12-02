// name=NP_ifind2D_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<int>(10,4) ; 
    a->fillIndexFlat();
    a->save("/tmp/a.npy");  

    int ival = 4 ; 
    int jcol = 0 ;   // column in which to look for ival 
    int jret = 3 ;  //  column to return  

    int vret = a->ifind2D<int>(ival, jcol, jret );  

    std::cout << " vret " << vret << std::endl ; 
    assert( vret == 7 ); 


    return 0 ; 

}
