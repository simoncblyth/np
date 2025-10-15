
#include "NP.hh"

struct NP_Load_test
{
    static int save_load();
    static int load();
    static int load_hit();
};

int NP_Load_test::save_load()
{
    NP* a = NP::Make<int>(10,4) ;
    a->fillIndexFlat();
    a->save("$FOLD/a.npy") ;
    std::cout << " a " << a->repr<int>() << std::endl ;

    NP* b = NP::Load("$FOLD/a.npy") ;
    std::cout << " b " << b->repr<int>() << std::endl ;

    return 0 ;
}


int NP_Load_test::load()
{
    NP* c = NP::Load("$FOLD/c.npy") ;
    std::cout << " c " << ( c ? c->sstr() : "-" ) << std::endl ;

    NP* d = NP::Load("$UNDEFINED/d.npy") ;
    std::cout << " d " << ( d ? d->sstr() : "-" ) << std::endl ;

    NP* e = NP::Load("$UNDEFINED") ;
    std::cout << " e " << ( e ? e->sstr() : "-" ) << std::endl ;

    return 0 ;
}

int NP_Load_test::load_hit()
{
    NP* h = NP::Load("$HITFOLD/hit.npy");
    std::cout << " h " << ( h ? h->sstr() : "-" ) << std::endl ;
    return 0 ;
}


int main()
{
    return NP_Load_test::load_hit();
}
