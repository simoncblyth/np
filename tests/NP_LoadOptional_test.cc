// ./NP_LoadOptional_test.sh

#include "NP.hh"

NP* UU_BURN = NP::Load("$SEvt__UU_BURN") ;

int main(int argc, char** argv)
{
    std::cout << "UU_BURN " << ( UU_BURN ? UU_BURN->sstr() : "-" ) << std::endl ; 
    return 0 ; 
}
