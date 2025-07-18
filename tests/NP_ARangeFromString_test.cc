#include "NPFold.h"

// ~/np/tests/NP_ARangeFromString_test.sh

struct NP_ARangeFromString_test
{
    static int Integer();
    static int Float();
    static int Main();
};

inline int NP_ARangeFromString_test::Integer()
{
    const char* spec0 = "[20000:45600]" ;
    NP* a0 = NP::ARange_FromString<int>( spec0 );
    assert( a0 && a0->num_items() == 25600 );
    a0->set_meta<std::string>("spec", spec0);

    const char* spec1 = "[20000:45600:2]" ;
    NP* a1 = NP::ARange_FromString<int>( spec1 );
    assert( a1 && a1->num_items() == 25600/2 );
    a1->set_meta<std::string>("spec", spec1);

    NPFold* sub = new NPFold ;
    sub->add("a0", a0);
    sub->add("a1", a1);

    NPFold* top = new NPFold ;
    top->add_subfold("Integer", sub );
    top->save("$FOLD");


    return 0;
}

inline int NP_ARangeFromString_test::Float()
{
    static const int N = 6 ;

    std::array<const char*,N> spec =
     {{
        "[0:101:10]",           // 0:
        "[1:10.001:0.5]",       // 1:
        "[0:1:0.1]",            // 2: ends at 0.9 not 1.0
        "[0:1.01:0.1]",         // 3: ends at 1.0
        "[100.]",               // 4:
        "[100.:101.:1.]"        // 5: same as 4:
     }} ;

    std::array<NP*,N> a = {} ;

    NPFold* sub = new NPFold ;
    for(int i=0 ; i < N ; i++)
    {
        a[i] = NP::ARange_FromString<float>( spec[i] );
        assert( a[i] );
        a[i]->set_meta<std::string>("spec", spec[i]);
        sub->add( i, a[i], 'a' );
    }

    assert( a[0]->num_items() == 11 );
    assert( a[1]->num_items() == 19 );
    assert( a[2]->num_items() == 10 );
    assert( a[3]->num_items() == 11 );
    assert( a[4]->num_items() == 1 );
    assert( a[5]->num_items() == 1 );

    NPFold* top = new NPFold ;
    top->add_subfold("Float", sub );
    top->save("$FOLD");

    return 0;
}

inline int NP_ARangeFromString_test::Main()
{
    const char* TEST = U::GetEnv("TEST", "ALL");
    bool ALL = strcmp(TEST,"ALL") == 0 ;
    int rc = 0 ;
    if(ALL||0==strcmp(TEST,"Integer")) rc += Integer();
    if(ALL||0==strcmp(TEST,"Float"))   rc += Float();
    return rc ;
}


int main()
{
    return NP_ARangeFromString_test::Main();
}
