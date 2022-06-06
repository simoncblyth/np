// name=NP_Make_ellipsis_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name


#include "NP.hh"

struct demo
{
   int x ; 
   int y ; 
   int z ; 
   int w ; 
}; 


void test_Make_ellipsis()
{
    std::vector<demo> dd ; 

    dd.push_back( {1,2,3,4} ); 
    dd.push_back( {10,20,30,40} ); 
    dd.push_back( {100,200,300,400} ); 

    NP* a = NP::Make<int>( (int*)dd.data(), int(dd.size()), 4 ); 
    a->save("/tmp/NP_Make_ellipsis_test/demo.npy") ; 
}

void test_Make_ellipsis_empty()
{
    std::vector<demo> dd ; 
    NP* a = NP::Make<int>( (int*)dd.data(), int(dd.size()), 4 ); 
    assert( a == nullptr ); 
}




int main(int argc, char** argv)
{
    //test_Make_ellipsis(); 
    test_Make_ellipsis_empty(); 

    return 0 ; 
}
