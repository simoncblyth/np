// ~/np/tests/NP_MakePSum_test.sh

#include "NPFold.h"

int main()
{
    int ni = 100 ;
    double dom0 = 100. ;
    double dom1 = 200. ;

    NP* a = NP::MakePRamp<double>( ni, dom0, dom1, 1.,  2. );
    NP* b = NP::MakePRamp<double>( ni, dom0, dom1, 2.,  4. );
    NP* c = NP::MakePRamp<double>( ni, dom0, dom1, 4.,  8. );
    NP* x = NP::MakePRamp<double>( ni, dom0, dom1, 7.,  14. );

    NP* s = NP::MakePSum(a, b, c);

    NP* ia = NP::MakePInverse(a);
    NP* ib = NP::MakePInverse(b);
    NP* ic = NP::MakePInverse(c);

    NP* ra = NP::MakePRatio( a, s );
    NP* rb = NP::MakePRatio( b, s );
    NP* rc = NP::MakePRatio( c, s );


    NPFold* fold = new NPFold ;
    fold->add("a", a);
    fold->add("b", b);
    fold->add("c", c);
    fold->add("x", x);
    fold->add("s", s);

    fold->add("ia", ia);
    fold->add("ib", ib);
    fold->add("ic", ic);

    fold->add("ra", ra);
    fold->add("rb", rb);
    fold->add("rc", rc);


    fold->save("$FOLD");

    return 0 ;
}
