// name=NPU_itemsize_test ; gcc $name.cc -std=c++11 -lstdc++ -DDEBUG_NPU -I.. -o /tmp/$name && /tmp/$name

#include <iomanip>
#include "NPU.hh"

void test_3D()
{
    std::vector<int> shape = {10, 4, 4} ; 

    assert( NPS::itemsize_(shape)     == shape[0]*shape[1]*shape[2] ); 

    assert( NPS::itemsize_(shape,0)  == shape[1]*shape[2] ); 
    assert( NPS::itemsize_(shape,9)  == shape[1]*shape[2] ); 

    assert( NPS::itemsize_(shape,0,0) == shape[2] ); 
    assert( NPS::itemsize_(shape,9,0) == shape[2] ); 

    assert( NPS::itemsize_(shape,0,0,0) == 1 ); 
    assert( NPS::itemsize_(shape,9,0,0) == 1 ); 
}

void test_4D()
{
    std::vector<int> shape = {10, 10, 4, 4} ; 

    assert( NPS::itemsize_(shape) == shape[0]*shape[1]*shape[2]*shape[3] ); 

    assert( NPS::itemsize_(shape,0)  == shape[1]*shape[2]*shape[3] ); 
    assert( NPS::itemsize_(shape,9)  == shape[1]*shape[2]*shape[3] ); 

    assert( NPS::itemsize_(shape,0,0) == shape[2]*shape[3] ); 
    assert( NPS::itemsize_(shape,9,0) == shape[2]*shape[3] ); 

    assert( NPS::itemsize_(shape,0,0,0) == shape[3] ); 
    assert( NPS::itemsize_(shape,9,0,0) == shape[3] ); 

    assert( NPS::itemsize_(shape,0,0,0,0) == 1 ); 
    assert( NPS::itemsize_(shape,9,0,0,0) == 1 ); 
}

void test_5D()
{
    std::vector<int> shape = {44, 4, 2, 761, 4 }; 

    assert( NPS::itemsize_(shape)  == shape[0]*shape[1]*shape[2]*shape[3]*shape[4] ); 

    assert( NPS::itemsize_(shape,0)  == shape[1]*shape[2]*shape[3]*shape[4] ); 
    assert( NPS::itemsize_(shape,9)  == shape[1]*shape[2]*shape[3]*shape[4] ); 

    assert( NPS::itemsize_(shape,0,0) == shape[2]*shape[3]*shape[4] ); 
    assert( NPS::itemsize_(shape,9,0) == shape[2]*shape[3]*shape[4] ); 

    assert( NPS::itemsize_(shape,0,0,0) == shape[3]*shape[4] ); 
    assert( NPS::itemsize_(shape,9,0,0) == shape[3]*shape[4] ); 

    assert( NPS::itemsize_(shape,0,0,0,0) == shape[4] ); 
    assert( NPS::itemsize_(shape,9,0,0,0) == shape[4] ); 

    assert( NPS::itemsize_(shape,9,0,0,0,0) == 1 ); 
    assert( NPS::itemsize_(shape,9,0,0,0,0) == 1 ); 
}

void test_6D()
{
    std::vector<int> shape = {44, 4, 2, 761, 4, 2 }; 

    assert( NPS::itemsize_(shape)  == shape[0]*shape[1]*shape[2]*shape[3]*shape[4]*shape[5] ); 

    assert( NPS::itemsize_(shape,0)  == shape[1]*shape[2]*shape[3]*shape[4]*shape[5] ); 
    assert( NPS::itemsize_(shape,9)  == shape[1]*shape[2]*shape[3]*shape[4]*shape[5] ); 

    assert( NPS::itemsize_(shape,0,0) == shape[2]*shape[3]*shape[4]*shape[5] ); 
    assert( NPS::itemsize_(shape,9,0) == shape[2]*shape[3]*shape[4]*shape[5] ); 

    assert( NPS::itemsize_(shape,0,0,0) == shape[3]*shape[4]*shape[5] ); 
    assert( NPS::itemsize_(shape,9,0,0) == shape[3]*shape[4]*shape[5] ); 

    assert( NPS::itemsize_(shape,0,0,0,0) == shape[4]*shape[5] ); 
    assert( NPS::itemsize_(shape,9,0,0,0) == shape[4]*shape[5] ); 

    assert( NPS::itemsize_(shape,9,0,0,0,0) == shape[5] ); 
    assert( NPS::itemsize_(shape,9,0,0,0,0) == shape[5] ); 

    assert( NPS::itemsize_(shape,9,0,0,0,0,0) == 1 ); 
    assert( NPS::itemsize_(shape,9,0,0,0,0,0) == 1 ); 
}

int main(int argc, char** argv)
{
    test_3D(); 
    test_4D(); 
    test_5D(); 
    test_6D(); 
    return 0 ; 
}
