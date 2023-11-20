// ./NPFold_copy_test.sh

#include "NPFold.h"



void test_copy()
{
    const char* _a = "0 0\n1 1\n2 2\n3 3" ; 
    const char* _b = "0 0\n1 1\n2 2\n3 3\n4 4" ; 
    const char* _c = "0 0\n1 1\n2 2\n3 3\n4 4\n5 5" ; 

    NP* a = NP::LoadFromString<int>(_a) ; 
    NP* b = NP::LoadFromString<int>(_b) ; 
    NP* c = NP::LoadFromString<int>(_c) ; 

    NPFold* f = new NPFold ; 
    f->add("a",a); 
    f->add("b",b); 
    f->add("c",c);

    std::cout 
        << "f.desc "
        << std::endl   
        << f->desc() 
        << std::endl   
        ; 

    bool shallow = true ; 
    NPFold* fc = f->copy("a,b,c", shallow); 

    std::cout 
        << "fc.desc "
        << std::endl   
        << fc->desc() 
        << std::endl   
        ; 


    const NP* b2 = fc->get("b"); 
    std::cout << " b2 " << b2->desc() << std::endl ; 

    if(shallow == true)
    {
        assert( b2 == b ); 
    }
    else
    {
        assert( b2 != b ); 
    }

    f->save("$FOLD");  
}

void test_copy_all()
{ 
    NPFold* f = new NPFold ; 
    f->meta = "hello:world" ; 

    bool shallow = true ; 
    NPFold* c = f->copy_all(shallow) ; 

    c->save("$FOLD"); 
    std::cout << c->descMetaKV() << std::endl ; 
}


int main()
{
    /*
    test_copy(); 
    */
    test_copy_all(); 

    return 0 ; 
}
