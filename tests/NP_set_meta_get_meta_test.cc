// ~/np/tests/NP_set_meta_get_meta_test.sh

const char* APATH = "$FOLD/a.npy" ;

#include "NP.hh"

struct NP_set_meta_get_meta_test
{
    static int uint64();

    static int string();
    static int string2();
    static int string3();
    static int string4();

    static int main();
};

inline int NP_set_meta_get_meta_test::main()
{
    const char* TEST = U::GetEnv("TEST","string4");
    bool ALL = strcmp(TEST,"ALL") == 0 ;

    int rc = 0 ;
    if(ALL||0==strcmp(TEST,"uint64")) rc += uint64();
    if(ALL||0==strcmp(TEST,"string")) rc += string();
    if(ALL||0==strcmp(TEST,"string2")) rc += string2();
    if(ALL||0==strcmp(TEST,"string3")) rc += string3();
    if(ALL||0==strcmp(TEST,"string4")) rc += string4();

    return rc ;
}


inline int NP_set_meta_get_meta_test::uint64()
{
    NP* a = NP::Make<float>(1,4,4);
    uint64_t u0 = std::numeric_limits<uint64_t>::max() ;
    a->set_meta<uint64_t>("u", u0 );
    a->save(APATH);
    NP* b = NP::Load(APATH);

    uint64_t u1 = b->get_meta<uint64_t>("u", 0) ;

    std::cout << " u0 " << u0 << std::endl ;
    std::cout << " u1 " << u1 << std::endl ;
    return 0 ;
}



inline int NP_set_meta_get_meta_test::string()
{
    const char* o_msg = "metadata_string with some blank spaces on the line" ;

    NP* a = NP::Make<float>(1,4,4);
    a->set_meta<std::string>("msg", o_msg) ;

    std::string a_msg = a->get_meta<std::string>("msg", "" );

    a->save(APATH);
    NP* b = NP::Load(APATH);

    std::string b_msg = b->get_meta<std::string>("msg", "" );

    std::cout << "o_msg:[" << o_msg << "]" << std::endl ;
    std::cout << "a_msg:[" << a_msg << "]" << std::endl ;
    std::cout << "b_msg:[" << b_msg << "]" << std::endl ;

    /**
    epsilon:tests blyth$ cat /tmp/NP_set_meta_get_meta_test/a_meta.txt
    msg:metadata_string with some blank spaces on the line
    **/

    return 0 ;
}

inline int NP_set_meta_get_meta_test::string2()
{
    NP* a = NP::Make<float>(1,4,4);
    a->set_meta<std::string>("red", "cyan") ;
    a->set_meta<std::string>("green", "magenta") ;
    a->set_meta<std::string>("blue", "yellow") ;

    std::string s0 = a->get_meta<std::string>("red", "" );
    std::string s1 = a->get_meta<std::string>("green", "" );
    std::string s2 = a->get_meta<std::string>("blue", "" );
    std::string s3 = a->get_meta<std::string>("missing", "" );

    std::cout << " s0 [" << s0  << "]\n" ;
    std::cout << " s1 [" << s1  << "]\n" ;
    std::cout << " s2 [" << s2  << "]\n" ;
    std::cout << " s3 [" << s3  << "]\n" ;

    return 0 ;
}

inline int NP_set_meta_get_meta_test::string3()
{
    NP* a = NP::Make<float>(1,4,4);
    a->meta = "QSim__simulate_tot_dt:0.0376182\nSettings:HitCompOneName:hit,PhotonCompOneName:photon\n" ;

    std::string s0  = a->get_meta<std::string>("QSim__simulate_tot_dt", "" );
    double d0       = a->get_meta<double>("QSim__simulate_tot_dt", 0.1 );

    std::cout << " s0 [" << s0  << "]\n" ;
    std::cout << " d0 [" << d0  << "]\n" ;
    return 0 ;
}

inline int NP_set_meta_get_meta_test::string4()
{
    NP* a = NP::Make<float>(1,4,4);
    a->meta = "QSim__simulate_tot_dt:0.0376182\nSettings:HitCompOneName:hit,PhotonCompOneName:photon\n" ;

    std::string s0  = a->get_meta<std::string>("QSim__simulate_tot_dt", "" );
    double d0       = a->get_meta<double>("QSim__simulate_tot_dt", 0.1 );

    std::cout << " s0 [" << s0  << "]\n" ;
    std::cout << " d0 [" << d0  << "]\n" ;


    std::string s1  = a->get_meta<std::string>("Settings", "" );
    std::cout << " s1 [" << s1  << "]\n" ;

    std::string s2  = a->get_meta<std::string>("Settings");
    std::cout << " s2 [" << s2  << "]\n" ;


    return 0 ;
}




int main()
{
    return NP_set_meta_get_meta_test::main();
}
