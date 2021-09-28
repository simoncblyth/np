// name=NPinterpHDTest ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name && ipython -i $name.py 

const char* FOLD = "/tmp/NPinterpHDTest" ; 

#include "NP.hh"

NP* MakeDummyICDF(unsigned ni, unsigned hd_factor) 
{
    unsigned nj = 4 ; enum { ALL, LHS, RHS, SPA } ; 
    unsigned nk = 2 ; enum { DOM, VAL } ; 
    double edge = 1./double(hd_factor) ;
 
    NP* a = NP::Make<double>( ni, nj, nk ); 

    for(unsigned i=0 ; i < ni ; i++)
    {
        // ALL 
        double x_all = double(i)/double(ni) ;  // HMM : this doesnt get to 1. but Linspace does ??
        double y_all = x_all ;                  // simplify testing by equating values to domain 
        a->set<double>( x_all, i, ALL, DOM );   
        a->set<double>( y_all, i, ALL, VAL );   

        // LHS, RHS : restricts range to get more resolution into extremes
        double x_lhs = double(i)/double(hd_factor*ni) ; 
        double y_lhs = x_lhs ;              
        a->set<double>( x_lhs, i, LHS, DOM );   
        a->set<double>( y_lhs, i, LHS, VAL );   

        double x_rhs = double(1.) - edge + double(i)/double(hd_factor*ni) ; 
        double y_rhs = x_rhs ;              
        a->set<double>( x_rhs, i, RHS, DOM );   
        a->set<double>( y_rhs, i, RHS, VAL );   
    }
    return a ; 
}


int main(int argc, char** argv)
{
    unsigned ni = 100 ; 
    unsigned hd_factor = 10 ; 

    NP* a = MakeDummyICDF(ni, hd_factor); 
    a->save(FOLD, "icdf.npy" );   

    unsigned tni = 1000 ; 
    NP* xy = NP::Linspace<double>(0.,1.,tni, 2) ; 
    for(unsigned i=0 ; i < tni ; i++)
    {
        double x = xy->get<double>(i, 0) ;   
        double y = a->interpHD(x, hd_factor);  
        xy->set<double>(y, i, 1); 
    }
    xy->save(FOLD, "xy.npy"); 

    return 0 ; 
}
