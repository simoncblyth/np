// name=NP_DescMetaKVS_ranges_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main()
{
    std::vector<std::string> keys = { 
         "SEvt__Init_RUN_META", 
         "CSGFoundry__Load_HEAD",
         "CSGFoundry__Load_TAIL",
         "CSGOptiX__Create_HEAD",
         "CSGOptiX__Create_TAIL", 
         "A000_QSim__simulate_HEAD",
         "A000_QSim__simulate_PREL",
         "A000_QSim__simulate_POST",
         "A000_QSim__simulate_TAIL",
         "A001_QSim__simulate_HEAD",
         "A001_QSim__simulate_PREL",
         "A001_QSim__simulate_POST",
         "A001_QSim__simulate_TAIL",
         "A002_QSim__simulate_HEAD",
         "A002_QSim__simulate_PREL",
         "A002_QSim__simulate_POST",
         "A002_QSim__simulate_TAIL",
         "CSGOptiX__SimulateMain_TAIL"
      }; 

    std::vector<int64_t> tt = {
         1, 
         2,
         3,
         4,
         5,
         101,
         102,
         103,
         104,
         201,
         202,
         203,
         204,
         301,
         302,
         303,
         304,
         400
     };

    assert( keys.size() == tt.size() ) ; 
    int64_t t0 = 1 ; 

    static constexpr const char* RANGES = R"( 
        SEvt__Init_RUN_META:CSGFoundry__Load_HEAD       
        CSGFoundry__Load_HEAD:CSGFoundry__Load_TAIL     ## load geom 
        CSGOptiX__Create_HEAD:CSGOptiX__Create_TAIL     ## upload geom
        A%0.3d_QSim__simulate_HEAD:A%0.3d_QSim__simulate_PREL         ## upload genstep
        A%0.3d_QSim__simulate_PREL:A%0.3d_QSim__simulate_POST         ## simulate kernel
        A%0.3d_QSim__simulate_POST:A%0.3d_QSim__simulate_TAIL         ## download 
        A%0.3d_QSim__simulate_TAIL:CSGOptiX__SimulateMain_TAIL
       )" ; 


    std::cout << NP::DescMetaKVS_ranges(keys, tt, t0, RANGES ) << std::endl ;
    return 0 ; 
}
