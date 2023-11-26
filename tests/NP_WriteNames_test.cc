// name=NP_WriteNames_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"

void test_WriteNames()
{
    std::vector<std::string> rgb = {"red", "green", "blue" } ; 
    std::vector<std::string> cmy = {"cyan", "magenta", "yellow" } ; 

    std::vector<std::string> all0 ; 
    std::copy( rgb.begin(), rgb.end(), std::back_inserter(all0) ); 
    std::copy( cmy.begin(), cmy.end(), std::back_inserter(all0) ); 
    assert( all0.size() == rgb.size() + cmy.size() ); 

    const char* fold = "/tmp/NP_WriteNames_test" ; 
    const char* name = "names.txt" ; 

    NP::WriteNames( fold, name, rgb  ); 
    NP::WriteNames( fold, name, cmy, 0, true  );   // 0:all, true:append

    std::vector<std::string> all ; 
    NP::ReadNames( fold, name,  all ); 

    assert( all.size() == all0.size() );

    for(unsigned i=0 ; i < all.size() ; i++ ) 
    {
        std::cout 
            << std::setw(3) << i 
            << " all0 " << std::setw(10) << all0[i].c_str() 
            << " all "  << std::setw(10) << all[i].c_str() 
           << std::endl 
           ; 

       assert( strcmp( all0[i].c_str(), all[i].c_str() ) == 0 ); 
    }
}

void test_WriteNames_Simple()
{
    const char* fold = "/tmp/NP_WriteNames_test" ; 
    const char* name = "simple.txt" ; 
    std::vector<std::string> names = {"red", "green", "blue" } ; 

    NP::WriteNames_Simple( fold, name, names  ); 
}

int main(int argc, char** argv)
{
    /*
    test_WriteNames();     
    */
    test_WriteNames_Simple();     

    return 0 ; 
}


