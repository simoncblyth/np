// name=NPSetMetaTest ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"


void test_SetMeta_GetMeta()
{
    std::cout << "test_SetMeta_GetMeta" << std::endl ; 


    std::string mt ; 
    NP::SetMeta<float>(mt, "innerRadius", 50.f ); 
    NP::SetMeta<float>(mt, "outerRadius", 100.f ); 
    std::cout << mt << std::endl ; 

    float innerRadius = NP::GetMeta<float>( mt, "innerRadius", -1.f ); 
    float outerRadius = NP::GetMeta<float>( mt, "outerRadius", -1.f ); 

    std::cout 
        << " innerRadius " << std::fixed << std::setw(10) << std::setprecision(4) << innerRadius 
        << " outerRadius " << std::fixed << std::setw(10) << std::setprecision(4) << outerRadius 
        << std::endl 
        ;

    assert( innerRadius == 50.f ); 
    assert( outerRadius == 100.f ); 
}


void test_set_meta_get_meta()
{
    std::cout << "test_set_meta_get_meta" << std::endl ; 

    NP* a = NP::Make<float>( 1, 4, 4); 

    a->set_meta<float>( "red", 1.f ); 
    a->set_meta<float>( "green", 2.f ); 
    a->set_meta<float>( "blue", 3.f ); 

    const char* msg = "test_set_meta_get_meta" ; 

    a->set_meta<std::string>( "msg", msg ); 

    std::cout << a->meta << std::endl ; 


    float red = a->get_meta<float>("red", -1.f ); 
    float green = a->get_meta<float>("green", -1.f ); 
    float blue = a->get_meta<float>("blue", -1.f ); 

    assert( red == 1.f ); 
    assert( green == 2.f ); 
    assert( blue == 3.f ); 

    std::string msg2 = a->get_meta<std::string>("msg", "" ) ; 

    assert( strcmp( msg2.c_str(), msg) == 0 );

    std::cout << " msg2 : " << msg2 << std::endl; 
}



int main(int argc, char** argv)
{
    test_SetMeta_GetMeta(); 
    test_set_meta_get_meta();

    return 0 ; 
}
