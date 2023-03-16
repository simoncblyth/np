// name=NP_set_meta_kv_test ; export FOLD=/tmp/$name ; mkdir -p $FOLD; gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name && $FOLD/$name && cat $FOLD/a_meta.txt 

#include "NP.hh"

int main()
{
    std::vector<std::pair<std::string, std::string>> kv = { {"hello", "world"}, {"world", "hello"} } ; 

    NP* a = NP::Make<int>(1) ; 
    a->set_meta_kv( kv ); 
    a->save("$FOLD/a.npy"); 

    return 0 ; 
}

