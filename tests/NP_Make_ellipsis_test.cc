// name=NP_Make_ellipsis_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name


#include "NP.hh"

struct demo
{
   int x ; 
   int y ; 
   int z ; 
   int w ; 
}; 


int main(int argc, char** argv)
{
    std::vector<demo> dd ; 

    dd.push_back( {1,2,3,4} ); 
    dd.push_back( {10,20,30,40} ); 
    dd.push_back( {100,200,300,400} ); 

    NP* a = NP::Make<int>( (int*)dd.data(), int(dd.size()), 4 ); 
    a->save("/tmp/NP_Make_ellipsis_test/demo.npy") ; 

    return 0 ; 
}
