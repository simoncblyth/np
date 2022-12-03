// name=NP_ifind2D_test ; gcc $name.cc -std=c++11 -lstdc++ -DX_WITH_VERBOSE -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

void test_flat()
{
    NP* a = NP::Make<int>(10,4) ; 
    a->fillIndexFlat();
    a->save("/tmp/a.npy");  

    int ival = 4 ; 
    int jcol = 0 ;   // column in which to look for ival 
    int jret = 3 ;  //  column to return  

    int vret = a->ifind2D<int>(ival, jcol, jret );  

    std::cout << " vret " << vret << std::endl ; 
    assert( vret == 7 ); 
}

void test_fail_to_find()
{
    NP* a = NP::LoadFromString<int>(R"(10 3)" ); 

    std::cout 
        << " a.sstr " << a->sstr()
        << " a.repr " << a->repr<int>() 
        << std::endl
        ; 

    int vret = a->ifind2D<int>( 0, 0, 1 ); 
    std::cout << " vret " << vret << std::endl ; 
    assert( vret == -1 ); 
}

void test_find()
{
    NP* a = NP::LoadFromString<int>(R"(
       10 3
       20 6
       30 9
       40 12 
      )" ); 

    std::cout 
        << " a.sstr " << a->sstr()
        << " a.repr " << a->repr<int>() 
        << std::endl
        ; 

    const int N = 7 ; 
    int xret[N] = { 3,6,9,12,-1,-1,-1 } ; 
    int vret[N] ; 

    vret[0] = a->ifind2D<int>( 10, 0, 1 ); 
    vret[1] = a->ifind2D<int>( 20, 0, 1 ); 
    vret[2] = a->ifind2D<int>( 30, 0, 1 ); 
    vret[3] = a->ifind2D<int>( 40, 0, 1 ); 
    vret[4] = a->ifind2D<int>( 50, 0, 1 ); 
    vret[5] = a->ifind2D<int>(  0, 0, 1 ); 
    vret[6] = a->ifind2D<int>( -1, 0, 1 ); 

    for(int i=0 ; i < N ; i++)
    {
        bool match = vret[i] == xret[i] ; 
        std::cout 
            << " i " << std::setw(3) << i 
            << " xret[i] " << std::setw(3) << xret[i] 
            << " vret[i] " << std::setw(3) << vret[i] 
            << " match " << ( match ? "YES" : "NO" )
            << std::endl 
            ; 
        assert( match); 
    }



}




int main(int argc, char** argv)
{
    test_find(); 

    return 0 ; 

}
