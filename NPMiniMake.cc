// gcc NPMiniMake.cc -lstdc++ && ./a.out 5 2 4 && python -c "import numpy as np ; print(np.load('/tmp/a.npy'))"
#include "NP.hh"
int main(int argc, char** argv)
{
    int ni = argc > 1 ? atoi(argv[1]) : 10  ; 
    int nj = argc > 2 ? atoi(argv[2]) : 1   ; 
    int nk = argc > 3 ? atoi(argv[3]) : 4   ; 
    NP<float>* a = new NP<float>(ni,nj,nk) ; 
    for(int i=0 ; i < ni ; i++ ){
    for(int j=0 ; j < nj ; j++ ){
    for(int k=0 ; k < nk ; k++ ){

        int index = i*nj*nk + j*nk + k ; // 3d -> 1d
        a->data[index] = float(index) ;  // dummy value 
    }
    }
    }
    a->save("/tmp/a.npy") ; 
    return 0 ; 
}
