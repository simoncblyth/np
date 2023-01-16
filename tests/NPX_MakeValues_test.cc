// ./NPX_MakeValues_test.sh

#include "NPX.h"
const char* FOLD = getenv("FOLD"); 
const char* NAME = "kv.npy" ; 

void test_int()
{
    NPX::KV<int> kv ; 
    kv.add("pmtTotal", 20000); 
    kv.add("pmtTotal_SPMT", 25600 ); 

    NP* a = kv.values(); 
    std::cout << " a "  << NPX::DescValues<int>(a) ; 

    a->save(FOLD, NAME); 

    NP* b = NP::Load(FOLD, NAME); 
    std::cout << " b "  << NPX::DescValues<int>(a) ; 
}

void test_double()
{
    NPX::KV<double> kv ; 
    kv.add("red", 1.1 ); 
    kv.add("green", 2.2 ); 
    kv.add("blue", 3.3 ); 

    NP* a = kv.values(); 
    std::cout << " a "  << NPX::DescValues<double>(a) ; 

    a->save(FOLD, NAME); 

    NP* b = NP::Load(FOLD, NAME); 
    std::cout << " b "  << NPX::DescValues<double>(a) ; 
}


int main(int argc, char** argv)
{
    //test_int(); 
    test_double(); 

    return 0 ; 
}
