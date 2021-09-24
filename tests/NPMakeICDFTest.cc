
#include "NP.hh"

const char* FOLD = "/tmp/NPMakeICDFTest" ; 

int main(int argc, char** argv)
{
    std::vector<double> src = {
       0.,   0.,
       1.,  10.,
       2.,  20.,
       3.,  30.,
       4.,  40.,
       5.,  50.,
       6.,  60.,
       7.,  70.,
       8.,  80.,
       9.,  90.
    }; 

    NP* dist = NP::Make<double>( src.size()/2 , 2 ) ; 
    dist->read(src.data()); 
    dist->save(FOLD, "dist.npy"); 

    NP* cdf =  NP::MakeCDF<double>( dist ); 
    cdf->save(FOLD, "cdf.npy"); 

    unsigned nu = 91 ; 
    unsigned hd_factor = 0 ; 

    NP* icdf = NP::MakeICDF<double>( cdf, nu , hd_factor ); 
    icdf->dump(); 
    icdf->save(FOLD, "icdf.npy"); 

    return 0 ; 
}

