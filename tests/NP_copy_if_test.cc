// ./NP_copy_if_test.sh 
#include "NPFold.h"


struct int_selector
{
    int cut ; 
    int_selector(int cut_) : cut(cut_) {}; 
    bool operator() (const int* p) const { return *p < cut  ; } 
};

struct int4 
{
    int x, y, z, w ; 
}; 


struct int4_selector
{
    int cut ; 
    int4_selector(int cut_) : cut(cut_) {}; 
    bool operator() (const int4* p) const { return (*p).w < cut  ; }  
}; 

struct int4x4 
{
    int4 x, y, z, w ; 
}; 

struct int4x4_selector
{
    int cut ; 
    int4x4_selector(int cut_) : cut(cut_) {}; 
    bool operator() (const int4x4* p) const { return (*p).w.w < cut  ; }  
}; 



void test_simple_copy_if()
{
    int_selector pred(50) ; 

    NP* a = NP::ARange<int>(0,100,1) ; 

    int n = a->count_if<int>(pred) ; 
    std::cout << "n " << n << std::endl ; 

    NP* b = a->simple_copy_if<int>( pred ); 

    NPFold* f = new NPFold ; 
    f->add("a", a ); 
    f->add("b", b ); 
    f->set_meta<std::string>("test", "test_int");
    f->set_meta<int>("count", n ); 
    f->set_meta<int>("pred.cut", pred.cut ); 
    f->save("$FOLD"); 
}



template<typename S>
void test_copy_if(const NP* a, std::function<bool(const S*)> pred, const char* label  )
{
    int n = a->count_if<S>(pred) ; 
    std::cout << "count_if<S>(pred) :  " << n << std::endl ; 

    NP* b = a->copy_if<int,S>( pred ); 

    NPFold* f = new NPFold ; 
    f->add("a", a ); 
    f->add("b", b ); 
    f->set_meta<std::string>("label", label);
    f->set_meta<int>("count", n ); 
    f->save("$FOLD"); 
}

template<typename S, typename... Args>
void test_flexible_copy_if(const NP* a, std::function<bool(const S*)> pred, Args... itemshape )
{
    int n = a->count_if<S>(pred) ; 
    std::cout << "count_if<S>(pred) :  " << n << std::endl ; 

    NP* b = a->flexible_copy_if<int,S>( pred, std::forward<Args>(itemshape)... ); 

    NPFold* f = new NPFold ; 
    f->add("a", a ); 
    f->add("b", b ); 
    f->set_meta<std::string>("test", "test_int4");
    f->set_meta<int>("count", n ); 
    f->save("$FOLD"); 
}


void test_copy_if_int4()
{
    NP* a = NP::ARange<int>(0,400,1) ; 
    a->change_shape(-1,4); 

    int4_selector pred(50) ; 
    test_copy_if<int4>(a, pred, "test_copy_if_int4" ) ; 
}

void test_copy_if_int4x4()
{
    NP* a = NP::ARange<int>(0,400,1) ; 
    a->change_shape(-1,4,4); 

    int4x4_selector pred(50) ; 
    test_copy_if<int4x4>(a, pred, "test_copy_if_int4x4" ) ; 
}

void test_flexible_copy_if_int4x4()
{
    NP* a = NP::ARange<int>(0,400,1) ; 
    a->change_shape(-1,4,4); 

    int4x4_selector pred(50) ; 
    test_flexible_copy_if<int4x4>(a, pred, 4, 4) ; 
}

int main()
{
    //test_simple_copy_if(); 
    //test_copy_if_int4(); 
    test_copy_if_int4x4(); 
    //test_flexible_copy_if_int4x4(); 

    return 0 ; 
}
