// name=NPU_Resolve_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name 

#include "NPU.hh"

int main(int argc, char** argv)
{
    const char* spec = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt/PMTSimParamData/MPT" ; 
    const char* path = U::Resolve(spec) ; 

    std::cout 
       << " spec " << ( spec ? spec : "-" ) << std::endl 
       << " path " << ( path ? path : "-" ) << std::endl 
       ;
       
    return 0 ; 
}
