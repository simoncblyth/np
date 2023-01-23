// ./NPFold_meta_test.sh 
#include "NPFold.h"

const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    int i0         = -42 ; 
    unsigned u0    = 42 ; 
    float f0       = 42.5f ; 
    double d0      = 42.5 ; 
    std::string s0 = "hello" ; 

    NPFold* fold = new NPFold ; 

    fold->set_meta<int>(           "int", i0 ); 
    fold->set_meta<unsigned>( "unsigned", u0 ); 
    fold->set_meta<float>(       "float", f0 );
    fold->set_meta<double>(     "double", d0 );
    fold->set_meta<std::string>("string", s0 );

    std::cout << " save to FOLD " << FOLD << std::endl ; 
 
    fold->save(FOLD); 

    NPFold* lfold = NPFold::Load(FOLD) ; 

    int         i1 = lfold->get_meta<int>("int", 0) ; 
    unsigned    u1 = lfold->get_meta<unsigned>("unsigned", 0) ; 
    float       f1 = lfold->get_meta<float>("float", 0.f) ;
    double      d1 = lfold->get_meta<double>("double", 0.f) ;
    std::string s1 = lfold->get_meta<std::string>("string", "" ); 

    std::cout 
        << " i0:" << std::setw(10) << i0  
        << " i1:" << std::setw(10) << i1
        << std::endl 
        << " u0:" << std::setw(10) << u0  
        << " u1:" << std::setw(10) << u1
        << std::endl 
        << " f0:" << std::setw(10) << f0  
        << " f1:" << std::setw(10) << f1
        << std::endl 
        << " d0:" << std::setw(10) << d0  
        << " d1:" << std::setw(10) << d1
        << std::endl 
        << " s0:" << std::setw(10) << s0  
        << " s1:" << std::setw(10) << s1
        << std::endl 
        ;

    assert( i0 == i1 ); 
    assert( u0 == u1 ); 
    assert( f0 == f1 ); 
    assert( d0 == d1 ); 
    assert( s0 == s1 ); 

    return 0 ; 
}
