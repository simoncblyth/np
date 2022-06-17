//  ./NP_Load_Concatenate_test.sh 

#include "NP.hh"

void test_Setup(const char* path)
{
    NP* a = NP::Make<float>(2,4,4) ; 
    a->fillIndexFlat(); 

    NP* b = NP::Make<float>(1,4,4) ; 
    b->fillIndexFlat(); 

    NP* c = NP::Make<float>(3,4,4) ; 
    c->fillIndexFlat(); 

    NP* d = NP::Make<float>(4,4,4) ; 
    d->fillIndexFlat(); 

    a->save(path, "a.npy"); 
    b->save(path, "b.npy"); 
    c->save(path, "c.npy"); 
    d->save(path, "d.npy"); 
}

void test_DirList(const char* path)
{
    std::vector<std::string> names ; 
    U::DirList(names, path, NP::EXT ); 
    U::Trim(names, NP::EXT ); 
    std::cout << U::Desc(names) << std::endl ; 
}

void test_Load_Concatenate(const char* path)
{
    NP* a = NP::Load(path); 
    std::cout << " a.brief " << a->brief() << std::endl ; 
    a->save(path, "concat/concat.npy"); 
}


int main(int argc, char** argv)
{
    const char* path = "/tmp/NP_Load_Concatenate_test" ; 
    test_Setup(path); 
    test_DirList(path); 
    test_Load_Concatenate(path); 
    return 0 ; 
}
