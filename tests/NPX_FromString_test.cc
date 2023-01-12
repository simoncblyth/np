// name=NPX_FromString_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPX.h"

int main(int argc, char** argv)
{
    NP* a = NPX::FromString<int>("0 1 1 2 3 5 8 13 21 34 55 89 144 233"); 

    std::cout << a->repr<int>() << std::endl ; 

    return 0 ; 
}
