#include "NPFold.h"

NPFold* substamps(const NPFold* f, const char* prefix)
{
    std::vector<const NPFold*> subs ; 
    std::vector<std::string> subpaths ; 
    f->find_subfold_with_prefix(subs, subpaths,  prefix );  
    assert( subs.size() == subpaths.size() ); 

    std::cout 
        << " find_subfold_with_prefix " << prefix
        << " subs.size " << subs.size()
        << std::endl
        ;

    //for(int i=0 ; i < int(subs.size()) ; i++) std::cout << subs[i]->loaddir << std::endl ; 
    //for(int i=0 ; i < int(subs.size()) ; i++) std::cout << subs[i]->desc() << std::endl ; 

    int num_sub = int(subs.size()) ; 
    int num_stamp = num_sub > 0 ? subs[0]->getMetaNumStamp() : 0 ;  

    int ni = num_sub ; 
    int nj = num_stamp ; 

    NP* t = NP::Make<int64_t>( ni, nj ) ; 
    int64_t* tt = t->values<int64_t>() ; 
    t->set_meta<std::string>("base", f->loaddir ? f->loaddir : "-" ); 
    t->set_meta<std::string>("prefix", prefix); 

    std::vector<std::string> comkeys ; 
    for(int i=0 ; i < ni ; i++) 
    {
        const NPFold* sub = subs[i] ; 
        const char* subpath = subpaths[i].c_str() ; 
        std::vector<std::string> keys ; 
        std::vector<int64_t>   stamps ; 
        bool only_with_stamps = true ; 
        sub->getMetaKVS(&keys, nullptr, &stamps, only_with_stamps ); 
        assert( int(stamps.size()) == nj ) ; 

        if(i == 0) comkeys = keys ; 
        bool same_keys = i == 0 ? true : keys == comkeys ; 
        std::cout << sub->loaddir << " stamps.size " << stamps.size() << " " << ( same_keys ? "Y" : "N" ) << std::endl; 
        assert(same_keys); 

        for(int j=0 ; j < nj ; j++) tt[i*nj+j] = stamps[j] ; 
        t->names.push_back(subpath); 
    }
    NPFold* out = new NPFold ; 
    out->add("stamps", t );
    out->add("labels", NPX::MakeCharArray(comkeys) );  

    return out ;  
}

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 

    NPFold* pn = f->substamps_pn(); 
    pn->save("$FOLD"); 

    return 0 ; 
} 



