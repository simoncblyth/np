#include "NPFold.h"

int main()
{
    NP* a = NP::ARange_FromString<int>( "[20000:45600]" );
    assert( a && a->num_items() == 25600 );

    NPFold* f = new NPFold ;
    f->add("a", a );
    f->save("$FOLD");

    return 0 ;
}
