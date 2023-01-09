// name=NP_ArrayFromVec_test ; mkdir /tmp/$name ; export FOLD=/tmp/$name ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name && /tmp/$name/$name


#include "NP.hh"

struct Demo
{
    int idx ; 
    int pad ; 
    double a ; 
    double b ; 
    double c ; 
};

const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    std::vector<Demo> dd ; 

    Demo d0 = { 0,0, 10. , 20. , 30.  }; 
    Demo d1 = { 1,0, 100., 200., 300. }; 
    Demo d2 = { 2,0, 1000., 2000., 3000. }; 
    
    dd.push_back(d0);    
    dd.push_back(d1);    
    dd.push_back(d2);    


    NP* a = NP::ArrayFromVec<double, Demo>( dd, 2, 2) ; 
    a->save(FOLD, "a.npy") ; 

    NP* b = NP::ArrayFromVec<double, Demo>( dd ) ; 
    b->save(FOLD, "b.npy") ; 



    return 0 ; 
}  
