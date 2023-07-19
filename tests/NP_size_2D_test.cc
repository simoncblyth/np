// name=NP_size_2D_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main()
{
   int ni = 50 ; 
   int nj = 4 ; 
   int nk = 2 ; 
   int nl = 761 ; 
   int nn = 4 ;  


   NP* a = NP::Make<float>(ni,nj,nk,nl,nn); 

   int width, height ; 
   a->size_2D<4>( width, height ); 

   assert( height == ni*nj*nk ); 
   assert( width == nl ); 
 
   std::cout << " a0 " << a->sstr() << std::endl ; 

   a->change_shape( height, width, nn ); 

   std::cout << " a1 " << a->sstr() << std::endl ; 


   return 0 ; 
}
/**

 a0 (50, 4, 2, 761, 4, )
 a1 (400, 761, 4, )

**/
