// name=NP_LoadVec_Test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include <cstring>
#include "NP.hh"


struct RootLoad
{
    std::vector<char> vbuf ; 
    long bytes_read ; 
    const char* buf ; 

    RootLoad(const char* path); 
}; 

inline RootLoad::RootLoad(const char* path)
    :
    bytes_read(NP::LoadVec(vbuf, path)),
    buf(vbuf.data())
{
    bool starts_with_root = strncmp(buf, "root", 4) == 0 ; 
    assert( starts_with_root ); 
}


int main(int argc, char** argv)
{
    const char* path = "$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root" ; 
    RootLoad rl(path); 

    std::cout << " rl.vbuf.size " << rl.vbuf.size() << std::endl ; 

    return 0 ; 
}
