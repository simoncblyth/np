#include "NPFold.h"

int main()
{
    NP* a = NP::Make<float>(100,4,4) ;
    a->fillIndexFlat();
    const char* path = "$FOLD/original.npy" ;
    a->save(path);

    std::vector<int64_t> sel_indices = {0,3,6,99} ;

    NP* b = NP::LoadSelection(path, sel_indices);

    NPFold* f = new NPFold ;
    f->add("a", a);
    f->add("b", b);
    f->save("$FOLD");


    return 0 ;
}
