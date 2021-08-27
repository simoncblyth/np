// ./NPReadTest.sh 

#include <vector>
#include "NP.hh"

int main(int argc, char** argv)
{
    std::vector<float>     af(16); 
    for(int i=0 ; i < 16 ; i++ ) af[i] = float(i); 

    NP a("<f4", 4, 4 ); 
    a.read(af.data()); 
    a.dump();
    a.save("/tmp/NPReadTest/a.npy");

    NP b("<f4", 4, 4 ); 
    b.read2(af.data()); 
    b.dump();
    b.save("/tmp/NPReadTest/b.npy");


    return 0 ; 
}
