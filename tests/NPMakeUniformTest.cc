// name=NPMakeUniformTest ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* uu = NP::MakeUniform<double>(1000000); 
    uu->save("/tmp/NPMakeUniformTest/uu.npy" ); 

    return 0 ; 
}
