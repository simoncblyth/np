// ./NPX_MakeCharArray_test.sh 
#include "NPX.h"

int main()
{
    std::vector<std::string> vec = {{
       "hello", 
       "world",
       "longer with spaces", 
       "red",
       "green",
       "blue"
     }} ; 
 
    NP* a = NPX::MakeCharArray(vec); 
    a->save("$FOLD/a.npy"); 

    return 0 ;    
}

/**

    In [12]: nn = f.a.view("|S%d" % f.a.shape[1] ) ; nn
    Out[12]: 
    array([[b'hello'],
           [b'world'],
           [b'longer with spaces'],
           [b'red'],
           [b'green'],
           [b'blue']], dtype='|S19')


**/

