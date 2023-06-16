// name=NPX_ArrayFromEnumMap_test ; export FOLD=/tmp/$name ; mkdir -p $FOLD ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name && $FOLD/$name

#include "NPX.h"

int main(int argc, char** argv)
{
    std::map<int, std::string> catMap ; 
    catMap[-1] = "red" ; 
    catMap[0] = "green" ; 
    catMap[1] = "blue" ; 
    catMap[2] = "cyan" ; 
    catMap[3] = "magenta" ; 
    catMap[4] = "yellow" ; 

    NP* a = NPX::ArrayFromEnumMap(catMap) ; 
    a->save("$FOLD/catMap.npy") ; 

    return 0 ; 
}
