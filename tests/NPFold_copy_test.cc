/**
NPFold_copy_test.cc
====================

~/np/tests/NPFold_copy_test.sh

TEST=deepcopy ~/np/tests/NPFold_copy_test.sh

**/

#include "NPFold.h"

struct NPFold_copy_test
{
    static const char* TEST ;

    static NPFold* MakeFold(); 

    static int shallowcopy();
    static int deepcopy();
    static int meta();
 
    static int Main(); 
};

const char* NPFold_copy_test::TEST = U::GetEnv("TEST", "ALL") ; 

 

NPFold* NPFold_copy_test::MakeFold()
{
    const char* _a = "0 0\n1 1\n2 2\n3 3" ; 
    const char* _b = "0 0\n1 1\n2 2\n3 3\n4 4" ; 
    const char* _c = "0 0\n1 1\n2 2\n3 3\n4 4\n5 5" ; 

    NPFold* x = new NPFold ; 
    x->add("a", NP::LoadFromString<int>(_a)); 
    x->add("b", NP::LoadFromString<int>(_b)); 
    x->add("c", NP::LoadFromString<int>(_c));

    NPFold* y = new NPFold ; 
    y->add("a", NP::LoadFromString<int>(_a)); 
    y->add("b", NP::LoadFromString<int>(_b)); 
    y->add("c", NP::LoadFromString<int>(_c));

    NPFold* z = new NPFold ; 
    z->add("a", NP::LoadFromString<int>(_a)); 
    z->add("b", NP::LoadFromString<int>(_b)); 
    z->add("c", NP::LoadFromString<int>(_c));

    NPFold* zx = new NPFold ; 
    zx->add("a", NP::LoadFromString<int>(_a)); 
    zx->add("b", NP::LoadFromString<int>(_b)); 
    zx->add("c", NP::LoadFromString<int>(_c));

    NPFold* zy = new NPFold ; 
    zy->add("a", NP::LoadFromString<int>(_a)); 
    zy->add("b", NP::LoadFromString<int>(_b)); 
    zy->add("c", NP::LoadFromString<int>(_c));

    NPFold* zz = new NPFold ; 
    zz->add("a", NP::LoadFromString<int>(_a)); 
    zz->add("b", NP::LoadFromString<int>(_b)); 
    zz->add("c", NP::LoadFromString<int>(_c));

    z->add_subfold("zx", zx ); 
    z->add_subfold("zy", zy ); 
    z->add_subfold("zz", zz ); 

    NPFold* top = new NPFold ; 
    top->add_subfold("x", x ); 
    top->add_subfold("y", y ); 
    top->add_subfold("z", z ); 


    if(0) std::cout 
        << "top.desc "
        << std::endl   
        << top->desc() 
        << std::endl   
        ; 

    top->set_verbose_r(); 
    return top ; 
}


int NPFold_copy_test::shallowcopy()
{
    NPFold* f = MakeFold(); 
    NPFold* fc = f->shallowcopy("a,b,c"); 

    std::cout 
        << "[NPFold_copy_test::shallowcopy\n"
        << " fc.desc\n"
        << fc->desc() 
        << "\n"
        << "]NPFold_copy_test::shallowcopy\n"
        ; 

    const char* q_key = "b" ; 

    std::vector<const NP*> f_aa ; 
    std::vector<std::string> f_tt ; 
    f->find_arrays_with_key_r(f_aa, f_tt, q_key); 

    std::vector<const NP*> fc_aa ; 
    std::vector<std::string> fc_tt ; 
    fc->find_arrays_with_key_r(fc_aa, fc_tt, q_key); 

    std::cout << "f\n"  << NPFold::DescArraysAndPaths( f_aa, f_tt )   << "\n" ; 
    std::cout << "fc\n" << NPFold::DescArraysAndPaths( fc_aa, fc_tt ) << "\n" ; 

    assert( f_aa.size() == fc_aa.size() ) ; 

    fc->save("$FOLD/$TEST");  
    return 0 ; 
}

int NPFold_copy_test::deepcopy()
{
    NPFold* f = MakeFold(); 
    NPFold* fc = f->deepcopy("a,b,c"); 

    std::cout 
        << "[NPFold_copy_test::deepcopy\n"
        << " fc.desc\n"
        << fc->desc() 
        << "\n"
        << "]NPFold_copy_test::deepcopy\n"
        ; 

    const char* q_key = "b" ; 

    std::vector<const NP*> f_aa ; 
    std::vector<std::string> f_tt ; 
    f->find_arrays_with_key_r(f_aa, f_tt, q_key); 

    std::vector<const NP*> fc_aa ; 
    std::vector<std::string> fc_tt ; 
    fc->find_arrays_with_key_r(fc_aa, fc_tt, q_key); 

    std::cout << "f\n"  << NPFold::DescArraysAndPaths( f_aa, f_tt )   << "\n" ; 
    std::cout << "fc\n" << NPFold::DescArraysAndPaths( fc_aa, fc_tt ) << "\n" ; 

    assert( f_aa.size() == fc_aa.size() ) ; 


    fc->save("$FOLD/$TEST");  
    return 0 ; 
}

int NPFold_copy_test::meta()
{ 
    NPFold* f = new NPFold ; 
    f->meta = "hello:world" ; 

    NPFold* c = f->shallowcopy() ; 
    c->save("$FOLD/$TEST"); 
    std::cout << c->descMetaKV() << std::endl ; 

    return 0 ; 
}

int NPFold_copy_test::Main()
{
    bool ALL = strcmp(TEST, "ALL") == 0 ; 
    int rc = 0 ;

    if(ALL||strcmp(TEST,"shallowcopy")==0)   rc+=shallowcopy();
    if(ALL||strcmp(TEST,"deepcopy")==0)      rc+=deepcopy(); 
    if(ALL||strcmp(TEST,"meta")==0)          rc+=meta(); 

    return rc ; 
}

int main(){ return NPFold_copy_test::Main() ; }

