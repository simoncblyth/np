// ~/np/tests/NP_Concatenate_test.sh 

#include "NPFold.h"

void test_0()
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
}



int main()
{
   test_0(); 
   return 0 ; 
}
