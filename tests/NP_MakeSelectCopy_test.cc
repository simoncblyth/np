// ./NP_MakeSelectCopy_test.sh 

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
    std::cout << " src " << src->desc() << std::endl ; 
    src->save(FOLD, "src.npy"); 

    const int N = 4 ; 
    NP* dst[N] ; 

    dst[0] = NP::MakeSelectCopy( src, 0,5,9 ); 
    dst[1] = NP::MakeSelectCopy_( src, "0,5,9" ); 
    dst[2] = NP::MakeSelectCopyE_( src, "MASK", "1,2,9" ); 
    dst[3] = NP::MakeSelectCopyE_( src, "OTHER" ); 

    dst[0]->save(FOLD, "dst0.npy"); 
    dst[1]->save(FOLD, "dst1.npy"); 
    dst[2]->save(FOLD, "dst2.npy"); 
    dst[3]->save(FOLD, "dst3.npy"); 

    std::cout << " dst[0] " << dst[0]->desc() << std::endl ; 
    std::cout << " dst[1] " << dst[1]->desc() << std::endl ; 
    std::cout << " dst[2] " << dst[2]->desc() << std::endl ; 
    std::cout << " dst[3] " << dst[3]->desc() << std::endl ; 

    return 0 ; 
}

