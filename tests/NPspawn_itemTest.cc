// name=NPspawn_itemTest ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name

const char* FOLD = "/tmp/NPspawn_itemTest" ; 
#include "NP.hh"

int main(int argc, char** argv)
{
    NP* src = NP::Make<float>(10, 2, 2, 2, 4, 4 ) ; 
    src->fillIndexFlat(); 

    std::cout << " src " << src->desc() << std::endl ; 
    src->save(FOLD, "src.npy" ); 

    for(unsigned i=0 ; i < src->shape[0] ; i++)
    {
        NP* dst = src->spawn_item(i) ; 
        std::string name = U::FormName("i", i, ".npy" ); 
        std::cout << " dst " << dst->desc() << " name " << name << std::endl ; 
        dst->save(FOLD, name.c_str()); 
    }
}

