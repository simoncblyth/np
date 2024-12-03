// ~/np/tests/NP_set_meta_get_meta_test.sh

const char* APATH = "$FOLD/a.npy" ; 

#include "NP.hh"


void test_string()
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
}


void test_uint64()
{
    NP* a = NP::Make<float>(1,4,4); 
    uint64_t u0 = std::numeric_limits<uint64_t>::max() ; 
    a->set_meta<uint64_t>("u", u0 ); 
    a->save(APATH);  
    NP* b = NP::Load(APATH);  
 
    uint64_t u1 = b->get_meta<uint64_t>("u", 0) ; 

    std::cout << " u0 " << u0 << std::endl ; 
    std::cout << " u1 " << u1 << std::endl ; 
}

int main()
{
    test_uint64(); 

    return 0 ; 
}
