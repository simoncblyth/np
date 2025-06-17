#include "NP.hh"

int main()
{
    int num_items = 10 ;

    std::vector<std::string> slis = {
         "[:5]",
         "[::2]",
         "[1:10]",
         "[1:10:2]"
    };

    std::vector<NP_slice> xslis = {
           {0,5,1},
           {0,num_items,2},
           {1,10,1},
           {1,10,2}
    };

    int nsli = slis.size();
    for(int i=0 ; i < nsli ; i++)
    {
        const char* _sli = slis[i].c_str();

        const NP_slice& xsli = xslis[i] ;

        NP_slice sli = {} ;

        sli.start = 0 ;
        sli.stop = num_items ;
        sli.step = 1 ;

        int rc = NP::ParseSliceIndexString(sli.start, sli.stop, sli.step, _sli );

        bool match = sli.is_match(xsli);

        std::cout
            << "_sli {" << std::setw(15) << _sli << "}"
            << " sli.desc " << std::setw(20) << sli.desc()
            << " xsli.desc " << std::setw(20) << xsli.desc()
            << " match " << ( match ? "YES" : "NO " )
            << " rc " << rc
            << "\n"
            ;
    }

    return 0 ;
}





