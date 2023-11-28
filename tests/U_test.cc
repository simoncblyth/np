// name=U_test ; gcc $name.cc -std=c++11 -lstdc++ -g -I.. -o /tmp/$name && /tmp/$name
// name=U_test ; gcc $name.cc -std=c++11 -lstdc++ -g -I.. -o /tmp/$name && lldb__ /tmp/$name

#include <cassert>
#include "NPU.hh"

void test_FormSiblingPath()
{
   const char* sibname = "NPFold_stamps_test" ; 
   const char* dirpath = "/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL" ; 
   std::string expect = "/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/NPFold_stamps_test" ; 
   std::string sibpath = U::FormSiblingPath(sibname, dirpath) ; 
   assert( strcmp(sibpath.c_str(), expect.c_str()) == 0 ) ; 
}

void test_FormExecutableSiblingPath(char** argv)
{
   const char* dirpath = "/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL" ; 
   std::string expect = "/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/U_test" ; 
   std::string sibpath = U::FormExecutableSiblingPath(argv[0], dirpath) ; 
   assert( strcmp(sibpath.c_str(), expect.c_str()) == 0 ) ; 
}

void test_SetEnvDefaultExecutableSiblingPath(char** argv)
{  
   const char* ekey = "FOLD" ; 
   const char* dirp = "/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL" ; 
   int rc = U::SetEnvDefaultExecutableSiblingPath( ekey, argv[0], dirp );    
   assert( rc == 0 );  
   char* eval = getenv(ekey); 

   std::cout 
       << "test_SetEnvDefaultExecutableSiblingPath"
       << std::endl 
       << " ekey " << ekey 
       << std::endl 
       << " dirp " << dirp 
       << std::endl 
       << " eval " << eval 
       << std::endl 
       ;
}

void test_LastDigit()
{
    const char* str = "0123456x,,]  " ; 

    char* p = U::LastDigit(str); 
    std::cout << " p {" << p << "}" <<  std::endl ; 

}

void test_FirstDigit()
{
    const char* str = "0123456x,,]  " ; 
    char* p = U::FirstDigit(str); 
    std::cout << " p {" << p << "}" <<  std::endl ; 
}
void test_FirstToLastDigit()
{
    std::vector<std::string> strs = {
        " no digits ",
        " one 1 digit ", 
        " two 12 digits",  
        ",,,,0123456x,,] ",
        " non 12 contig 34 " ,  
     } ; 

    int num = strs.size(); 
    for(int i=0 ; i < num ; i++)
    {
       const char* str = strs[i].c_str(); 
       char* p = U::FirstToLastDigit(str); 
       std::cout 
          << std::setw(40) << str 
          << " p {" << ( p ? p : "-" )<< "}" 
          <<  std::endl 
          ;
    } 
}


const char* LABELS = R"LITERAL(
t_BeginOfEvent
t_setGenstep_0
t_setGenstep_1
t_setGenstep_2
t_setGenstep_3
t_setGenstep_4
t_setGenstep_5
t_setGenstep_6
t_setGenstep_7
t_setGenstep_8
t_PreLaunch
t_PostLaunch
t_EndOfEvent
)LITERAL" ; 

void test_Summarize()
{
    std::stringstream fss(LABELS) ;
    std::string line ; 
    while(std::getline(fss, line)) 
    {        
        const char* smry = U::Summarize(line.c_str(), 7) ; 
        std::cout 
           << std::setw(60) << line 
           << " : " 
           << smry 
           << std::endl 
           ; 
    }
}

void test_LineVector()
{
    std::vector<std::string> lines ; 
    U::LineVector(lines, LABELS); 
    for(int i=0 ; i < int(lines.size()) ; i++) std::cout << lines[i] << std::endl ; 
}



int main(int argc, char** argv)
{
    /*
    test_FormSiblingPath(); 
    test_FormExecutableSiblingPath(argv); 
    test_SetEnvDefaultExecutableSiblingPath(argv); 

    test_LastDigit(); 
    test_FirstDigit(); 
    test_FirstToLastDigit(); 
    test_Summarize(); 
    */

    test_LineVector(); 

    return 0 ; 
}