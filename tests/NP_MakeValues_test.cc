// name=NP_MakeValues_test ; mkdir -p /tmp/$name ;  gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && FOLD=/tmp/$name /tmp/$name/$name 

#include <cstdlib>
#include "NP.hh"

const char* FOLD = getenv("FOLD") ; 

int main(int argc, char** argv)
{
    std::vector<std::pair<std::string, double>> values ; 
    values.push_back( {"red", 1. } ); 
    values.push_back( {"green", 2. } ); 
    values.push_back( {"blue", 3. } ); 

    NP* vv = NP::MakeValues(values) ; 
    vv->save(FOLD, "values.npy" );    

    std::cout << vv->descValues() << std::endl; 

    return 0 ; 

}
