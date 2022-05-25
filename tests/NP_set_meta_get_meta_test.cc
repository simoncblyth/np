// name=NP_set_meta_get_meta_test ; mkdir -p /tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -DDEBUG -o /tmp/$name/$name && /tmp/$name/$name

const char* PATH = "/tmp/NP_set_meta_get_meta_test/a.npy" ; 

#include "NP.hh"

int main()
{
    const char* o_msg = "metadata_string with some blank spaces on the line" ; 

    NP* a = NP::Make<float>(1,4,4); 
    a->set_meta<std::string>("msg", o_msg) ; 

    std::string a_msg = a->get_meta<std::string>("msg", "" ); 

    a->save(PATH); 
    NP* b = NP::Load(PATH);  

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
