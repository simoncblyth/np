// name=NPReadTest ; gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name && python3 -c "import numpy as np ; print(np.load(\"/tmp/$name.npy\"))"

#include <vector>
#include "NP.hh"

int main(int argc, char** argv)
{
    std::vector<float>     af(16); 
    for(int i=0 ; i < 16 ; i++ ) af[i] = float(i); 

    NP a("<f4", 4, 4 ); 
    a.read(af.data()); 
    a.dump();
    a.save("/tmp/NPReadTest.npy");

    return 0 ; 
}
