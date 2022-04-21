// name=NPSaveLoadTest ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name

#include "NP.hh"
const char* FOLD = "/tmp/NPSaveLoadTest" ; 

void test_save(int dom_low, int dom_high, const std::vector<std::string> a_names)
{
    NP* a = NP::Make<int>(10, 4); 
    a->fillIndexFlat(); 
    a->set_meta<int>("domain_low",  dom_low ) ; 
    a->set_meta<int>("domain_high", dom_high ) ; 
    a->set_names( a_names); 
    a->save(FOLD, "a.npy"); 
}

void test_load(int dom_low, int dom_high, const std::vector<std::string> a_names)
{
    NP* b = NP::Load(FOLD, "a.npy" ); 
    std::cout << " b.sstr " << b->sstr() <<  std::endl ; 

    std::vector<std::string> b_names ; 
    b->get_names(b_names) ; 
    for(unsigned i=0 ; i < b_names.size() ; i++) std::cout << b_names[i] << std::endl ; 

    assert( b_names.size() == a_names.size() ); 

    int dom_low_2 = b->get_meta<int>("domain_low" ); 
    int dom_high_2 = b->get_meta<int>("domain_high" ); 

    assert( dom_low_2 == dom_low ); 
    assert( dom_high_2 == dom_high ); 
}

void test_save_load()
{
    int dom_low = 101 ; 
    int dom_high = 202 ; 
    std::vector<std::string> a_names = { "red", "green", "blue" } ;
    test_save( dom_low, dom_high, a_names ); 
    test_load( dom_low, dom_high, a_names ); 
}

void test_get_name_index()
{
    std::vector<std::string> a_names = { "red", "green", "blue" } ;
    NP* a = NP::Make<int>(10, 4); 
    a->fillIndexFlat(); 
    a->set_names( a_names); 

    int idx0 = a->get_name_index("red"); 
    int idx1 = a->get_name_index("green"); 
    int idx2 = a->get_name_index("blue"); 

    assert( idx0 == 0 ); 
    assert( idx1 == 1 ); 
    assert( idx2 == 2 ); 

    int idx3 = a->get_name_index("cyan"); 
    std::cout << " idx3 " << idx3 << std::endl ;  
    assert( idx3 == -1 ); 
}


int main(int argc, char** argv)
{
    test_save_load(); 
    //test_get_name_index(); 
    return 0 ; 
}


