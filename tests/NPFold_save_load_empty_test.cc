/**
NPFold_save_load_empty_test.cc
=================================

::

     ~/np/tests/NPFold_save_load_empty_test.sh





**/

#include "NPFold.h"


int main(int argc, char** argv)
{
    NPFold* a = new NPFold ;
    a->add("a", NP::Make<int>(1) );

    NPFold* b = new NPFold ;

    //b->add("b", NP::Make<int>(1) );
    std::string bmeta = "fold_with_just_metadata_not_saved_unless_set_allowonly_meta" ;
    b->set_meta<std::string>("bmeta", bmeta);


    NPFold* c = new NPFold ;
    c->add("c", NP::Make<int>(1) );


    NPFold* fold = new NPFold ;
    fold->add_subfold( "a", a  );
    fold->add_subfold( "b", b  );
    fold->add_subfold( "c", c  );

    // THE DEFAULTS OF THE BELOW ARE BOTH FALSE
    //fold->set_allowempty_r();
    //fold->set_allowonlymeta_r();

    fold->save("$FOLD");

    NPFold* fold1 = NPFold::Load("$FOLD") ;
    std::cout << " fold1 " << fold1->desc() << std::endl ;


    return 0 ;
}

// ~/np/tests/NPFold_save_load_empty_test.sh

