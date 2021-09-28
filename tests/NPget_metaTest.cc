// name=NPget_metaTest ; gcc $name.cc -std=c++11 -D_DEBUG -I.. -lstdc++ -o /tmp/$name && /tmp/$name 

#include "NP.hh"


NP* make_array()
{
    NP* a = NP::FromString<float>("1") ; 

    a->meta = R"LITERAL(

hd_factor:10
other:100
withoutdelimiter
another:42
somefloat:42.5
somedouble:142.5
someint:-101
someunsigned:1001

)LITERAL";

   return a ; 
}



void test_get_meta_string(const NP* a)
{
    const char* k0 = "hd_factor" ; 
    std::string v0 = a->get_meta_string(k0); 
    std::cout 
        << " k0 [" << k0 << "]" 
        << " v0 [" << v0 << "]" 
        <<  std::endl 
        ; 

    const char* k1 = "nonexisting" ; 
    std::string v1 = a->get_meta_string(k1); 

    std::cout 
        << " k1 [" << k1 << "]" 
        << " v1 [" << v1 << "]" 
        <<  std::endl
        ; 
}

void test_get_meta(const NP* a )
{
    const char* k0 = "hd_factor" ; 
    unsigned v0 = a->get_meta<unsigned>(k0, 0); 
    std::cout 
        << " k0 [" << k0 << "]" 
        << " v0 [" << v0 << "]" 
        <<  std::endl 
        ; 

    const char* k1 = "someint" ; 
    int v1 = a->get_meta<int>(k1, 0); 
    std::cout 
        << " k1 [" << k1 << "]" 
        << " v1 [" << v1 << "]" 
        <<  std::endl 
        ; 

    const char* k2 = "somefloat" ; 
    float v2 = a->get_meta<float>(k2); 
    std::cout 
        << " k2 [" << k2 << "]" 
        << " v2 [" << v2 << "]" 
        <<  std::endl 
        ; 
 
    const char* k3 = "hd_factor_typo" ; 
    unsigned v3 = a->get_meta<unsigned>(k3); 
    std::cout 
        << " k3 [" << k3 << "]" 
        << " v3 [" << v3 << "]" 
        <<  std::endl 
        ; 
}


void test_set_meta( NP* a )
{
    std::cout << "test_set_meta" << std::endl << a->meta << std::endl ; 

    a->set_meta<unsigned>("hd_factor", 20) ; 
    a->set_meta<unsigned>("hd_factor", 30) ; 
    a->set_meta<unsigned>("hd_factor", 40) ; 

    std::cout << "test_set_meta" << std::endl << a->meta << std::endl ; 
}



int main(int argc, char** argv)
{
    const NP* a = make_array(); 
    test_get_meta_string(a); 
    test_get_meta(a); 

    
    test_set_meta(const_cast<NP*>(a)); 

    return 0 ; 
}
