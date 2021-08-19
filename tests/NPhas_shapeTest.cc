// name=NPhas_shapeTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <vector>
#include <iostream>
#include "NP.hh"

void test_has_shape()
{
    NP* a = NP::Make<double>( 10, 5 ); 
    a->fill<double>(1.); 

    assert( a->has_shape(10,5) == true ); 
    assert( a->has_shape(-1,5) == true ); 
    assert( a->has_shape(10,-1) == true ); 

    assert( a->has_shape(11,5) == false ); 
    assert( a->has_shape(11,5) == false ); 
    assert( a->has_shape(10,5,1) == false ); 


    NP* b = NP::Make<double>( 10, 6, 4, 4, 4 ); 
    b->fill<double>(1.); 

    assert( b->has_shape(10,6,4,4,4) == true ); 
    assert( b->has_shape(11,5) == false ); 
}


int main(int argc, char** argv)
{
    test_has_shape(); 
    return 0 ;
}

