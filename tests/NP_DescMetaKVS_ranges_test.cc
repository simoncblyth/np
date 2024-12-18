// ~/np/tests/NP_DescMetaKVS_ranges_test.sh

#include "NP.hh"

struct NP_DescMetaKVS_ranges_test
{
    static int ranges(); 

    static void add_tuple( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, const char* tag, int64_t t ); 
    static void add_tuple( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, int64_t t0, const std::vector<std::string>& tags ); 
    static void add_QSim( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, int64_t t0  ); 
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


void NP_DescMetaKVS_ranges_test::add_tuple( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, const char* tag, int64_t t )
{
    std::stringstream ss ; 
    ss << prefix << tag ; 
    kt.push_back( {ss.str(), t} ); 
}

void NP_DescMetaKVS_ranges_test::add_tuple( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, int64_t t0, const std::vector<std::string>& tags )
{
    int64_t t = t0 ; 
    for(int i=0 ; i < int(tags.size()) ; i++)
    {
        add_tuple(kt, prefix, tags[i].c_str(), t ); 
        t += 10 ; 
    }
}

void NP_DescMetaKVS_ranges_test::add_QSim( std::vector<std::tuple<std::string,int64_t>>& kt, const char* prefix, int64_t t0  )
{
    add_tuple(kt, prefix, "HEAD", t0 ); 
    add_tuple(kt, prefix, "LBEG", t0+10 ); 

    std::vector<std::string> tags = {"PRUP", "PREL", "POST", "DOWN" } ; 
    add_tuple(kt, prefix, t0+100, tags ); 
    add_tuple(kt, prefix, t0+200, tags ); 
    add_tuple(kt, prefix, t0+300, tags ); 
    add_tuple(kt, prefix, t0+400, tags ); 

    add_tuple(kt, prefix, "LEND", t0+500); 
    add_tuple(kt, prefix, "PCAT", t0+600); 
    add_tuple(kt, prefix, "BRES", t0+700); 
    add_tuple(kt, prefix, "TAIL", t0+800); 
}



int NP_DescMetaKVS_ranges_test::ranges2()
{
    std::cout << "[NP_DescMetaKVS_ranges_test::ranges2\n" ; 

    std::vector<std::tuple<std::string,int64_t>> kt = {
       {  "SEvt__Init_RUN_META", 10  },
       {  "CSGFoundry__Load_HEAD", 20 },
       {  "CSGFoundry__Load_TAIL", 30 },
       {  "CSGOptiX__Create_HEAD", 40 },
       {  "CSGOptiX__Create_TAIL", 50 }
      }; 

    add_QSim( kt, "A000_QSim__simulate_",  1000 ); 
    add_QSim( kt, "A001_QSim__simulate_",  2000 ); 
    add_QSim( kt, "A002_QSim__simulate_",  3000 ); 
    add_QSim( kt, "A003_QSim__simulate_",  4000 ); 

    kt.push_back({"CSGOptiX__SimulateMain_TAIL", 5000 }); 


 
    std::vector<std::string> keys ; 
    std::vector<int64_t> tt ; 
    U::SplitTuple( keys, tt, kt ); 
    assert( keys.size() == tt.size() ) ; 

    static constexpr const char* RANGES = R"( 
        SEvt__Init_RUN_META:CSGFoundry__Load_HEAD                     ## init
        CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL                   ## load_geom
        CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL                   ## upload_geom
        A%0.3d_QSim__simulate_HEAD:A%0.3d_QSim__simulate_LBEG         ## slice_genstep
        A%0.3d_QSim__simulate_PRUP:A%0.3d_QSim__simulate_PREL         ## upload genstep slice
        A%0.3d_QSim__simulate_PREL:A%0.3d_QSim__simulate_POST         ## simulate slice
        A%0.3d_QSim__simulate_POST:A%0.3d_QSim__simulate_DOWN         ## download slice
        A%0.3d_QSim__simulate_LEND:A%0.3d_QSim__simulate_PCAT         ## concat slices
        A%0.3d_QSim__simulate_BRES:A%0.3d_QSim__simulate_TAIL         ## save arrays 
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


