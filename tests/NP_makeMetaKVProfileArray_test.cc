// name=NP_makeMetaKVProfileArray_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main()
{
    NP* a = NP::Make<int>(0); 
    a->meta = R"LITERAL(
SEvt__setIndex_n003:1701421742355692,19238812,1276176
SEvt__endIndex_n003:1701421762192700,19321852,1357048
SEvt__setIndex_p003:1701421762333464,19349976,1385172
SEvt__endIndex_p003:1701421762511425,19349976,1385172
)LITERAL" ; 

    NP* p = a->makeMetaKVProfileArray("Index"); 
    std::cout << " p " << ( p ? p->sstr() : "-" ) << std::endl ; 

    std::cout << " p " << p->descTable<int64_t>(16) << std::endl ; 


    return 0 ;
}
