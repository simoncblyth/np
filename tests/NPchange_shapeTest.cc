// name=NPchange_shapeTest ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name 

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<int>(1, 5, 2, 1) ; 
    std::vector<int> src = { 1, 10, 2, 20, 3, 30, 4, 40, 5, 50 }; 
    a->read(src.data()); 

    std::cout << "initial shape " << a->sstr() << std::endl ; 
    a->dump(); 
    assert( a->has_shape(1,5,2,1) ); 

    a->change_shape(-1) ; 
    std::cout << "a->change_shape(-1) : " << a->sstr() << std::endl ; 
    a->dump(); 
    assert( a->has_shape(10) ); 

    a->change_shape(-1,2) ; 
    std::cout << " a->change_shape(-1,2) " << a->sstr() << std::endl ; 
    a->dump(); 
    assert( a->has_shape(5,2) ); 

    a->change_shape(-1,5) ; 
    std::cout << "a->change_shape(-1,5) " << a->sstr() << std::endl ; 
    a->dump(); 
    assert( a->has_shape(2,5)); 

    a->change_shape(-1,2) ; 
    std::cout << "a->change_shape(-1,2) " << a->sstr() << std::endl ; 
    a->dump(); 
    assert( a->has_shape(5,2)); 
    assert( a->has_shape(-1,2)); 
    assert( a->has_shape(5,-1)); 

    return 0 ;         
 
}
