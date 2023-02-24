// name=NP_scan_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include <functional>
#include "NP.hh"


NP* scan( std::function<double(int, double)> fn, const std::vector<int>& ii, const std::vector<double>& jj )
{
    int ni = ii.size() ; 
    int nj = jj.size() ; 
    NP* a = NP::Make<double>( ni, nj );
    double* aa = a->values<double>() ;     
    for(int i=0 ; i < ni ; i++) for(int j=0 ; j < nj ; j++) aa[i*nj+j] = fn(ii[i], jj[j]) ;
    return a ; 
} 

struct IPMTSimParamSvc
{
    double get_pmtid_qe( int pmtid, double en ) const { return double( pmtid + en ) ; } ; 
}; 


int main(int argc, char** argv)
{
    IPMTSimParamSvc svc ; 

    std::function<double(int, double)> fn = std::bind( &IPMTSimParamSvc::get_pmtid_qe, &svc, std::placeholders::_1, std::placeholders::_2 ) ; 

    std::vector<int> ii = { 0,1,2,3} ;
    std::vector<double> jj = { 0.,1.,2.,3.} ;
 
    NP* a = scan( fn, ii, jj );
    std::cout << a->repr<double>() << std::endl ;  

    const char* path = "/tmp/scan.npy" ; 
    a->save(path); 
    std::cout << "save to " << path << std::endl ; 

    return 0 ; 
}

