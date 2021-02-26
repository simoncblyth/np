// name=NPWriteTest ; gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name && python3 -c "import numpy as np ; print(np.load(\"/tmp/$name.npy\"))"

#include <vector>
#include "NP.hh"

int main(int argc, char** argv)
{
    std::vector<float>     af = {1.,2.,3.,4.,5.} ; 
    std::vector<double>    ad = {1.,2.,3.,4.,5.} ; 
    std::vector<int>       ai = {1 ,2 ,-3 ,4 ,-5 } ; 
    std::vector<unsigned>  au = {1 ,2 ,3 ,4 ,5 } ; 

    NP::Write("/tmp", "NPWriteTest.npy", af );   
    NP::Write("/tmp", "NPWriteTest.npy", ad );   
    NP::Write("/tmp", "NPWriteTest.npy", au );   
    NP::Write("/tmp", "NPWriteTest.npy", ai );   

    return 0 ; 
}
