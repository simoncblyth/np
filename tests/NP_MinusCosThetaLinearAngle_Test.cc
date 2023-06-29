// ./NP_MinusCosThetaLinearAngle_Test.sh

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* mct1 = NP::MinusCosThetaLinearAngle<double>(1); 
    NP* mct181 = NP::MinusCosThetaLinearAngle<double>(181); 
    NP* mct900 = NP::MinusCosThetaLinearAngle<double>(900); 

    NP* st1 = NP::SqrtOneMinusSquare(mct1) ; 
    NP* st181 = NP::SqrtOneMinusSquare(mct181) ; 
    NP* st900 = NP::SqrtOneMinusSquare(mct900) ; 

    mct1->save("$FOLD/mct1.npy"); 
    mct181->save("$FOLD/mct181.npy"); 
    mct900->save("$FOLD/mct900.npy"); 

    st1->save("$FOLD/st1.npy"); 
    st181->save("$FOLD/st181.npy"); 
    st900->save("$FOLD/st900.npy"); 

    return 0 ; 
}
