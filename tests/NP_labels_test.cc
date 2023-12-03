// ~/np/tests/NP_labels_test.sh 
#include "NP.hh"

int main()
{
    std::vector<std::string> labels = {"red", "green", "blue" } ; 

    const char* path = "$FOLD/a.npy" ;

    NP* a = NP::Make<int>(3,3);
    a->names = labels ; 
    a->labels = new std::vector<std::string>(labels.begin(), labels.end() ) ; 
    std::cout << "a " <<  a->descTable<int>(7) ; 

    a->save(path) ; 

    NP* b = NP::Load(path) ; 
    std::cout << "b " <<  b->descTable<int>(7) ; 

    return 0 ; 
}
// ~/np/tests/NP_labels_test.sh 

