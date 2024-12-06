/**

~/np/tests/NPFold_concat_test.sh
TEST=trivial ~/np/tests/NPFold_concat_test.sh
TEST=concat ~/np/tests/NPFold_concat_test.sh

**/

#include "NPFold.h"


struct NPFold_concat_test
{
    static NPFold* make_fold_0(); 
    static NPFold* make_fold(int nsub); 

    static int maxdepth(); 
    static int can_concat(); 
    static int concat0(); 
    static int concat(); 
    static int trivial(); 

    static int Main(); 
};




NPFold* NPFold_concat_test::make_fold_0()
{
    NPFold* top = new NPFold ; 
    {
        NPFold* f1a = new NPFold ; 
        NPFold* f1b = new NPFold ; 
        top->add_subfold(0, f1a, 'f') ; 
        top->add_subfold(1, f1b, 'f') ; 

        NP* a = NP::Linspace<int>(0, 100, 101) ; 
        NP* b = NP::Linspace<int>(0, 100, 101) ; 
        f1a->add("a", a ); 
        f1b->add("a", b ); 

        std::cout << " a        " << ( a ? a->sstr() : "-" ) << "\n" ;  
        std::cout << " b        " << ( b ? b->sstr() : "-" ) << "\n" ;  
   }
   return top ; 
}


NPFold* NPFold_concat_test::make_fold(int nsub)
{
    NPFold* top = new NPFold ; 
    for(int i=0 ; i < nsub ; i++ )
    {
        NPFold* sub = top->add_subfold();  ; 
        NP* a = NP::Linspace<int>(0, 100, 101) ; 
        NP* b = NP::Linspace<int>(0, 100, 101) ; 
        sub->add("a", a ); 
        sub->add("b", b ); 
    }
    return top ; 
}


int NPFold_concat_test::maxdepth()
{
    {
        NPFold* f0 = new NPFold ; 
        assert( f0->maxdepth() == 0 ); 
    }
    {
        NPFold* f0 = new NPFold ; 
        NPFold* f1a = new NPFold ; 
        NPFold* f1b = new NPFold ; 
        f0->add_subfold(0, f1a, 'f') ; 
        f0->add_subfold(1, f1b, 'f') ; 
        assert( f0->maxdepth() == 1 ); 
        assert( f1a->maxdepth() == 0 ); 
        assert( f1b->maxdepth() == 0 ); 
    }
    return 0 ; 
}

int NPFold_concat_test::can_concat()
{
    {
        NPFold* f0 = new NPFold ; 
        assert( f0->can_concat() == false ); 
    }
    {
        NPFold* f0 = new NPFold ; 
        NPFold* f1a = new NPFold ; 
        NPFold* f1b = new NPFold ; 
        f0->add_subfold(0, f1a, 'f') ; 
        f0->add_subfold(1, f1b, 'f') ; 

        std::stringstream ss ; 
        bool can = f0->can_concat(&ss) ; 
        std::cout << ss.str() << "\n" ; 
        assert( can == false );  
    }
    {
        NPFold* top = make_fold(3); 
        std::stringstream ss ; 
        bool can = top->can_concat(&ss) ; 
        std::cout << ss.str() << "\n" ; 
        assert( can == true );  
    }
    return 0 ; 
}


 
int NPFold_concat_test::concat0()
{
    std::stringstream ss ; 
    std::ostream* out = &ss ; 

    NPFold* top = make_fold_0(); 

    top->concat(out) ; 
    top->clear_subfold();  

    // following clear_subfold null-ify any stale pointers
    // whose objects are deleted by the clear
    // or close scope and make sure not to hold
    // on to any transient pointers 

    if(out) std::cout << ss.str() ; 

    const NP* a_concat = top->get("a"); 
    std::cout << " a_concat " << ( a_concat ? a_concat->sstr() : "-" ) << "\n" ;  

    top->save("$FOLD/concat0"); 
    return 0 ; 
}


int NPFold_concat_test::concat()
{
    std::stringstream ss ; 
    std::ostream* out = &ss ; 

    NPFold* top = make_fold(5); 

    top->concat(out) ; 
    top->clear_subfold();  

    if(out) std::cout << ss.str() ; 

    const NP* a = top->get("a"); 
    std::cout << " a " << ( a ? a->sstr() : "-" ) << "\n" ;  

    top->save("$FOLD/concat"); 
    return 0 ; 
}



int NPFold_concat_test::trivial()
{
    std::stringstream ss ; 
    std::ostream* out = &ss ; 

    NPFold* top = new NPFold ; 

    NP* a = nullptr ; 
    {
        NPFold* f1a = new NPFold ; 
        top->add_subfold(0, f1a, 'f') ; 

        a = NP::Linspace<int>(0, 100, 101) ; 
        std::cout << " a        " << ( a ? a->sstr() : "-" ) << "\n" ;  

        f1a->add("a", a ); 

        top->concat(out) ; 
        top->clear_subfold();  
    }

    if(out) std::cout << ss.str() ; 

    const NP* a_concat = top->get("a"); 
    std::cout << " a_concat " << ( a_concat ? a_concat->sstr() : "-" ) << "\n" ;  
    assert( a_concat == a );

    top->save("$FOLD/trivial"); 
    return 0 ; 
}
 

 


int NPFold_concat_test::Main()
{
    const char* TEST = U::GetEnv("TEST", "ALL"); 
    bool ALL = strcmp(TEST, "ALL") == 0 ; 
    int rc = 0 ; 
    if(ALL||strcmp(TEST,"maxdepth")==0)   rc += maxdepth(); 
    if(ALL||strcmp(TEST,"can_concat")==0) rc += can_concat(); 
    if(ALL||strcmp(TEST,"concat0")==0)    rc += concat0(); 
    if(ALL||strcmp(TEST,"concat")==0)     rc += concat(); 
    if(ALL||strcmp(TEST,"trivial")==0)    rc += trivial(); 
    return rc ; 
}

int main(){ return NPFold_concat_test::Main() ; }


