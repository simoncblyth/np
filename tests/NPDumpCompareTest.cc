// name=NPDumpCompareTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <iostream>
#include "NP.hh"

void test_DumpCompare()
{
    NP* a = NP::Linspace<double>( 1., 10., 10 ); 
    NP* b = NP::Linspace<double>( 1., 10., 10 ); 
    NP::DumpCompare<double>( a, b, 0, 0, 1e-6 ); 
}

int main(int argc, char** argv)
{
    test_DumpCompare(); 
    return 0 ;
}

