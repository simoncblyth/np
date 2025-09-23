/**
NP_ReadToBufferCallback_test.cc
=================================

**/


#include "NP.hh"


int main()
{
    NP* a = NP::Make<float>(1,4,4);
    a->fillIndexFlat();
    a->save("$FOLD/a0.npy");
    a->update_headers();

    std::vector<char> buf ;
    a->serializeHeaderAndDataToBuffer(buf);
    NP::SaveBufferToFile(buf, "$FOLD/a1.npy" );

    std::cout << NP::HexDump( buf.data(), buf.size() );

    NP* a2 = NP::LoadFromBuffer_( buf.data(), buf.size() );
    std::cout << " a2 " << a2->sstr() << "\n" ;
    a2->save("$FOLD/a2.npy");

    return 0;
}
