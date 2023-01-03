// name=NP_LoadVec_Test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include <cstring>
#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = "$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root" ; 
    std::vector<char> vbuf ; 
    NP::LoadVec(vbuf, path); 

    std::cout << " vbuf.size " << vbuf.size() << std::endl ; 
    const char* buf = vbuf.data(); 

    bool starts_with_root = strncmp(buf, "root", 4) == 0 ; 
    assert( starts_with_root ); 


    return 0 ; 
}
