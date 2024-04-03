//  ~/np/tests/np_test.sh 

#include <cstdlib>
#include "np.h"

int main()
{
    std::vector<int> shape = {100,10,4,4} ; 
    double* pp = new double[100*10*4*4] ; 

    int ni = shape[0] ; 
    int nj = shape[1] ; 
    int nk = shape[2] ; 
    int nl = shape[3] ; 

    for(int i=0 ; i < ni ; i++ ) 
    for(int j=0 ; j < nj ; j++ ) 
    for(int k=0 ; k < nk ; k++ ) 
    for(int l=0 ; l < nl ; l++ ) 
    {
        int idx = i*nj*nk*nl + j*nk*nl + k*nl + l ; 
        double val = i*100000 + j*1000 + k*100 + l ; 
        pp[idx] = val ; 
    }

    np::Write(getenv("NPY"), shape, pp, "<f8") ;   

    return 0 ; 
} 
