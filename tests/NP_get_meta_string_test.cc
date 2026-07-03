#include "NP.hh"

static const char* METADATA_WITH_BOTH = R"(
OTHER:hello
TESTSCRIPT:the-testscript
SCRIPT:the-script
BOTHER:world
)" ;

static const char* METADATA_WITH_ONE = R"(
OTHER:hello
SCRIPT:the-script
BOTHER:world
)" ;


int main()
{
    {
        const char* kk = "TESTSCRIPT|SCRIPT" ;
        std::string value_both = NP::get_meta_string_(METADATA_WITH_BOTH, kk);
        std::string value_one  = NP::get_meta_string_(METADATA_WITH_ONE , kk);
        std::cout << "value_both : [" << value_both << "]\n" ;
        assert( value_both == "the-testscript" );
        std::cout << "value_one  : [" << value_one << "]\n" ;
        assert( value_one == "the-script" );
    }

    {
        const char* kk = "SCRIPT|TESTSCRIPT" ;
        std::string value_both = NP::get_meta_string_(METADATA_WITH_BOTH, kk);
        std::string value_one = NP::get_meta_string_(METADATA_WITH_ONE, kk);
        std::cout << "value_both : [" << value_both << "]\n" ;
        assert( value_both == "the-script" );
        std::cout << "value_one : [" << value_one << "]\n" ;
        assert( value_one == "the-script" );
    }

}
