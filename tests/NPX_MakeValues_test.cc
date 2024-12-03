// ~/np/tests/NPX_MakeValues_test.sh

#include "NPX.h"

static const char* PATH="$FOLD/kv.npy" ; 

void test_int()
{
    NPX::KV<int> kv ; 
    kv.add("pmtTotal", 20000); 
    kv.add("pmtTotal_SPMT", 25600 ); 

    NP* a = kv.values(); 
    std::cout << " a "  << NPX::DescValues<int>(a) ; 

    a->save(PATH); 

    NP* b = NP::Load(PATH); 
    std::cout << " b "  << NPX::DescValues<int>(b) ; 
}

void test_double()
{
    NPX::KV<double> kv ; 
    kv.add("red", 1.1 ); 
    kv.add("green", 2.2 ); 
    kv.add("blue", 3.3 ); 

    NP* a = kv.values(); 
    std::cout << " a "  << NPX::DescValues<double>(a) ; 

    a->save(PATH); 

    NP* b = NP::Load(PATH); 
    std::cout << " b "  << NPX::DescValues<double>(b) ; 
}


int main(int argc, char** argv)
{
    //test_int(); 
    test_double(); 

    return 0 ; 
}
