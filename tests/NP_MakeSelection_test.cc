// ./NP_MakeSelection_test.sh 

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


int main(int argc, char** argv)
{
    const char* FOLD = getenv("FOLD"); 
    NP* src = MakeSrc<double>(10,4) ; 

    std::vector<int64_t> vv = {0,2,4,6,8} ;
    NP* sel = NP::MakeFromValues<int64_t>( vv.data(), vv.size() ); 

    std::cout << " src " << src->desc() << std::endl ; 
    std::cout << " sel " << sel->desc() << std::endl ; 
    src->save(FOLD, "src.npy"); 
    sel->save(FOLD, "sel.npy"); 

    NP* dst = NP::MakeSelection( src, sel ); 
    dst->save(FOLD, "dst.npy"); 
    std::cout << " dst " << dst->desc() << std::endl ; 

    return 0 ; 
}

