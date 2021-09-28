// name=NPinterpHDTest ; mkdir -p /tmp/$name ; gcc $name.cc -g -std=c++11 -DDEBUG -I.. -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name && ipython -i $name.py 

const char* FOLD = "/tmp/NPinterpHDTest" ; 

#include "NP.hh"



NP* MakeDummyICDF(unsigned num_items, unsigned hd_factor) 
{
    unsigned ni = 100 ; 
    unsigned nj = 4 ; enum { ALL, LHS, RHS, SPA } ; 
    unsigned nk = 2 ; enum { DOM, VAL } ; 
    double edge = 1./double(hd_factor) ;

    NP* a = nullptr ; 

    if( num_items > 1 )
    {
        a = NP::Make<double>( num_items, ni, nj, nk ) ;

        for(unsigned item=0 ; item < num_items ; item++)
        {
            for(unsigned i=0 ; i < ni ; i++)
            {
                // ALL 
                double x_all = double(i)/double(ni) ;  // HMM : this doesnt get to 1. but Linspace does ??
                double y_all = x_all ;                  // simplify testing by equating values to domain 
                a->set<double>( x_all, item, i, ALL, DOM );   
                a->set<double>( y_all, item, i, ALL, VAL );   

                // LHS, RHS : restricts range to get more resolution into extremes
                double x_lhs = double(i)/double(hd_factor*ni) ; 
                double y_lhs = x_lhs ;              
                a->set<double>( x_lhs, item, i, LHS, DOM );   
                a->set<double>( y_lhs, item, i, LHS, VAL );   

                double x_rhs = double(1.) - edge + double(i)/double(hd_factor*ni) ; 
                double y_rhs = x_rhs ;              
                a->set<double>( x_rhs, item, i, RHS, DOM );   
                a->set<double>( y_rhs, item, i, RHS, VAL );   
            }
        }
    }
    else
    {
        a = NP::Make<double>( ni, nj, nk ) ; 

        // using set_offset is an attempt to avoid this kind of duplication
        // but its tricky to get right 

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
    }

    return a ; 
}

void test_3()
{
    unsigned num_items = 1 ; 
    unsigned hd_factor = 10 ; 

    NP* a = MakeDummyICDF(num_items, hd_factor); 
    a->save(FOLD, "icdf.npy" );   

    unsigned ni = 1000 ; 
    NP* xy = NP::Linspace<double>(0.,1.,ni, 2) ; 
    for(unsigned i=0 ; i < ni ; i++)
    {
        double x = xy->get<double>(i, 0) ;   
        double y = a->interpHD(x, hd_factor);  
        xy->set<double>(y, i, 1); 
    }
    xy->save(FOLD, "xy.npy"); 
}


void test_4()
{
    unsigned num_items = 2 ; 
    unsigned hd_factor = 10 ; 

    NP* a = MakeDummyICDF(num_items, hd_factor); 
    a->save(FOLD, "icdf.npy" );   

    unsigned ni = 1000 ; 
    NP* xx = NP::Linspace<double>(0.,1.,ni) ;
    NP* xy = NP::Make<double>(num_items,ni, 2) ;

    for(unsigned item=0 ; item < num_items ; item++)
    { 
        for(unsigned i=0 ; i < ni ; i++)
        {
            double x = xx->get<double>(i, 0) ;   
            double y = a->interpHD<double>(x, hd_factor, item);

            xy->set<double>(x, item, i, 0); 
            xy->set<double>(y, item, i, 1); 
        }
    }
    xy->save(FOLD, "xy.npy"); 
}



int main(int argc, char** argv)
{
    //test_3(); 
    test_4(); 

    return 0 ; 
}
