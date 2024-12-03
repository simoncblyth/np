// ./NP_ReadKV_test.sh

#include "NP.hh"

void test_ReadKV()
{
    std::vector<std::string> keys ; 
    std::vector<double> vals ; 
    std::vector<std::string> extras ; 

    NP::ReadKV<double>("/tmp", "THICKNESS", keys, vals, &extras ); 
    std::cout << NP::DescKV<double>(keys, vals, &extras ); 
}


const char* THICKNESS_SPECS = R"(
PMTProperty.R12860.THICKNESS
PMTProperty.NNVTMCP.THICKNESS
PMTProperty.NNVTMCP_HiQE.THICKNESS
)" ; 


void test_ReadKV_Value()
{
    std::vector<std::string> keys = {"ARC_THICKNESS", "PHC_THICKNESS" }; 
    std::cout << "[ test_ReadKV_Value keys.size " << keys.size() << std::endl ; 

    std::stringstream ss(THICKNESS_SPECS) ;
    std::string spec ;
    while (std::getline(ss, spec))
    {
        if(spec.empty()) continue ;
        const char* s = spec.c_str();  

        for(unsigned i=0 ; i < keys.size() ; i++)
        { 
            const char* key = keys[i].c_str(); 
            double val = NP::ReadKV_Value<double>(s, key) ;  

            std::cout 
                << "NP::ReadKV_Value "
                << " s " << std::setw(40) << s 
                << " key " << std::setw(20) << key 
                << " : " 
                << std::scientific << std::setw(20) << std::setprecision(10) << val 
                << std::endl
                ;
        } 
    }
    std::cout << "] test_ReadKV_Value keys.size " << keys.size() << std::endl ; 
}


// added leading and trailing whitespace to check it gets ignored 
const char* SPECS = R"(
   PMTProperty.R12860.ARC_RINDEX
PMTProperty.R12860.ARC_KINDEX
PMTProperty.R12860.PHC_RINDEX
   PMTProperty.R12860.PHC_KINDEX
PMTProperty.R12860.CE    
PMTProperty.R12860.QE_shape         

    PMTProperty.NNVTMCP.ARC_RINDEX    
PMTProperty.NNVTMCP.ARC_KINDEX
PMTProperty.NNVTMCP.PHC_RINDEX
PMTProperty.NNVTMCP.PHC_KINDEX
PMTProperty.NNVTMCP.CE
PMTProperty.NNVTMCP.QE_shape 

PMTProperty.NNVTMCP_HiQE.ARC_RINDEX
PMTProperty.NNVTMCP_HiQE.ARC_KINDEX
PMTProperty.NNVTMCP_HiQE.PHC_RINDEX
PMTProperty.NNVTMCP_HiQE.PHC_KINDEX
PMTProperty.NNVTMCP_HiQE.CE
PMTProperty.NNVTMCP_HiQE.QE_shape 

)" ; 

void test_Resolve()
{
    std::stringstream ss(SPECS) ;
    std::string spec ;
    while (std::getline(ss, spec))
    {
        if(spec.empty()) continue ;
        const char* s = spec.c_str();  
        const char* path = NP::Resolve(s) ; 
        std::cout 
             << " spec " << std::setw(50) << ( s ? s : "-" ) 
             << " path " << std::setw(50) << ( path ? path : "-" ) 
             << std::endl
             ; 
    }
}

void test_LoadFromTxtFile_Prop()
{
    std::stringstream ss(SPECS) ;
    std::string spec ;
    while (std::getline(ss, spec))
    {
        if(spec.empty()) continue ;
        const char* s = spec.c_str();  
        NP* prop = NP::LoadFromTxtFile<double>(s); 
        const char* p = NP::Resolve(s) ; 
        std::cout 
             << " prop " <<  std::setw(15) << ( prop ? prop->sstr() : "-" )
             << " spec " << std::setw(50) << ( s ? s : "-" ) 
             << " p " << std::setw(50) << ( p ? p : "-" ) 
             << std::endl
             ; 

        std::string out = p ; 
        out += ".npy" ; 
        //std::cout << " save to " << out << std::endl ; 
        prop->save(out.c_str()); 
    }
}

void test_LoadFromTxtFile()
{
    const char* path = "/tmp/PHC_RINDEX" ; 

    NP* a = NP::LoadFromTxtFile<double>(path) ;   
    std::cout << " a.sstr " << ( a ? a->sstr() : "-" ) << std::endl ; 
    std::string out = path ; 
    out += ".npy" ; 
    std::cout << " save to " << out << std::endl ; 
    a->save(out.c_str()); 
}

void test_Accessors()
{
    {
        const char* s = "PMTProperty.R12860.PHC_KINDEX" ; 
        NP* a = NP::LoadFromTxtFile<double>(s) ; 
        std::cout << " a " << ( a ? a->sstr() : "-" ) << " " << s << std::endl ; 
    }

    {
        const char* s = "PMTProperty.R12860.THICKNESS" ; 
        const char* k = "PHC_THICKNESS" ; 
        double v = NP::ReadKV_Value<double>(s, k) ;  

        std::cout 
            << " s " << s 
            << " k " << k  
            << " v " << std::scientific << std::setw(10) << std::setprecision(5) << v 
            << std::endl 
            ; 
    }

    {
        const char* s = "PMTProperty.R12860.THICKNESS" ; 
        const char* k = "ARC_THICKNESS" ; 
        double v = NP::ReadKV_Value<double>(s, k) ;  

        std::cout 
            << " s " << s 
            << " k " << k  
            << " v " << std::scientific << std::setw(10) << std::setprecision(5) << v 
            << std::endl 
            ; 
    }

}


void test_ConvertsTo()
{
    std::vector<std::string> strs = 
        {{ 
           "hello", "world", "1", "1.1" , "10" , "1e6", "1e-6", 
           "2.69531", "*eV", "2.7101", 
           "   2.69531  ", "  *eV  ", "  2.7101  " 
        }} ;  


    for(unsigned idx=0 ; idx < strs.size() ; idx++)
    {
        const char* str = strs[idx].c_str(); 
        bool f = U::ConvertsTo<float>(str); 
        bool d = U::ConvertsTo<double>(str); 
        bool i = U::ConvertsTo<int>(str); 
        bool u = U::ConvertsTo<unsigned>(str); 
        bool s = U::ConvertsTo<std::string>(str); 

        float    fv = f ? U::To<float>(str)  : 0.f ;  
        double   dv = d ? U::To<double>(str) : 0. ;  
        int      iv = i ? U::To<int>(str) : 0 ;  
        unsigned uv = u ? U::To<unsigned>(str) : 0u ;  
        std::string sv = s ? U::To<std::string>(str) : "-" ;  
        

        std::cout 
            << std::setw(10) << str 
            << " f " << f
            << " d " << d
            << " i " << i
            << " u " << u
            << " s " << s
            << " fv " << fv
            << " dv " << dv
            << " iv " << iv
            << " uv " << uv
            << " sv " << sv
            << std::endl 
            ;
    }
}

const char* STR_0 = R"(1.55     *eV    2.72832
    2.69531  *eV    2.7101
    2.7552   *eV    2.5918
    3.17908  *eV    1.9797
    15.5     *eV    1.9797)" ; 


const char* STR_1 = R"(
    1.55     *eV    2.72832
    2.69531  *eV    2.7101
    2.7552   *eV    2.5918
    3.17908  *eV    1.9797
    15.5     *eV    1.9797
)" ; 



void test_LoadFromString()
{
    NP* a0 = NP::LoadFromString<double>(STR_0) ; 
    std::cout 
        << " test_LoadFromString a0.sstr " 
        << ( a0 ? a0->sstr() : "-" ) 
        << std::endl
        ;

    NP* a1 = NP::LoadFromString<double>(STR_1) ; 
    std::cout 
        << " test_LoadFromString a1.sstr " 
        << ( a1 ? a1->sstr() : "-" ) 
        << std::endl
        ;

    NP* a2 = NP::LoadFromString<double>(R"(
    1.55     *eV    2.72832
    2.69531  *eV    2.7101
    2.7552   *eV    2.5918
    3.17908  *eV    1.9797
    15.5     *eV    1.9797
)") ; 

    std::cout 
        << " test_LoadFromString a2.sstr " 
        << ( a2 ? a2->sstr() : "-" ) 
        << std::endl
        ;
}

void test_LoadFromString_meta()
{
    const char* STR = R"(
ARC_THICKNESS   36.49e-9*m
PHC_THICKNESS   21.13e-9*m
)" ; 

    std::cout << STR << std::endl ; 

    NP* a = NP::LoadFromString<double>(STR) ; 

    std::cout 
        << " test_LoadFromString_meta a.sstr " 
        << ( a ? a->sstr() : "-" ) 
        << " a->names.size " << a->names.size() 
        << std::endl
        ;

    for(unsigned i=0 ; i < a->names.size() ; i++) std::cout
        << " a->names[" << i << "] [" << a->names[i] << "]"
        << std::endl
        ;

    std::vector<std::string> nn = { "ARC_THICKNESS", "PHC_THICKNESS" } ; 

    const double* vv = a->cvalues<double>() ; 

    std::string units = a->get_meta<std::string>("units", "") ; 

  
    for(unsigned i=0 ; i < nn.size() ; i++)
    {
        const char* n = nn[i].c_str(); 
        unsigned count(0); 
        int idx = a->get_name_index(n, count ); 

        double nv = a->get_named_value<double>( n, -1. );  

        std::cout 
            << " i " << i 
            << " n " << n 
            << " idx " << idx 
            << " count " << count 
            << " vv[idx] " << vv[idx]
            << " nv " << nv 
            << " units [" << units << "]" 
            << std::endl 
            ;  
    }


}    

void test_LoadFromString_get_named_value()
{
    const char* STR = R"(
ARC_THICKNESS   36.49e-9*m
PHC_THICKNESS   21.13e-9*m
)" ; 

    std::cout << STR << std::endl ; 

    NP* a = NP::LoadFromString<double>(STR) ; 

    double d0 = a->get_named_value<double>("ARC_THICKNESS", -1.);  
    double d1 = a->get_named_value<double>("PHC_THICKNESS", -1.);  
    assert( d0 == 3.649e-8 ); 
    assert( d1 == 2.113e-8 ); 

}


void test_LoadFromString_ConstantProperty()
{
    const char* STR = R"(
#some constant property of LS

#SCINTILLATIONYIELD
ScintillationYield   9846/MeV
ResolutionScale      1.0

#birks law
BirksConstant1  12.05e-3*g/cm2/MeV
BirksConstant2  0


)" ; 

    std::cout << STR << std::endl ; 

    NP* a = NP::LoadFromString<double>(STR) ; 

    std::cout << " a.sstr " << ( a ? a->sstr() : "-" ) << std::endl;  

    double ScintillationYield = a->get_named_value<double>("ScintillationYield", -1.);  
    double ResolutionScale = a->get_named_value<double>("ResolutionScale", -1.);  
    double BirksConstant1 = a->get_named_value<double>("BirksConstant1", -1.);  
    double BirksConstant2 = a->get_named_value<double>("BirksConstant2", -1.);  

    std::cout << "ScintillationYield " << ScintillationYield << std::endl ; 
    std::cout << "ResolutionScale    " << ResolutionScale << std::endl ; 
    std::cout << "BirksConstant1     " << BirksConstant1 << std::endl ; 
    std::cout << "BirksConstant2     " << BirksConstant2 << std::endl ; 


}

void test_ZEROProp()
{
    NP* a = NP::ZEROProp<double>() ; 
    std::cout << " a.sstr " << ( a ? a->sstr() : "-" ) << std::endl;  
    a->dump(); 
}



int main()
{
    /*
    test_ReadKV(); 
    test_ReadKV_Value(); 
    test_Accessors(); 
    test_Resolve();  
    test_LoadFromTxtFile_Prop(); 
    test_LoadFromTxtFile(); 
    test_ConvertsTo();    
    test_Accessors(); 
    test_LoadFromString(); 
    test_LoadFromString_meta(); 
    test_LoadFromString_get_named_value(); 
    test_LoadFromString_ConstantProperty(); 
    */
    test_ZEROProp(); 
 

    return 0 ; 
}
