// ./NP_MakeSliceSelection_test.sh

#include "NP.hh"
#include "NPFold.h"

int test_ParseSliceString()
{
    std::vector<NP::INT> idxx ;
    const char* sli = "  [:,0,0,2]<0.5  " ;
    NP::ParseSliceString(idxx, sli );

    std::cout << "test_ParseSliceString idxx.size " << idxx.size() << "\n" ;

    assert( idxx.size() == 4 );
    assert( idxx[0] == -1 );
    assert( idxx[1] ==  0 );
    assert( idxx[2] ==  0 );
    assert( idxx[3] ==  2 );
    return 0 ;
}

int test_makeWhereSelection()
{
    NP* src = NP::Load("$AFOLD/record.npy");
    std::vector<std::string> sels = {{
       "  [:,0,0,0] < 0  ",
       "  [:,0,0,0] > 0  ",
       "  [:,0,0,0] < 0.5  ",
       "  [:,0,0,0] > 0.5  "
    }} ;

    std::cout << "[test_makeWhereSelection\n" ;
    for(int i=0 ; i < int(sels.size()) ; i++)
    {
        const char* _sel = sels[i].c_str();
        NP* sel = src->makeWhereSelection<float>( _sel );
        std::cout
            << " _sel " << std::setw(20) << _sel
            << " sel " << std::setw(20) << ( sel ? sel->sstr() : "-" )
            << "\n"
            ;
    }
    std::cout << "]test_makeWhereSelection\n" ;
    return 0 ;
}


int test_MakeSliceSelection()
{
    NP* src = NP::Load("$AFOLD/record.npy");

    std::vector<std::string> sels = {{
       "  [:,0,0,0] < 0  ",
       "  [:,0,0,0] > 0  ",
       "  [:,0,0,0] < 0.5  ",
       "  [:,0,0,0] > 0.5  "
    }} ;
    std::vector<std::string> labs = {{
       "a",
       "b",
       "c",
       "d"
    }};

    NPFold* fold = new NPFold ;

    std::cout << "[test_MakeSliceSelection src " << ( src ? src->sstr() : "-" ) << "\n" ;
    for(int i=0 ; i < int(sels.size()) ; i++)
    {
        const char* _sel = sels[i].c_str();
        const char* _lab = labs[i].c_str();
        NP* dst = NP::MakeSliceSelection<float>( src,  _sel );
        std::cout
            << " _sel " << std::setw(20) << _sel
            << " dst " << std::setw(20) << ( dst ? dst->sstr() : "-" )
            << "\n"
            ;
       fold->add(_lab, dst);

    }
    std::cout << "]test_MakeSliceSelection\n" ;
    fold->save("$FOLD/MakeSliceSelection");
    return 0 ;
}


int test_LoadSlice()
{

    std::vector<std::string> sels = {{
       "  [:,0,0,0] < 0  ",
       "  [:,0,0,0] > 0  ",
       "  [:,0,0,0] < -1.0  ",
       "  [:,0,0,0] > +1.0  ",
       "",
       "NULL",
       "$AFOLD_RECORD_SLICE"
    }} ;
    std::vector<std::string> labs = {{
       "a",
       "b",
       "c",
       "d",
       "e",
       "f",
       "g"
    }};

    NPFold* fold = new NPFold ;

    std::cout << "[test_LoadSlice\n" ;
    for(int i=0 ; i < int(sels.size()) ; i++)
    {
        const char* _sel = sels[i].c_str();
        const char* _lab = labs[i].c_str();
        if(strcmp(_sel, "NULL")==0) _sel = nullptr ;
        NP* dst = NP::LoadSlice<float>("$AFOLD/record.npy", _sel);
        std::cout
            << " _lab " << std::setw(20) << _lab
            << " _sel " << std::setw(20) << ( _sel ? _sel : "-" )
            << " dst " << std::setw(20) << ( dst ? dst->sstr() : "-" )
            << "\n"
            ;
       fold->add(_lab, dst);

    }
    std::cout << "]test_LoadSlice\n" ;
    fold->save("$FOLD/LoadSlice");
    return 0 ;
}





int main(int argc, char** argv)
{
    //const char* DEFTEST = "ParseSliceString" ;
    //const char* DEFTEST = "makeWhereSelection" ;
    //const char* DEFTEST = "MakeSliceSelection" ;
    const char* DEFTEST = "LoadSlice" ;
    const char* TEST = U::GetEnv("TEST", DEFTEST) ;
    bool ALL = strcmp(TEST, "ALL") == 0 ;
    int rc = 0 ;
    if(ALL||0==strcmp(TEST,"ParseSliceString"))   rc += test_ParseSliceString();
    if(ALL||0==strcmp(TEST,"makeWhereSelection")) rc += test_makeWhereSelection();
    if(ALL||0==strcmp(TEST,"MakeSliceSelection")) rc += test_MakeSliceSelection();
    if(ALL||0==strcmp(TEST,"LoadSlice"))          rc += test_LoadSlice();


    return rc ;
}

