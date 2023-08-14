// ./NPFold_test.sh 

#include <iostream>
#include "NPFold.h"

int main(int argc, char** argv)
{
    NPFold* f0 = new NPFold ; 
    f0->add("demo.npy", NP::Make<float>(1) ); 
    f0->add("propcom.npy", nullptr ); 
    f0->save("$FOLD"); 

    NPFold* f1 = NPFold::Load("$FOLD"); 
    std::cout << f1->desc() << std::endl ; 

    return 0 ; 
}
