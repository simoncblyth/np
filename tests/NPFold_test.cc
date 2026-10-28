// ~/np/tests/NPFold_test.sh

#include <iostream>
#include "NPFold.h"


struct NPFold_test
{
    static int Demo();
    static int TESTFOLD_LoadSave();
    static int Main();
};

int NPFold_test::Demo()
{
    NPFold* f0 = new NPFold ;
    f0->add("demo.npy", NP::Make<float>(1) );
    f0->add("propcom.npy", nullptr );
    f0->save("$FOLD");

    NPFold* f1 = NPFold::Load("$FOLD");
    std::cout << f1->desc() << std::endl ;
    return 0 ;
}

int NPFold_test::TESTFOLD_LoadSave()
{
    NPFold* fold = NPFold::Load("$TESTFOLD");
    fold->save("$FOLD");
    return 0 ;
}

int NPFold_test::Main()
{
    //return Demo();
    return TESTFOLD_LoadSave();
}


int main()
{
    return NPFold_test::Main() ;
}
