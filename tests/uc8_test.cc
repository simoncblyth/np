// ./uc8_test.sh

#include "NPX.h"

struct ModelTrigger_Debug
{
    static std::vector<ModelTrigger_Debug> record ; 
    void add(){ record.push_back(*this); }

    double x ; 
    double y ; 
    double z ; 
    uc8   etrig ; 
};

std::vector<ModelTrigger_Debug> ModelTrigger_Debug::record = {} ; 

void test_uc8()
{
    uc8 u ; 
    u.set("hello world") ; 
    std::cout << u.get() << std::endl ; 
    std::cout << u.desc() << std::endl ; 
}

void test_ModelTrigger_Debug()
{
    assert( sizeof(ModelTrigger_Debug) == sizeof(uint64_t)*4 ); 

    ModelTrigger_Debug dbg ; 

    dbg.x = 10. ; 
    dbg.y = 100. ; 
    dbg.z = 1000. ; 
    dbg.etrig.set("HELLO"); 
    dbg.add();

    dbg.x = 20. ; 
    dbg.y = 200. ; 
    dbg.z = 2000. ; 
    dbg.etrig.set("WORLD");     
    dbg.add(); 

    NP* a = NPX::ArrayFromVec<double, ModelTrigger_Debug>( ModelTrigger_Debug::record ) ; 

    a->save("$FOLD/a.npy"); 
}



int main()
{
    //test_uc8(); 
    test_ModelTrigger_Debug(); 

    return 0 ; 
}

/**

In [1]: t.a
Out[1]: 
array([[  10.,  100., 1000.,    0.],
       [  20.,  200., 2000.,    0.]])

In [2]: t.a[:,3]
Out[2]: array([0., 0.])

In [3]: t.a[:,3].view("|S8")
Out[3]: array([b'HELLO', b'WORLD'], dtype='|S8')


**/
