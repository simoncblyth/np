// ~/np/tests/NPFold_clear_except_test.sh

#include "NPFold.h"

NPFold* make_fold()
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

    return f ; 
}

void test_clear_except()
{
    NPFold* f = make_fold(); 
    const NP* b = f->get("b"); 

    f->headline = "(before clear_except)" ; 

    std::cout << f->desc() ; 

    bool copy = false ; 
    //bool copy = true ; 
    f->clear_except("b", copy); 
    f->headline = "(after clear_except)" ; 

    std::cout << f->desc() ; 


    const NP* b2 = f->get("b"); 
    std::cout << " b2 " << b2->desc() << std::endl ; 

    if(copy == false)
    {
        assert( b2 == b ); 
    }

    f->save("$FOLD");  
}



void test_clear_only(bool copy)
{
    NPFold* f = make_fold(); 
    const NP* a = f->get("a"); 
    [[maybe_unused]] const NP* b = f->get("b"); 
    const NP* c = f->get("c"); 

    f->headline = "(before clear_only)" ; 

    std::cout << f->desc() ; 

    f->clear_only("b", copy); 
    f->headline = "(after clear_only)" ; 

    std::cout << f->desc() ; 

    const NP* a2 = f->get("a"); 
    const NP* b2 = f->get("b"); 
    const NP* c2 = f->get("c"); 

    std::cout << " a2 " << ( a2 ? a2->desc() : "-" ) << std::endl ; 
    std::cout << " b2 " << ( b2 ? b2->desc() : "-" ) << std::endl ; 
    std::cout << " c2 " << ( c2 ? c2->desc() : "-" ) << std::endl ; 

    if(copy)
    {
        assert( a2 != a ); 
        assert( b2 == nullptr ); 
        assert( c2 != c ); 
    }
    else
    {
        assert( a2 == a ); 
        assert( b2 == nullptr ); 
        assert( c2 == c ); 
    }


    f->save("$FOLD");  
}

int main()
{
    /*
    test_clear_except(); 
    test_clear_only(false); 
    */
    test_clear_only(true); 
    return 0 ; 
}
