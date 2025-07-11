#include "NPFold.h"

struct NP_LoadSlice_test
{
    static int LoadSliceWhere();
    static int LoadSliceLarge();
    static int LoadSlice();
    static int Main();
};

int NP_LoadSlice_test::LoadSlice()
{
    const char* path = "$AFOLD/record.npy" ;
    const char* sli = "$AFOLD_RECORD_SLICE" ;

    NP* a = NP::Load( path );
    NP* b = NP::LoadSlice( path, sli );

    NPFold* fold = new NPFold ;
    fold->add("a", a);
    fold->add("b", b);
    fold->save("$FOLD/LoadSlice");

    std::cout
        << "NP_LoadSlice_test::LoadSlice\n"
        << " a " << a->sstr() << " a.lpath " << a->lpath << "\n"
        << " b " << b->sstr() << " b.lpath " << b->lpath << "\n"
        << "\n"
        ;

    return 0 ;
}
int NP_LoadSlice_test::LoadSliceLarge()
{
    const char* path = "$AFOLD/record.npy" ;
    const char* sli = "$AFOLD_RECORD_SLICE" ;
    NP* b = NP::LoadSlice( path, sli );
    std::cout
        << "NP_LoadSlice_test::LoadSliceLarge\n"
        << " b " << b->sstr()
        << " b.lpath " << b->lpath
        << "\n"
        ;

    NPFold* fold = new NPFold ;
    fold->add("b", b);
    fold->save("$FOLD/LoadSliceLarge");

    return 0 ;
}

int NP_LoadSlice_test::LoadSliceWhere()
{
    const char* path = "$AFOLD/record.npy" ;
    const char* sli = "$AFOLD_RECORD_SLICE" ;
    NP* b = NP::LoadSlice( path, sli );
    std::cout
        << "NP_LoadSlice_test::LoadSliceWhere\n"
        << " b " << b->sstr()
        << " b.lpath " << b->lpath
        << "\n"
        ;

    NPFold* fold = new NPFold ;
    fold->add("b", b);
    fold->save("$FOLD/LoadSliceWhere");

    return 0 ;
}





int NP_LoadSlice_test::Main()
{
    const char* TEST = U::GetEnv("TEST", "LoadSlice" );
    int rc = 0 ;
    if(strcmp(TEST,"LoadSlice")      == 0) rc += LoadSlice();
    if(strcmp(TEST,"LoadSliceLarge") == 0) rc += LoadSliceLarge();
    if(strcmp(TEST,"LoadSliceWhere") == 0) rc += LoadSliceWhere();
    return rc ;
}


int main()
{
    return NP_LoadSlice_test::Main();
}





