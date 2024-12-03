// ~/np/tests/NP_Combine_parasite_test.sh

#include "NPX.h"

int main()
{
    unsigned N = 10 ; 

    std::vector<const NP*> aa ; 
    for(unsigned i=0 ; i < N ; i++) aa.push_back(NPX::MakeDemo("<f8", 2+i, 2 )); 
    NP* c0 = NP::Combine(aa, true, nullptr) ; 
    c0->save("$FOLD/c0.npy" ); 


    std::vector<double> pp ; 
    for(unsigned i=0 ; i < N ; i++) pp.push_back(double(i)*100.) ; 
    NP* parasite = NPX::Make(pp) ; 

    NP* c1 = NP::Combine(aa, true, parasite ) ; 
    c1->save("$FOLD/c1.npy" ); 

    return 0 ; 
}
