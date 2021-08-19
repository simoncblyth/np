// name=NPcumsumTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <vector>
#include <iostream>
#include "NP.hh"

void test_cumsum_1d()
{
    NP* a = NP::Linspace<double>(0., 9., 10) ;  
    int axis = 1 ; 
    NP* c = a->cumsum<double>(axis); 

    a->dump(); 
    c->dump(); 
}

void test_cumsum_2d()
{
    NP* a = NP::Make<double>( 10, 5 ); 
    a->fill<double>(1.); 
    a->save("/tmp/NPcumsumTest/a.npy"); 

    NP* b = NP::MakeLike(a); 
    b->save("/tmp/NPcumsumTest/b.npy"); 

    int axis = 1 ; 
    NP* c = a->cumsum<double>(axis); 
    c->save("/tmp/NPcumsumTest/c0.npy"); 

    c->divide_by_last<double>(); 
    c->save("/tmp/NPcumsumTest/c1.npy"); 

}


/**
::

    In [25]: np.cumsum(np.linspace(0.,9.,10))
    Out[25]: array([ 0.,  1.,  3.,  6., 10., 15., 21., 28., 36., 45.])

**/

int main(int argc, char** argv)
{
    test_cumsum_1d(); 
    test_cumsum_2d(); 
    return 0 ;
}

