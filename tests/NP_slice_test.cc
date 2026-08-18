// ~/np/tests/NP_slice_test.sh
#include "NP.hh"


struct NP_slice_test
{
    static int bnd_index(const NP* bnd);
    static int bnd_slice(const NP* bnd);
    static int bnd();

    static int slice();

    static int parse(const char* _sli);
    static int parse();

    static int main();
};

int NP_slice_test::main()
{
    int rc = 0 ;
    //rc += bnd();
    //rc += slice();
    rc += parse();
    return rc ;
}

int NP_slice_test::bnd_index(const NP* bnd)
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
    return 0;
}

int NP_slice_test::bnd_slice(const NP* bnd)
{
    // <f8(44, 4, 2, 761, 4, )
    int species = 0 ;
    int group = 0 ;
    int wavelength = -1 ;

    for(int boundary=0 ; boundary < bnd->shape[0] ; boundary++)
    {
        for(int prop=0 ; prop < 4 ; prop++)
        {
            std::vector<double> out ;
            bnd->slice(out, boundary, species, group, wavelength, prop );

            unsigned offset = bnd->offset_(boundary, species, group, wavelength, prop) ;

            std::cout
                << " prop " << std::setw(3) << prop
                << " offset " << std::setw(3) << offset
                << " NP::DescSliceBrief " << NP::DescSliceBrief(out)
                << " bnd.name  " << bnd->names[boundary]
                << std::endl
                ;
        }
        std::cout << std::endl ;
    }
    return 0;
}

int NP_slice_test::bnd()
{
    // TODO: use modern path resolution
    const char* path = "/Users/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/41c046fe05b28cb70b1fc65d0e6b7749/1/CSG_GGeo/CSGFoundry/SSim/bnd.npy" ;
    NP* bnd = NP::Load(path);
    if(bnd == nullptr) return 1 ;
    std::cout << bnd->brief() << std::endl ;

    int rc = 0 ;
    rc += bnd_index(bnd);
    rc += bnd_slice(bnd);
    return rc ;
}

int NP_slice_test::slice()
{
    const int NI = 10 ;
    const int NJ = 4 ;

    NP* states = NP::Make<unsigned long>(NI, NJ) ;
    states->fillIndexFlat();

    std::vector<unsigned long> state ;

    for(int i=0 ; i < NI ; i++)
    {
        states->slice(state, i, -1);
        for(int j=0 ; j < NJ ; j++) std::cout << std::setw(5) << state[j] << " " ;
        std::cout << std::endl ;

        std::cout << states->sliceArrayString<unsigned long>(i, -1 ) << std::endl ;
    }
   return 0;
}

int NP_slice_test::parse(const char* _sli)
{
   NP_slice<int64_t> sli = {};
   bool dump = false ;
   int rc = sli.parse(_sli, dump);
   std::cout << std::setw(10) <<  _sli << " : " << sli.desc() << " : " << rc << "\n" ;
   return rc ;
}

int NP_slice_test::parse()
{
   bool dump = true ;
   int rc = 0 ;
   rc += parse("[:100]");
   rc += parse("[1:10]");
   rc += parse("[0:10:2]");
   rc += parse("[::10]");
   return rc ;
}


int main()
{
    return NP_slice_test::main();
}


