// ./NP_MakeNarrow5D_test.sh 

#include "NP.hh"

template <typename T>
NP* MakeSrc(unsigned ni, unsigned nj)   // static 
{
    NP* a = NP::Make<T>( ni, nj );  
    T* vv = a->values<T>(); 
    for(unsigned i=0 ; i < ni ; i++)
    {   
        for( unsigned j=0 ; j < nj ; j++)
        {   
            switch(j)
            {   
                case 0:    vv[i*nj+j] = T(i)         ; break ; 
                case 1:    vv[i*nj+j] = T(10*i)      ; break ; 
                case 2:    vv[i*nj+j] = T(100*i)     ; break ; 
                default:   vv[i*nj+j] = T(1000*i)    ; break ; 
            }   
        }   
    }   
    a->dump(); 
    return a ; 
}


template<typename T>
struct NP_MakeNarrow5D_test
{
    static const char* FOLD ; 

    NP* a ; 
    NP* b ; 
    std::vector<const NP*> vv ;

    NP* c ; 
    NP* fc ; 

    NP* d ; 
    NP* fd ; 

    NP* e ; 

    NP_MakeNarrow5D_test(int ni, int nj, int nk); 
    void save() const ; 
};

template<typename T>
const char* NP_MakeNarrow5D_test<T>::FOLD = U::GetEnv("FOLD", "/tmp") ; 

template<typename T>
NP_MakeNarrow5D_test<T>::NP_MakeNarrow5D_test(int ni, int nj, int nk )
    :
    a(MakeSrc<T>(10,2 )),
    b(MakeSrc<T>( 2,2 )),
    c(nullptr),
    fc(nullptr),
    d(nullptr),
    fd(nullptr),
    e(nullptr)
{
    for(int i=0 ; i < ni ; i++)
    for(int j=0 ; j < nj ; j++)
    for(int k=0 ; k < nk ; k++)
    {
        int ik = k % 2 ; 
        vv.push_back( ik == 0 ? a : b ); 
    }
  

    c = NP::Combine(vv) ; 

    const std::vector<int>& shape = c->shape ; 
    assert( shape.size() == 3 );  
    int c_ni = c->num_items() ; 
    assert( c_ni == shape[0] ); 
    assert( c_ni == ni*nj*nk ); 
    int nl = shape[1] ;
    int nm = shape[2] ;  
    
    c->change_shape( ni, nj, nk, nl, nm ); 

    std::cout << " c.sstr " << c->sstr() << std::endl ;  
    c->dump(); 
 
    fc = NP::MakeWithType<float>(c) ; 
    std::cout << " fc.sstr " << fc->sstr() << std::endl ;  


    // changing the type while still 3D 
    // enables the last column integer annotation to be preserved

    d = NP::Combine(vv) ; 
    fd = NP::MakeWithType<float>(d) ; 
    
    d->change_shape( ni, nj, nk, nl, nm ); 
    fd->change_shape( ni, nj, nk, nl, nm ); 

    e = c->copy() ; 
    e->change_shape_to_3D() ; 
}
 
template<typename T>
void NP_MakeNarrow5D_test<T>::save() const 
{
    a->save(FOLD, "a.npy");  
    b->save(FOLD, "b.npy");  
    c->save(FOLD, "c.npy");  
    fc->save(FOLD, "fc.npy");  
    d->save(FOLD, "d.npy");  
    fd->save(FOLD, "fd.npy");  
    e->save(FOLD, "e.npy");  
}

int main(int argc, char** argv)
{
    NP_MakeNarrow5D_test<double> t(3,4,2) ; 
    t.save();  
    return 0 ; 
}

