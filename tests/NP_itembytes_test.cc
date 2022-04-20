// name=NP_itembytes_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include <iomanip>
#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::Make<char>(3, 4, 4); 
    a->fillIndexFlat(); 

    const char* start ; 
    unsigned num_bytes ; 

    for(unsigned t=0 ; t < 3 ; t++)
    { 
        a->itembytes_(&start, num_bytes, 2, t); 
        std::cout << " t " << std::setw(5) << t << " : " ; 
        for(unsigned i=0 ; i < num_bytes ; i++) std::cout << std::setw(5) << int(start[i]) << " " ; 
        std::cout << std::endl ; 
    }

    return 0 ; 
}
