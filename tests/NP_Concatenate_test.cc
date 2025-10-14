// ~/np/tests/NP_Concatenate_test.sh 

#include "NPFold.h"

struct NP_Concatenate_test
{
    static int test_0();
    static int test_1();
};


int NP_Concatenate_test::test_0()
{
    NP* a = NP::Make<int>( 2, 3 ); 
    int* aa = a->values<int>(); 
    for(int i=0 ; i < a->num_values() ; i++) aa[i] = i ; 

    NP* b = NP::Make<int>( 2, 3 ); 
    int* bb = b->values<int>(); 
    for(int i=0 ; i < b->num_values() ; i++) bb[i] = i ; 

    NP* c = NP::Make<int>( 2, 3 ); 
    int* cc = c->values<int>(); 
    for(int i=0 ; i < c->num_values() ; i++) cc[i] = i ; 

    std::vector<NP*> subs ; 
    subs.push_back(a);  
    subs.push_back(b);  
    subs.push_back(c);  

    NP* com = NP::Concatenate( subs ); 
    std::cout << com->sstr() << std::endl ; 

    std::vector<const NP*> csubs ; 
    csubs.push_back(const_cast<const NP*>(a));  
    csubs.push_back(const_cast<const NP*>(b));  
    csubs.push_back(const_cast<const NP*>(c));  

    NP* ccom = NP::Concatenate( csubs ); 
    std::cout << ccom->sstr() << std::endl ; 

    std::vector<NP*> isubs ; 
    isubs.push_back(NP::Incremented(a,0));  
    isubs.push_back(NP::Incremented(b,100));  
    isubs.push_back(NP::Incremented(c,200));  

    NP* icom = NP::Concatenate( isubs ); 
    std::cout << icom->sstr() << std::endl ; 

    NPFold* fold = new NPFold ; 
    fold->add("a", a); 
    fold->add("b", b); 
    fold->add("c", c); 
    fold->add("com", com); 
    fold->add("ccom", ccom); 
    fold->add("icom", icom); 

    fold->save("$FOLD"); 

    return 0 ;
}

int NP_Concatenate_test::test_1()
{
    //NP::UINT mx = 0xffff ; 
    //NP::UINT mx = 100000000 ;    // 0.1 billion  (100M)  completes
    //NP::UINT mx = 200000000 ;    // 0.2 billion  (200M)  completes
    NP::UINT mx   = 400000000 ;    // 0.4 billion  (400M)  completes, combined array is 76G

    //NP::UINT mx = 1000000000 ;    // 1 billion   KILLED during alloc of combined 3 billion array
    //NP::UINT mx = 0x7fffffff ;  // 2.14 billion  KILLED
    //NP::UINT mx = 0xffffffff ;  // 4.29 billion
    std::cout << U::FormatLog("NP_Concatenate_test::test_1 mx ") << mx << "\n" ; 
 
    std::cout << U::FormatLog("NP_Concatenate_test::test_1.a.make\n") ;
    NP* a = NP::Make<int>( mx, 4, 4 );  
    std::cout << U::FormatLog("NP_Concatenate_test::test_1.a.fill\n") ;
    a->fill<int>(1) ;

    std::cout << U::FormatLog("NP_Concatenate_test::test_1.b.make\n") ;
    NP* b = NP::Make<int>( mx, 4, 4 );  
    std::cout << U::FormatLog("NP_Concatenate_test::test_1.b.fill\n") ;
    b->fill<int>(2) ;

    std::cout <<  U::FormatLog("NP_Concatenate_test::test_1.c.make\n") ;
    NP* c = NP::Make<int>( mx, 4, 4 );  
    std::cout <<  U::FormatLog("NP_Concatenate_test::test_1.c.fill\n") ;
    c->fill<int>(3) ;

    std::cout <<  U::FormatLog("NP_Concatenate_test::test_1.subs\n") ;
    std::vector<NP*> subs ; 
    subs.push_back(a);  
    subs.push_back(b);  
    subs.push_back(c);  

    std::cout << U::FormatLog("NP_Concatenate_test::test_1.Concatenate[\n") ;
    NP* com = NP::Concatenate( subs ); 
    std::cout << U::FormatLog("NP_Concatenate_test::test_1.Concatenate]\n") ;

    std::cout << U::FormatLog("NP_Concatenate_test::test_1.fold[\n") ;
    NPFold* fold = new NPFold ; 
    fold->add("a", a); 
    fold->add("b", b); 
    fold->add("c", c); 
    fold->add("com", com); 
    fold->save("$FOLD"); 
    std::cout <<  U::FormatLog("NP_Concatenate_test::test_1.fold]\n") ;
 
    return 0 ;
}

int main()
{
   return NP_Concatenate_test::test_1();
}
