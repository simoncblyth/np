#include "NP.hh"

int test_load(int argc, char** argv)
{
    const char* arg = argc > 1 ? argv[1] : nullptr ; 
    if(arg == nullptr) return 0 ;    

    NP* a = NP::Load(arg); 

    std::cout 
        << " arg " << arg << std::endl 
        << a->desc() 
        << std::endl
        ;  
    return 0 ; 
}

void test_default_ctor_data_size()
{
    // this was returning 4 for an empty array due to NPS::size bug
    NP* a = new NP ;  
    std::cout << " a->data.size " << a->data.size() << std::endl ;  
}


int main(int argc, char** argv)
{
    //test_default_ctor_data_size(); 
    test_load(argc, argv); 


    return 0 ; 
}
