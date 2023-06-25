// name=NP_MinusCosThetaLinearAngle_Test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::MinusCosThetaLinearAngle<double>(181); 
    a->save("/tmp/a.npy"); 

    return 0 ; 
}
