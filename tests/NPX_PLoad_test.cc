#include "NPX.h"
#include "NPFold.h"

int main()
{
    const char* base = "$HOME/opticks/sysrap" ;
    NP* n = NPX::PLoad<double>(base,"RINDEX_Water_Hale_n.txt") ;
    NP* k = NPX::PLoad<double>(base,"RINDEX_Water_Hale_k.txt");
    // source wl domain units are um, scale by 1000. to give nm
    n->pscale<double>(1000., 0);
    k->pscale<double>(1000., 0);

    std::cout << " n " << ( n ? n->sstr() : "-" ) << "\n" ;
    std::cout << " k " << ( k ? k->sstr() : "-" ) << "\n" ;

    NPFold* fold = new NPFold ;
    fold->add("n", n);
    fold->add("k", k);
    fold->save("$FOLD");

    return 0 ;
}
