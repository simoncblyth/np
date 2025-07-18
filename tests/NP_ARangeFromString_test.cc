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
    static const int N = 3 ;

    std::array<NP*,N> a = {} ;
    std::array<const char*,N> spec =
     {{
         "[20000:45600]",      // 0
         "[20000:45600:2]",    // 1
         "[20000:45600:-10]"   // 2  -ve step switches to linspace
     }} ;

    NPFold* sub = new NPFold ;
    for(int i=0 ; i < N ; i++)
    {
        a[i] = NP::ARange_FromString<int>( spec[i] );
        assert( a[i] );
        a[i]->set_meta<std::string>("spec", spec[i]);
        sub->add( i, a[i], 'a' );
    }

    assert( a[0]->num_items() == 25600 );
    assert( a[1]->num_items() == 25600/2 );
    assert( a[2]->num_items() == 10 );

    NPFold* top = new NPFold ;
    top->add_subfold("Integer", sub );
    top->save("$FOLD");

    return 0;
}

inline int NP_ARangeFromString_test::Float()
{
    static const int N = 7 ;

    std::array<NP*,N> a = {} ;
    std::array<const char*,N> spec =
     {{
        "[0:101:10]",           // 0:
        "[1:10.001:0.5]",       // 1:
        "[0:1:0.1]",            // 2: ends at 0.9 not 1.0
        "[0:1.01:0.1]",         // 3: ends at 1.0
        "[100.]",               // 4:
        "[100.:101.:1.]",       // 5: same as 4:
        "[0.1:88.8:-20]"        // 6: -ve step switches to linspace
     }} ;


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
    assert( a[6]->num_items() == 20 );

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
