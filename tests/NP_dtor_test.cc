// name=NP_dtor_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include <vector>
#include <iostream>

/**

Default dtor of N invokes default dtor 
of the vector member which invokes the D dtors of the 
contents of the vector. 

**/

struct D
{
   int i ; 
   D(int i_) : i(i_) {}
   ~D() {  std::cout << "~D(" << i << ") " << std::endl ; }
};


struct N
{
   N(){
       std::cout << "[ N::N" << std::endl ; 
       data.push_back( D(0) ); 
       data.push_back( D(1) ); 
       data.push_back( D(2) ); 
       data.push_back( D(3) ); 
       std::cout << "] N::N" << std::endl ; 
   }
   std::vector<D> data ; 
};


int main()
{
    N* n = new N ; 
    delete n ;   

    return 0 ;  
}
