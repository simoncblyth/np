// name=NPminmaxTest ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name

#include <array>
#include "NP.hh"

std::array<double, 20> src {{ 
     1.,   10., 
     2.,   20., 
     3.,   30., 
     4.,   40., 
     5.,   50.,

     100., 1000., 
     200., 2000., 
     300., 3000., 
     400., 4000., 
     500., 5000.,

 }} ; 



void dump( const NP* a, int item=-1 )
{
    std::cout << " dump item " << item << std::endl ;  

    unsigned ndim = a->shape.size(); 
    assert( ndim == 2 || ndim == 3 ); 

    unsigned ni = a->shape[ndim-2]; 
    unsigned nj = a->shape[ndim-1]; 

    unsigned num_items = ndim == 3 ? a->shape[0] : 1 ;
    assert( item < int(num_items) );
    unsigned item_offset = item == -1 ? 0 : ni*nj*item ;
    const double* aa = a->cvalues<double>() + item_offset ; 
      
    for(unsigned i=0 ; i < ni ; i++)
    {
        for(unsigned j=0 ; j < nj ; j++) std::cout << aa[i*nj+j] << " " ; 
        std::cout << std::endl ; 
    }
}



void test_2d()
{
    std::cout << "test_2d" << std::endl ;
    NP* a = NP::Make<double>(10, 2);  
    a->read( src.data() ); 

    dump(a) ; 

    unsigned nj = a->shape[1]; 
    for(unsigned j=0 ; j < nj ; j++)
    {
         double mn, mx ; 
         a->minmax<double>( mn, mx, j ); 

         std::cout 
             << " j " << std::setw(3) << j 
             << " mn " << std::setw(6) << mn
             << " mx " << std::setw(6) << mx
             << std::endl
             ; 
    } 


}

void test_3d()
{
    std::cout << "test_3d" << std::endl ;
    NP* a = NP::Make<double>(2, 5, 2);  
    a->read( src.data() ); 

    dump(a, 0); 
    dump(a, 1); 

    unsigned ni = a->shape[0]; 
    unsigned nj = a->shape[1]; 
    unsigned nk = a->shape[2]; 

    double mn, mx ; 

    for(unsigned i=0 ; i < ni ; i++)
    {
        unsigned item = i ; 
        for(unsigned k=0 ; k < nk ; k++)
        {
            unsigned column = k ; 
            a->minmax<double>( mn, mx, column, item ); 

            std::cout 
                << " item "   << std::setw(3) << item
                << " column " << std::setw(3) << column 
                << " mn " << std::setw(6) << mn
                << " mx " << std::setw(6) << mx
                << std::endl
                ; 
        } 
    }
}


int main(int argc, char** argv)
{
    test_2d(); 
    test_3d(); 
    return 0 ; 
}
