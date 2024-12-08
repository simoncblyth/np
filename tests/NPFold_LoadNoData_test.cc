/**

~/np/tests/NPFold_LoadNoData_test.sh
TEST=run ~/np/tests/NPFold_LoadNoData_test.sh
TEST=substamp ~/np/tests/NPFold_LoadNoData_test.sh


**/

#include "NPFold.h"

struct NPFold_LoadNoData_test
{
    static const char* TEST ; 
    static bool VERBOSE ;
    static int main(int argc, char** argv);

    NPFold* f ; 
    NPFold_LoadNoData_test(const char* dirp); 

    int run();  
    int substamp();  

    int test(); 
}; 

const char* NPFold_LoadNoData_test::TEST = U::GetEnv("TEST", "ALL") ; 
bool        NPFold_LoadNoData_test::VERBOSE = getenv("VERBOSE") != nullptr ; 

int NPFold_LoadNoData_test::main(int argc, char** argv)
{
    const char* dirp = argc > 1 ? argv[1] : U::PWD() ;   
    if(dirp == nullptr) return 0 ; 

    std::cout 
        << argv[0]
        << std::endl
        << "NPFold::LoadNoData(\"" << dirp << "\")" 
        << std::endl
        ;   



    NPFold_LoadNoData_test t(dirp); 
    return t.test(); 
}


NPFold_LoadNoData_test::NPFold_LoadNoData_test(const char* dirp)
    :
    f(NPFold::LoadNoData(dirp))
{
    if(VERBOSE) std::cout 
        << "[" << ".VERBOSE\n"
        << ( f ? f->desc() : "-" ) << "\n"
        << "]" << ".VERBOSE\n"
        ;
}


int NPFold_LoadNoData_test::test()
{
    bool ALL = strcmp(TEST, "ALL") == 0 ; 
    int rc = 0 ; 
    if(ALL||0==strcmp(TEST, "run"))      rc += run(); 
    if(ALL||0==strcmp(TEST, "substamp")) rc += substamp(); 
    return rc ; 
}


int NPFold_LoadNoData_test::run()
{
    const NP* run = f->get("run"); 
    std::cout 
        << " run " << ( run ? run->sstr() : "-" ) 
        << std::endl 
        << ( run ? run->meta : "-" ) 
        << std::endl 
        << ( run ? run->descMetaKV() : "-" ) 
        << std::endl 
        << ( run ? run->descMetaKVS() : "-" ) 
        << std::endl 
        ; 
    return 0 ; 
}

int NPFold_LoadNoData_test::substamp()
{
    NPFold* s = f->subfold_summary("substamp", "a://A", "b://B"); 
    assert(s); 
    return 0 ; 
}



int main(int argc, char** argv)
{
    return NPFold_LoadNoData_test::main(argc, argv); 
}


// ~/np/tests/NPFold_LoadNoData_test.sh

