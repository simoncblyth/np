// name=NP2Test ; gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name && /tmp/$name

#include <iostream>
#include "NP.hh"

void test_load(int argc, char** argv)
{
    const char* default_path = "/tmp/wavelength_deviant_mask.npy" ; 
    const char* path = argc > 1 ? argv[1] : default_path ; 

    NP* a = NP::Load(path); 
    std::cout << a->desc() << std::endl ; 
    std::cout 
        << "a.dtype [" << a->dtype << "]" 
        << "a.shape.size " << a->shape.size() 
        << std::endl 
        ; 

    if( strcmp(a->dtype, "<i8") == 0 && a->shape.size() == 1 )
    {
        size_t* values = a->values<size_t>(); 
        for(unsigned i=0 ; i < a->shape[0] ; i++) 
            std::cout 
                << " i " << std::setw(4) << i 
                << " idx " << std::setw(7) << values[i] 
                << std::endl
                ; 
    }
}

void test_Linspace()
{
    NP* a = NP::Linspace<float>(0.f, 1.f, 11u ); 
    a->dump();  
}


int main(int argc, char** argv)
{
    //test_load(argc, argv); 
    test_Linspace(); 
    return 0 ;
}


