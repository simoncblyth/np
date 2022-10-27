// name=NP_ReadKV_test ; gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o /tmp/$name && lldb__ /tmp/$name

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

void test_ArrayFromTxt_Prop()
{
    std::stringstream ss(SPECS) ;
    std::string spec ;
    while (std::getline(ss, spec))
    {
        if(spec.empty()) continue ;
        const char* s = spec.c_str();  
        NP* prop = NP::ArrayFromTxt<double>(s); 
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

void test_ArrayFromTxt()
{
    const char* path = "/tmp/PHC_RINDEX" ; 

    NP* a = NP::ArrayFromTxt<double>(path) ;   
    std::cout << " a.sstr " << ( a ? a->sstr() : "-" ) << std::endl ; 
    std::string out = path ; 
    out += ".npy" ; 
    std::cout << " save to " << out << std::endl ; 
    a->save(out.c_str()); 
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
        bool f = NP::ConvertsTo<float>(str); 
        bool d = NP::ConvertsTo<double>(str); 
        bool i = NP::ConvertsTo<int>(str); 
        bool u = NP::ConvertsTo<unsigned>(str); 
        bool s = NP::ConvertsTo<std::string>(str); 

        float    fv = f ? NP::To<float>(str)  : 0.f ;  
        double   dv = d ? NP::To<double>(str) : 0. ;  
        int      iv = i ? NP::To<int>(str) : 0 ;  
        unsigned uv = u ? NP::To<unsigned>(str) : 0u ;  
        std::string sv = s ? NP::To<std::string>(str) : "-" ;  
        

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



int main()
{
    /*
    test_ReadKV(); 
    test_ReadKV_Value(); 
    test_Resolve();  
    test_ArrayFromTxt_Prop(); 
    test_ArrayFromTxt(); 
    test_ConvertsTo();    
    */

    test_ReadKV_Value(); 
 

    return 0 ; 
}
