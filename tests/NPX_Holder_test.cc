// name=NPX_Holder_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPX.h"

int main()
{
    std::vector<std::string> nn = {"red","green", "blue" } ; 
    NP* a = NPX::Holder(nn); 
    a->save("/tmp/a.npy") ; 

    return 0 ; 
}


