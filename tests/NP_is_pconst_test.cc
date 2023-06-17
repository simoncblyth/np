// name=NP_is_pconst_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    NP* a = NP::LoadFromString<double>(R"(
    1.55     *eV    1.0
    6.2      *eV    1.0
    10.33    *eV    1.0 
    15.5     *eV    1.0
)" ); 

    bool ipc = a->is_pconst<double>() ; 
    double pc = a->pconst<double>(-1) ; 
    double pl = a->plhs<double>(0) ; 
    double pr = a->prhs<double>(0) ; 

    std::cout 
        << " ipc " << ipc 
        << " pc " << pc 
        << " pl " << pl 
        << " pr " << pr 
        << std::endl
        ; 

    NP* b = NP::MakePCopyNotDumb<double>(a ); 
 
    a->save("/tmp/a.npy"); 
    b->save("/tmp/b.npy"); 


    return 0 ; 
}
