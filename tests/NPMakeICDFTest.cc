// ./NPMakeICDFTest.sh
#include "NP.hh"

const char* FOLD = "/tmp/NPMakeICDFTest" ; 

NP* make_dist(unsigned mul)
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

    NP* dist0 = NP::Make<double>( src.size()/2 , 2 ) ; 
    dist0->read(src.data()); 
    dist0->save(FOLD, "dist0.npy"); 
    NP* dist = mul > 1 ? NP::MakeDiv<double>(dist0, mul ) : dist0 ; 
    dist->save(FOLD, "dist.npy"); 
    return dist ; 
}



int main(int argc, char** argv)
{
    unsigned mul = 10 ; 
    NP* dist = make_dist(mul) ; 

    NP* cdf =  NP::MakeCDF<double>( dist ); 
    cdf->save(FOLD, "cdf.npy"); 

    unsigned nu = 91 ; 
    unsigned hd_factor = 0 ;  // TODO: get hd_factor creation and lookups operational 
    NP* icdf = NP::MakeICDF<double>( cdf, nu , hd_factor ); 
    icdf->dump(); 
    icdf->change_shape(-1); 
    icdf->save(FOLD, "icdf.npy"); 
    std::cout << " icdf " << icdf->sstr() << std::endl ; 

    NP* icdf_prop = NP::MakeProperty<double>( icdf ) ; 
    icdf_prop->save(FOLD, "icdf_prop.npy" );  

    std::cout << " icdf_prop " << icdf_prop->sstr() << std::endl ; 
    


    NP* sample = NP::MakeSample<double>( icdf_prop, 1000000 );  
    sample->save(FOLD, "sample.npy"); 

    return 0 ; 
}

