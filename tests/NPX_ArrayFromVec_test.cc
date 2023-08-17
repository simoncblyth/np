// ./NPX_ArrayFromVec_test.sh 

#include "NPFold.h"
#include "NPX.h"

struct Compound
{
    int ii[16] ; 
}; 

int main()
{
    std::vector<Compound> v = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }} ; 
    NP* a = NPX::ArrayFromVec<int,Compound>( v, 4, 4) ; 

    NPFold* f = new NPFold ; 

    f->add("a_args", NPX::ArrayFromVec<int,Compound>(  v, 4, 4  )) ; 
    f->add("a_str",  NPX::ArrayFromVec_<int,Compound>( v, "4,4" )) ; 

    f->save("$FOLD") ; 

    return 0 ; 
}
