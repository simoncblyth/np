// ./NP_MakeValues_test.sh 

#include <cstdlib>
#include "NP.hh"

const char* FOLD = getenv("FOLD") ; 

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


    NP* vv0 = NP::MakeValues(values) ; 
    vv0->save(FOLD, "values0.npy" );    

    NP* vv = NP::MakeValues(values, "pink") ; 
    vv->save(FOLD, "values.npy" );    

    std::cout << "vv0" << std::endl << vv0->descValues() << std::endl; 
    std::cout << "vv" << std::endl << vv->descValues() << std::endl; 

    return 0 ; 

}
