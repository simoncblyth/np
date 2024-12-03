// ~/np/tests/NPMakeICDFTest.sh
#include "NP.hh"

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
    dist0->save("$FOLD/dist0.npy"); 
    NP* dist = mul > 1 ? NP::MakeDiv<double>(dist0, mul ) : dist0 ; 
    dist->save("$FOLD/dist.npy"); 
    return dist ; 
}

int main(int argc, char** argv)
{
    unsigned mul = 10 ; 
    NP* dist = make_dist(mul) ; 
    std::cout << " dist " << dist->sstr() << std::endl ; 

    NP* cdf =  NP::MakeCDF<double>( dist ); 
    cdf->save("$FOLD/cdf.npy"); 
    std::cout << " cdf " << cdf->sstr() << std::endl ; 

    unsigned nu = 91 ; 
    unsigned hd_factor = 10 ; 
    // TODO: get hd_factor creation and lookups operational 
    bool dump = true ;

    NP* icdf = NP::MakeICDF<double>( cdf, nu , hd_factor, dump ); 
    std::cout << " icdf " << icdf->sstr() << std::endl ; 
    icdf->change_shape(-1, hd_factor > 0 ? 4  : -1 ); 
    std::cout << " icdf after change_shape " << icdf->sstr() << " hd_factor " << hd_factor << std::endl ; 
    icdf->dump(); 
    icdf->save("$FOLD/icdf.npy"); 


    NP* icdf_prop = NP::MakeProperty<double>( icdf, hd_factor ) ; 
    icdf_prop->save("$FOLD/icdf_prop.npy" );  
    std::cout << " icdf_prop " << icdf_prop->sstr() << " hd_factor " << hd_factor << std::endl ; 


    unsigned seed = 0u ; 
    NP* sample = NP::MakeLookupSample<double>( icdf_prop, 1000000, seed, hd_factor );  
    sample->save("$FOLD/lookup_sample.npy"); 

    return 0 ; 
}

