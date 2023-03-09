// ./uc4_test.sh

#include "NPX.h"

struct ModelTrigger_Debug
{
    static std::vector<ModelTrigger_Debug> record ; 
    void add(){ record.push_back(*this); }
    static NP* Array(){ return NPX::ArrayFromVec<float, ModelTrigger_Debug>( ModelTrigger_Debug::record ) ; }

    float x ; 
    float y ; 
    float z ; 
    uc4   w ; 
};

std::vector<ModelTrigger_Debug> ModelTrigger_Debug::record = {} ; 

void test_uc4()
{
    uc4 w ; 
    w.set("hello") ; 
    std::cout << w.get() << std::endl ; 
    std::cout << w.desc() << std::endl ; 
}

int main()
{
    assert( sizeof(ModelTrigger_Debug) == sizeof(unsigned)*4 ); 

    ModelTrigger_Debug dbg ; 

    dbg.x = 10.f ; 
    dbg.y = 100.f ; 
    dbg.z = 1000.f ; 
    dbg.w.set("HELLO"); 
    dbg.add();

    dbg.x = 20.f ; 
    dbg.y = 200.f ; 
    dbg.z = 2000.f ; 
    dbg.w.set("WORLD");     
    dbg.add(); 

    ModelTrigger_Debug::Array()->save("$FOLD/a.npy"); 

    return 0 ; 
}
/**
In [1]: t.a 
Out[1]: 
array([[      10.,      100.,     1000., 53548320.],
       [      20.,      200.,     2000., 55131484.]], dtype=float32)

In [2]: t.a[:,3]
Out[2]: array([53548320., 55131484.], dtype=float32)

In [3]: t.a[:,3].view("|S4")
Out[3]: array([b'HELL', b'WORL'], dtype='|S4')


**/

/**
    In [3]: a = np.array([1819043176], dtype=np.int32 )
    In [4]: a.view("|S4")
    Out[4]: array([b'hell'], dtype='|S4')

**/



