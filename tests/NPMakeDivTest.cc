// name=NPMakeDivTest ; gcc $name.cc -std=c++11 -lstdc++ -DDEBUG -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"


void test_1()
{
    std::vector<double> _src = { 0., 1., 2. } ;  
    NP* src = NP::Make<double>(_src.size()) ; 
    src->read( _src.data() ); 

    unsigned mul = 1 ; 

    NP* dst = NP::MakeDiv<double>( src, mul  ); 
    const double* src_v = src->cvalues<double>(); 
    const double* dst_v = dst->cvalues<double>(); 

    for(unsigned i=0 ; i < dst->shape[0] ; i++)
    {
        std::cout 
           << " i " << std::setw(3) << i 
           << " dst_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << dst_v[i] 
           << " src_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << src_v[i] 
           << std::endl
           ;

        assert( dst_v[i] == src_v[i] );  
    }
}


/**


    0     1     2
    +-----+-----+

   0.    1.0    2.0


    0  1  2  3  4
    +--+--+--+--+

   0.  .5 1. 1.2 2.


**/

void test_2()
{
    std::vector<double> _src = { 0., 1., 2. } ;  
    NP* src = NP::Make<double>(_src.size()) ; 
    src->read( _src.data() ); 

    unsigned mul = 2 ; 

    NP* dst = NP::MakeDiv<double>( src, mul  ); 
    const double* src_v = src->cvalues<double>(); 
    const double* dst_v = dst->cvalues<double>(); 

    for(unsigned i=0 ; i < src->shape[0] ; i++)
        std::cout 
           << " i " << std::setw(3) << i 
           << " src_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << src_v[i] 
           << std::endl
           ;
 
    for(unsigned i=0 ; i < dst->shape[0] ; i++)
    {
        std::cout 
           << " i " << std::setw(3) << i 
           << " dst_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << dst_v[i] 
           << std::endl
           ;

       if( i % mul == 0 )
       {
           unsigned j = i/mul ; 
           std::cout 
               << " i " << std::setw(3) << i 
               << " j " << std::setw(3) << j 
               << " dst_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << dst_v[i] 
               << " src_v[j] " << std::setw(10) << std::fixed << std::setprecision(4) << src_v[j] 
               << std::endl
               ;
           assert( dst_v[i] == src_v[j] ); 
       }
    }

}




void test_many(unsigned mul)
{
    std::cout << " test_many mul " << mul << std::endl ; 
    NP* src = NP::Linspace<double>(0., 10., 11 ); 


    NP* dst = NP::MakeDiv<double>( src, mul  ); 
    const double* src_v = src->cvalues<double>(); 
    const double* dst_v = dst->cvalues<double>(); 

    for(unsigned i=0 ; i < src->shape[0] ; i++)
        std::cout 
           << " i " << std::setw(3) << i 
           << " src_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << src_v[i] 
           << std::endl
           ;
 
    for(unsigned i=0 ; i < dst->shape[0] ; i++)
    {
        std::cout 
           << " i " << std::setw(3) << i 
           << " dst_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << dst_v[i] 
           << std::endl
           ;

       if( i % mul == 0 )
       {
           unsigned j = i/mul ; 
           std::cout 
               << " i " << std::setw(3) << i 
               << " j " << std::setw(3) << j 
               << " dst_v[i] " << std::setw(10) << std::fixed << std::setprecision(4) << dst_v[i] 
               << " src_v[j] " << std::setw(10) << std::fixed << std::setprecision(4) << src_v[j] 
               << std::endl
               ;
           assert( dst_v[i] == src_v[j] ); 
       }
    }

}








int main(int argc, char** argv)
{
    //test_1(); 
    //test_2(); 

    test_many(4); 


    return 0 ; 
}
