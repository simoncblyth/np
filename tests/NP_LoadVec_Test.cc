// ./NP_LoadVec_Test.sh 

#include <cstring>
#include "NP.hh"
#include "RootCheck/Bytes.h"


struct RootLoad
{
    std::vector<char> vbuf ; 
    long bytes_read ; 
    char* buffer ; 
    Int_t  fVersion{0}; 
    Int_t  headerLength{0};

    RootLoad(const char* path); 
    std::string desc() const ; 
}; 

inline RootLoad::RootLoad(const char* path)
    :
    bytes_read(NP::LoadVec(vbuf, path)),
    buffer(vbuf.data() + 4)
{
    bool starts_with_root = strncmp(buffer - 4, "root", 4) == 0 ; 
    assert( starts_with_root ); 

    frombuf(buffer, &fVersion);
    frombuf(buffer, &headerLength);
}

inline std::string RootLoad::desc() const 
{
    std::stringstream ss ; 
    ss << "RootLoad::desc" 
       << std::endl
       << " vbuf.size " << vbuf.size() 
       << std::endl 
       << " fVersion " << fVersion 
       << std::endl 
       << " headerLength " << headerLength 
       << std::endl 
       ; 
    std::string s = ss.str() ; 
    return s ; 
}





int main(int argc, char** argv)
{
    const char* path = "$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root" ; 
    RootLoad rl(path); 
    std::cout << rl.desc() << std::endl ; 

    return 0 ; 
}
