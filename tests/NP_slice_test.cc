// name=NP_slice_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

void test_index(const NP* bnd)
{
    int boundary = 4 ; 
    int species = 0 ; 
    int group = 1 ; 
    int wavelength = 0 ; 
    int prop = 0 ; 

    unsigned i0 = bnd->index( boundary, species, group, wavelength, prop ); 
    unsigned i1 = bnd->index0(boundary, species, group, wavelength, prop ); 
    unsigned i2 = bnd->index_(boundary, species, group, wavelength, prop ); 
    std::cout << " i0 " << i0 << " i1 " << i1 << " i2 " << i2 << std::endl ;

    assert( i0 == i1 ); 
    assert( i0 == i2 ); 
}

void test_slice(const NP* bnd)
{
    // <f8(44, 4, 2, 761, 4, )
    int species = 0 ; 
    int group = 1 ; 
    int wavelength = -1 ; 
    int prop = 0 ; 

    for(int boundary=0 ; boundary < bnd->shape[0] ; boundary++)
    {
        std::vector<double> out ; 
        bnd->slice(out, boundary, species, group, wavelength, prop );  
        std::cout 
            << bnd->names[boundary] << std::endl 
            << NP::DescSlice(out, 5 ) 
            ; 
    }
}

int main(int argc, char** argv)
{
    const char* defpath = "/Users/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/41c046fe05b28cb70b1fc65d0e6b7749/1/CSG_GGeo/CSGFoundry/SSim/bnd.npy" ; 
    const char* path = argc > 1 ? argv[1] : defpath ; 
    NP* bnd = NP::Load(path); 
    if(bnd == nullptr) return 1 ; 

    std::cout << bnd->brief() << std::endl ; 

    /*
    test_index(bnd); 
    */
    test_slice(bnd); 

    return 0 ; 
}
