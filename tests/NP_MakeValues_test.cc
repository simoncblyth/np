// ~/np/tests/NP_MakeValues_test.sh 

#include <cstdlib>
#include "NPX.h"


int main(int argc, char** argv)
{
    std::vector<std::pair<std::string, double>> values ; 
    values.push_back( {"red", 1. } ); 
    values.push_back( {"green", 2. } ); 
    values.push_back( {"green.pink", 200. } ); 
    values.push_back( {"green.pink", 300. } ); 
    values.push_back( {"green.pink", 400. } ); 
    values.push_back( {"green", 2. } ); 
    values.push_back( {"blue", 3. } ); 


    NP* vv0 = NPX::MakeValues(values) ; 
    vv0->save("$FOLD/values0.npy" );    

    NP* vv = NPX::MakeValues(values, "pink") ; 
    vv->save("$FOLD/values.npy" );    
    vv->set_meta<std::string>("opt", "U0,U1,U2") ; 

    std::cout << "vv0" << std::endl << vv0->descValues() << std::endl; 
    std::cout << "vv" << std::endl << vv->descValues() << std::endl; 

    std::cout << "vv.descMeta" << std::endl << vv->descMeta() << std::endl ; 

    return 0 ; 

}
