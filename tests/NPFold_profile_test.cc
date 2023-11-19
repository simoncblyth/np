#include "NPFold.h"

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ;   
    if(path == nullptr) return 0 ; 

    NPFold* f = NPFold::Load(path); 
    //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 
    const char* prefix = "//p" ; 

    NPFold* ab = f->subprofile_ab("//p", "//n"); 
    ab->save("$FOLD"); 

    return 0 ; 
}



/*
    //NPFold::subprofile(const char* prefix) const 

    bool dump = false ; 
    const char* loaddir = f->loaddir ; 

    std::vector<const NPFold*> subs ; 
    std::vector<std::string> subpaths ; 
    f->find_subfold_with_prefix(subs, subpaths,  prefix );  
    assert( subs.size() == subpaths.size() ); 



    int num_sub = int(subs.size()) ; 
    int num_prof = num_sub > 0 ? subs[0]->getMetaNumProfile() : 0 ;  

    std::cout 
        << " num_sub " << num_sub 
        << " sub0.num_prof " << num_prof 
        << std::endl
        ; 

    int ni = num_sub ; 
    int nj = num_prof ; 
    int nk = 3 ;   

    NP* t = NP::Make<int64_t>( ni, nj, nk ) ; 
    int64_t* tt = t->values<int64_t>() ; 
    t->set_meta<std::string>("base", loaddir ? loaddir : "-" ); 
    t->set_meta<std::string>("prefix", prefix ? prefix : "-" ); 

    std::vector<std::string> comkeys ; 
    for(int i=0 ; i < ni ; i++) 
    {
        const NPFold* sub = subs[i] ; 
        const char* subpath = subpaths[i].c_str() ; 

       
        if(dump) std::cout 
            << subpath 
            << std::endl
            << sub->descMetaKV()
            << std::endl
            ; 

        std::vector<std::string> keys ; 
        std::vector<std::string> vals ; 
        bool only_with_profiles = true ; 
        sub->getMetaKV(&keys, &vals, only_with_profiles ); 
        assert( vals.size() == keys.size() ) ; 
        assert( int(vals.size()) == nj ) ; 

        if(i == 0) comkeys = keys ; 
        bool same_keys = i == 0 ? true : keys == comkeys ; 
        std::cout << sub->loaddir << " keys.size " << keys.size() << " " << ( same_keys ? "Y" : "N" ) << std::endl; 
        assert(same_keys); 

        for(int j=0 ; j < nj ; j++) 
        {
            const char* v = vals[j].c_str(); 
            std::vector<int64_t> elem ; 
            U::MakeVec<int64_t>( elem, v, ',' ); 
            assert( elem.size() == nk ); 
            for(int k=0 ; k < nk ; k++)  tt[i*nj*nk+j*nk+k] = elem[k] ; 
        }
        t->names.push_back(subpath); 
    }
    NPFold* out = new NPFold ; 
    out->add("profile", t );
    out->add("labels", NPX::MakeCharArray(comkeys) );  
*/




