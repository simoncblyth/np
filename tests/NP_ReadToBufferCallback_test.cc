/**
NP_ReadToBufferCallback_test.cc
=================================

**/


#include "NP.hh"


int main()
{
    NP* a = NP::Make<float>(1,4,4);
    a->fillIndexFlat();
    a->set_meta<int>("red", 1);
    a->set_meta<int>("green", 2);
    a->set_meta<int>("blue", 3);
    a->set_meta<float>("cyan", 2.14);
    a->set_meta<float>("pi", M_PI);

    std::cout << "a.meta[\n" << a->meta << "]\n" ;

    a->save("$FOLD/a0.npy");
    //a->update_headers();  // saving does this already

    std::vector<char> buf0 ;
    a->serializeToBuffer(buf0, 1, 1);
    std::cout
         << "[NP_ReadToBufferCallback_test.HexDump.buf0\n"
         << NP::HexDump( buf0.data(), buf0.size() )
         << "]NP_ReadToBufferCallback_test.HexDump,buf0\n"
         ;
    NP::SaveBufferToFile(buf0, "$FOLD/a1.npy" );


    NP* a2 = nullptr ;
    {
        a2 = NP::LoadFromBuffer_( buf0.data(), buf0.size() );
        std::cout << "-NP_ReadToBufferCallback_test.a2 " << a2->sstr() << "\n" ;
        a2->save("$FOLD/a2.npy");
    }

    NP* a3 = nullptr ;
    {
        std::cout << "[NP_ReadToBufferCallback_test.CreateFromBuffer\n" ;
        size_t size = 1 ;
        size_t nitems = 1;
        a3 = NP::CreateFromBuffer( buf0, size, nitems);
        std::cout << "-NP_ReadToBufferCallback_test.CreateFromBuffer.a3 " << a3->sstr() << "\n" ;
        a3->save("$FOLD/a3.npy");
        std::cout << "]NP_ReadToBufferCallback_test.CreateFromBuffer\n" ;
    }

    std::cout << "[NP_ReadToBufferCallback_test.serializeToBuffer\n" ;
    std::vector<char> buf1 ;
    a3->serializeToBuffer(buf1);
    std::cout
         << "[NP_ReadToBufferCallback_test.HexDump.buf1\n"
         << NP::HexDump( buf1.data(), buf1.size() )
         << "]NP_ReadToBufferCallback_test.HexDump,buf1\n"
         ;

    NP::SaveBufferToFile(buf1, "$FOLD/a4.npy" );
    std::cout << "]NP_ReadToBufferCallback_test.serializeToBuffer\n" ;


    return 0;
}
