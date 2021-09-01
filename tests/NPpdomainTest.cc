// name=NPpdomainTest ; mkdir -p /tmp/$name ; mkdir -p /tmp/$name/3d ; gcc $name.cc -DDEBUG -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name && ipython -i $name.py 
#include <iostream>
#include "NP.hh"

NP* make_prop_2d(unsigned item, unsigned ni, unsigned nj)
{
    assert( nj == 2 ); 
    NP* a = NP::Make<double>( ni, nj ); 
    double* aa = a->values<double>(); 
    for(unsigned i=0 ; i < ni ; i++)
    {
        double dom = double(100*i+1000*item) ; 
        double val = double(10*i) ;    

        aa[i*nj+0] = dom ; 
        aa[i*nj+1] = val ; 

#ifdef DEBUG
        std::cout 
            << " i " << std::setw(4) << i 
            << " dom " << std::setw(10) << std::fixed << std::setprecision(4) << dom
            << " val " << std::setw(10) << std::fixed << std::setprecision(4) << val 
            << std::endl 
            ;
#endif
    }
    return a ; 
}


NP* make_props_3d()
{
    unsigned num_items = 5 ; 
    unsigned ni = 11 ; 
    unsigned nj = 2 ; 
    NP* a = NP::Make<double>( num_items, ni, nj ); 
    for(unsigned item=0 ; item < num_items ; item++)
    {
        NP* prop = make_prop_2d(item, ni, nj); 
        unsigned prop_num_bytes = prop->arr_bytes();   // assuming all items the same size 
        memcpy( a->bytes() + prop_num_bytes*item, prop->bytes(), prop_num_bytes ); 
    }
    return a ; 
}
 

void test_pdomain_2d()
{
    NP* a = make_prop_2d(0, 11,2); 

    NP* b = NP::Make<double>( 10*a->shape[0], 2 ); 
    double* bb = b->values<double>(); 
    
    unsigned ni = b->shape[0] ; 
    unsigned nj = b->shape[1] ; 

    for(unsigned i=0 ; i < ni ; i++)
    {
        double tval = double(i) ;   
        double tdom = a->pdomain<double>(tval);  

        bb[i*nj+0] = tval ; 
        bb[i*nj+1] = tdom ; 

/*
        std::cout 
            << " i " << std::setw(4) << i 
            << " tval " << std::setw(10) << std::fixed << std::setprecision(4) << tval 
            << " tdom " << std::setw(10) << std::fixed << std::setprecision(4) << tdom
            << std::endl 
            ;
*/
    }
    a->save("/tmp/NPpdomainTest/a.npy");
    b->save("/tmp/NPpdomainTest/b.npy");
}



void test_pdomain_3d()
{
    NP* a = make_props_3d(); 
    a->save("/tmp/NPpdomainTest/3d/a.npy"); 
    const double* aa = a->cvalues<double>(); 
    unsigned aj = a->shape[1] ; 

    unsigned ndim = a->shape.size(); 
    assert( ndim == 3 ); 

    NP* b = NP::Make<double>( a->shape[0], 10*a->shape[1], a->shape[2] ); 
    double* bb = b->values<double>(); 

    unsigned ni = b->shape[0] ; 
    unsigned nj = b->shape[1] ; 
    unsigned nk = b->shape[2] ; 
    assert( nk == 2 );  

    for(unsigned i=0 ; i < ni ; i++)
    {
        for(unsigned j=0 ; j < nj ; j++)
        {
            double tval = double(j) ;   
            int item = i ; 
            double tdom = a->pdomain<double>(tval, item);  

            bb[i*nj*nk+j*nk+0] = tval ; 
            bb[i*nj*nk+j*nk+1] = tdom ; 
        }
    }
    b->save("/tmp/NPpdomainTest/3d/b.npy"); 
}



int main(int argc, char** argv)
{
    //test_pdomain_2d(); 
    test_pdomain_3d(); 

    return 0 ;
}

