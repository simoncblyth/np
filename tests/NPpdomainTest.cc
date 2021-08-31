// name=NPpdomainTest ; mkdir -p /tmp/$name ; gcc $name.cc -DDEBUG -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name && ipython -i $name.py 
#include <iostream>
#include "NP.hh"

NP* make_prop()
{
    NP* a = NP::Make<double>( 11, 2 ); 
    double* aa = a->values<double>(); 
    unsigned ni = a->shape[0] ; 
    unsigned nj = a->shape[1] ; 
    for(unsigned i=0 ; i < ni ; i++)
    {
        double dom = double(100*i) ; 
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


#ifdef DEBUG
    /*
    double lhs_0 = a->plhs<double>(0); 
    double rhs_0 = a->prhs<double>(0); 
    double lhs_1 = a->plhs<double>(1); 
    double rhs_1 = a->prhs<double>(1); 
    std::cout 
        << " lhs_0 " << std::setw(10) << std::fixed << std::setprecision(4) << lhs_0
        << " rhs_0 " << std::setw(10) << std::fixed << std::setprecision(4) << rhs_0
        << " lhs_1 " << std::setw(10) << std::fixed << std::setprecision(4) << lhs_1
        << " rhs_1 " << std::setw(10) << std::fixed << std::setprecision(4) << rhs_1
        << std::endl 
        ;
    */
#endif

    return a ; 
}

void test_pdomain()
{
    NP* a = make_prop(); 

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

int main(int argc, char** argv)
{
    test_pdomain(); 
    return 0 ;
}

