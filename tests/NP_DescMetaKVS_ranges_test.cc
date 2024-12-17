// ~/np/tests/NP_DescMetaKVS_ranges_test.sh

#include "NP.hh"

struct NP_DescMetaKVS_ranges_test
{
    static int ranges(); 
    static int ranges2(); 
    static int Main(); 
}; 


int NP_DescMetaKVS_ranges_test::ranges()
{
    std::cout << "[NP_DescMetaKVS_ranges_test::ranges\n" ; 
    std::vector<std::tuple<std::string,int64_t>> kt = {
       {  "SEvt__Init_RUN_META", 1  },
       {  "CSGFoundry__Load_HEAD", 2 },
       {  "CSGFoundry__Load_TAIL", 3 },
       {  "CSGOptiX__Create_HEAD", 4 },
       {  "CSGOptiX__Create_TAIL", 5 }, 
       {  "A000_QSim__simulate_HEAD", 101 },
       {  "A000_QSim__simulate_PREL", 102 },
       {  "A000_QSim__simulate_POST", 103 },
       {  "A000_QSim__simulate_TAIL", 104 },
       {  "A001_QSim__simulate_HEAD", 201 },
       {  "A001_QSim__simulate_PREL", 202 },
       {  "A001_QSim__simulate_POST", 203 },
       {  "A001_QSim__simulate_TAIL", 204 },  
       {  "A002_QSim__simulate_HEAD", 301 },
       {  "A002_QSim__simulate_PREL", 302 },
       {  "A002_QSim__simulate_POST", 303 },
       {  "A002_QSim__simulate_TAIL", 304 },
       {  "CSGOptiX__SimulateMain_TAIL", 400 }
        } ; 
 
    std::vector<std::string> keys ; 
    std::vector<int64_t> tt ; 
    U::SplitTuple( keys, tt, kt ); 
    assert( keys.size() == tt.size() ) ; 

    static constexpr const char* RANGES = R"( 
        SEvt__Init_RUN_META:CSGFoundry__Load_HEAD       
        CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL     ## load geom 
        CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL     ## upload geom
        A%0.3d_QSim__simulate_HEAD:A%0.3d_QSim__simulate_PREL         ## upload genstep
        A%0.3d_QSim__simulate_PREL:A%0.3d_QSim__simulate_POST         ## simulate kernel
        A%0.3d_QSim__simulate_POST:A%0.3d_QSim__simulate_TAIL         ## download 
        A%0.3d_QSim__simulate_TAIL:CSGOptiX__SimulateMain_TAIL
       )" ; 



    std::cout << NP::DescMetaKVS_ranges(keys, tt, RANGES ) << std::endl ;

    NP* rr = NP::MakeMetaKVS_ranges(keys, tt, RANGES ) ; 
    std::cout << "rr\n" << rr->descTable<int64_t>(20) ; 

    std::cout << "]NP_DescMetaKVS_ranges_test::ranges\n" ; 
    return 0 ; 
}


int NP_DescMetaKVS_ranges_test::ranges2()
{
    std::cout << "[NP_DescMetaKVS_ranges_test::ranges2\n" ; 

    std::vector<std::tuple<std::string,int64_t>> kt = {
       {  "SEvt__Init_RUN_META", 10  },
       {  "CSGFoundry__Load_HEAD", 20 },
       {  "CSGFoundry__Load_TAIL", 30 },
       {  "CSGOptiX__Create_HEAD", 40 },
       {  "CSGOptiX__Create_TAIL", 50 }, 
       {  "A000_QSim__simulate_HEAD", 1010 },
       {  "A000_QSim__simulate_PREL", 1020 },
       {  "A000_QSim__simulate_POST", 1030 },
       {  "A000_QSim__simulate_PREL", 1031 },
       {  "A000_QSim__simulate_POST", 1038 },
       {  "A000_QSim__simulate_TAIL", 1040 },
       {  "A001_QSim__simulate_HEAD", 2010 },
       {  "A001_QSim__simulate_PREL", 2020 },
       {  "A001_QSim__simulate_POST", 2030 },
       {  "A001_QSim__simulate_TAIL", 2040 },  
       {  "A002_QSim__simulate_HEAD", 3010 },
       {  "A002_QSim__simulate_PREL", 3020 },
       {  "A002_QSim__simulate_POST", 3030 },
       {  "A002_QSim__simulate_TAIL", 3040 },
       {  "CSGOptiX__SimulateMain_TAIL", 4000 }
        } ; 
 
    std::vector<std::string> keys ; 
    std::vector<int64_t> tt ; 
    U::SplitTuple( keys, tt, kt ); 
    assert( keys.size() == tt.size() ) ; 

    static constexpr const char* RANGES = R"( 
        SEvt__Init_RUN_META:CSGFoundry__Load_HEAD       
        CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL     ## load geom 
        CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL     ## upload geom
        A%0.3d_QSim__simulate_HEAD:A%0.3d_QSim__simulate_PREL         ## upload genstep
        A%0.3d_QSim__simulate_PREL:A%0.3d_QSim__simulate_POST         ## simulate kernel
        A%0.3d_QSim__simulate_POST:A%0.3d_QSim__simulate_TAIL         ## download 
        A%0.3d_QSim__simulate_TAIL:CSGOptiX__SimulateMain_TAIL
       )" ; 


    std::cout << NP::DescMetaKVS_ranges2(keys, tt, RANGES ) << std::endl ;

    NP* rr = NP::MakeMetaKVS_ranges2(keys, tt, RANGES ) ; 
    std::cout << "rr\n" << rr->descTable<int64_t>(20) ; 

    std::cout << "]NP_DescMetaKVS_ranges_test::ranges2\n" ; 
    return 0 ; 
}

int NP_DescMetaKVS_ranges_test::Main()
{
    const char* TEST = U::GetEnv( "TEST", "ranges2" ); 
    bool ALL = strcmp(TEST, "ALL") == 0 ; 
    int rc = 0 ;
    if(ALL||0==strcmp(TEST,"ranges"))  rc += ranges(); 
    if(ALL||0==strcmp(TEST,"ranges2")) rc += ranges2(); 
    return rc ; 
}

int main(int argc, char** argv){ return NP_DescMetaKVS_ranges_test::Main() ; }

// ~/np/tests/NP_DescMetaKVS_ranges_test.sh


