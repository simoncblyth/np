// gcc NPTest.cc -std=c++11  -I.. -lstdc++ -o /tmp/NPTest && /tmp/NPTest

#include <iostream>
#include <sstream>
#include "NP.hh"

std::string make_path(const char* dtype, const char* ext)
{
    std::stringstream ss ; 
    ss << "/tmp/NPTest_" << *(dtype+1) << *(dtype+2) << ext ; 
    return ss.str();  
} 

void test_lifecycle(const char* dtype, int ni, int nj=-1, int nk=-1, int nl=-1, int nm=-1 )
{
    std::string npy = make_path(dtype, ".npy" ); 
    std::string nph = make_path(dtype, ".nph" ); 
    std::string npj = make_path(dtype, ".npj" ); 
    const char* path = npy.c_str(); 

    std::cout 
        << "test_lifecycle"
        << " dtype " << dtype 
        << " npy " << npy 
        << " nph " << nph
        << " npj " << npj 
        << std::endl
        ; 

    NP* a = new NP(dtype, ni, nj, nk, nl, nm)  ;  
    a->fillIndexFlat(); 

    std::cout << " a.desc " << a->desc() << std::endl ; 

    a->save(path); 
    a->save_header(nph.c_str()) ; 
    a->save_jsonhdr(npj.c_str());

    NP* b = NP::Load(npy.c_str()); 

    std::cout << " b.desc " << b->desc() << std::endl ; 
    b->dump(); 

    int rc = NPU::check(path) ;  
    assert( rc == 0 ); 
}


void test_lifecycle()
{
    //std::vector<std::string> dtypes = {"<f4" , "<f8" , "<i1", "<i2", "<i4", "<i8" , "<u1", "<u2", "<u4", "<u8" }; 
    std::vector<std::string> dtypes = {"<f4" , "<f8" }; 
    //std::vector<std::string> dtypes = { "<u1" }; 

    for(unsigned i=0 ; i < dtypes.size() ; i++)
    {
        const char* dtype = dtypes[i].c_str() ; 
        test_lifecycle( dtype, 10, 4 );  
    } 
}

void test_format()
{
    float a=42.0 ; 
    std::cout << std::setw(10) << std::fixed << std::setprecision(3)  << a << std::endl ; 
}


void test_sizeof()
{
    assert( sizeof(float) == 4  ); 
    assert( sizeof(double) == 8  ); 

    assert( sizeof(char) == 1 ); 
    assert( sizeof(short) == 2 ); 
    assert( sizeof(int)   == 4 ); 
    assert( sizeof(long)  == 8 ); 
    assert( sizeof(long long)  == 8 ); 
}

int main(int argc, char** argv)
{
    test_sizeof(); 
    test_lifecycle(); 
    //test_format(); 
    return 0 ; 
}

