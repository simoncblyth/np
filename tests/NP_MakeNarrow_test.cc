// ./NP_MakeNarrow_test.sh 

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
struct NP_MakeNarrow_test
{
    static const char* FOLD ; 

    NP* a ; 
    NP* b ; 
    NP* c ; 
    NP* abc ; 
    NP* fabc ; 

    NP_MakeNarrow_test(); 
    void save() const ; 
};

template<typename T>
const char* NP_MakeNarrow_test<T>::FOLD = U::GetEnv("FOLD", "/tmp") ; 

template<typename T>
NP_MakeNarrow_test<T>::NP_MakeNarrow_test()
    :
    a(MakeSrc<T>(10,2 )),
    b(MakeSrc<T>( 2,2 )),
    c(MakeSrc<T>( 5,2 )),
    abc(NP::Combine_(a,b,c)),
    fabc(NP::MakeWithType<float>(abc))
{
    std::cout << " abc.sstr " << abc->sstr() << std::endl ;  
    abc->dump(); 
}
 
template<typename T>
void NP_MakeNarrow_test<T>::save() const 
{
    a->save(FOLD, "a.npy");  
    b->save(FOLD, "b.npy");  
    c->save(FOLD, "c.npy");  
    abc->save(FOLD, "abc.npy");  
    fabc->save(FOLD, "fabc.npy");  
}

int main(int argc, char** argv)
{
    NP_MakeNarrow_test<double> t ; 
    t.save();  
    return 0 ; 
}

/**
Issue : Last column integer annotation gets scrubbed by narrowing (or widening presumably)::

    In [2]: t.abc[...,-1,-1].view(np.int64)
    Out[2]: array([10,  2,  5])

    In [3]: t.fabc[...,-1,-1].view(np.int32)
    Out[3]: array([0, 0, 0], dtype=int32)

After fix the annotation survives being narrowed::

    In [1]: t.fabc[...,-1,-1].view(np.int32)
    Out[1]: array([10,  2,  5], dtype=int32)


This works for simple 3D case but with higher dimensions
only the final of each cat gets preserved::

    In [3]: t.src_rindex.view(np.int64)[...,-1,-1]
    Out[3]: 
    array([[[10,  2],
            [14,  2],
            [14, 14],
            [ 4,  2]],

           [[10,  2],
            [14,  2],
            [14, 14],
            [ 4,  2]],

           [[10,  2],
            [14,  2],
            [14, 14],
            [ 4,  2]]])


    In [4]: t.rindex.view(np.int32)[...,-1,-1]
    Out[4]: 
    array([[[0, 0],
            [0, 0],
            [0, 0],
            [0, 2]],

           [[0, 0],
            [0, 0],
            [0, 0],
            [0, 2]],

           [[0, 0],
            [0, 0],
            [0, 0],
            [0, 2]]], dtype=int32)




**/

