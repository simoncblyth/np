// name=NPdivide_by_lastTest ; mkdir -p /tmp/$name ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name && /tmp/$name/$name
#include <vector>
#include <iostream>
#include "NP.hh"

void test_divide_by_last_1d()
{
    NP* a = NP::Linspace<double>(0., 10., 11) ;  
    a->divide_by_last<double>(); 
    a->dump(0,11); 
}

void test_divide_by_last_2d()
{
    NP* a = NP::Make<double>(20, 11);  
    double* aa = a->values<double>(); 
    unsigned ni = a->shape[0] ; 
    unsigned nj = a->shape[1] ; 

    for(unsigned i=0 ; i < ni ; i++)
    {
        for(unsigned j=0 ; j < nj ; j++)
        {
             aa[nj*i + j] = double(i)*double(j) ; 
        }
    }
    a->save("/tmp/NPdivide_by_lastTest/a.npy"); 
    a->divide_by_last<double>(); 
    a->save("/tmp/NPdivide_by_lastTest/b.npy"); 
}

/*
epsilon:tests blyth$ ipython -c "print(np.load('/tmp/NPdivide_by_lastTest/a.npy'))"
[[  0.   0.   0.   0.   0.   0.   0.   0.   0.   0.   0.]
 [  0.   1.   2.   3.   4.   5.   6.   7.   8.   9.  10.]
 [  0.   2.   4.   6.   8.  10.  12.  14.  16.  18.  20.]
 [  0.   3.   6.   9.  12.  15.  18.  21.  24.  27.  30.]
 [  0.   4.   8.  12.  16.  20.  24.  28.  32.  36.  40.]
 [  0.   5.  10.  15.  20.  25.  30.  35.  40.  45.  50.]
 [  0.   6.  12.  18.  24.  30.  36.  42.  48.  54.  60.]
 [  0.   7.  14.  21.  28.  35.  42.  49.  56.  63.  70.]
 [  0.   8.  16.  24.  32.  40.  48.  56.  64.  72.  80.]
 [  0.   9.  18.  27.  36.  45.  54.  63.  72.  81.  90.]
 [  0.  10.  20.  30.  40.  50.  60.  70.  80.  90. 100.]
 [  0.  11.  22.  33.  44.  55.  66.  77.  88.  99. 110.]
 [  0.  12.  24.  36.  48.  60.  72.  84.  96. 108. 120.]
 [  0.  13.  26.  39.  52.  65.  78.  91. 104. 117. 130.]
 [  0.  14.  28.  42.  56.  70.  84.  98. 112. 126. 140.]
 [  0.  15.  30.  45.  60.  75.  90. 105. 120. 135. 150.]
 [  0.  16.  32.  48.  64.  80.  96. 112. 128. 144. 160.]
 [  0.  17.  34.  51.  68.  85. 102. 119. 136. 153. 170.]
 [  0.  18.  36.  54.  72.  90. 108. 126. 144. 162. 180.]
 [  0.  19.  38.  57.  76.  95. 114. 133. 152. 171. 190.]]

epsilon:tests blyth$ ipython -c "print(np.load('/tmp/NPdivide_by_lastTest/b.npy'))"
[[0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]
 [0.  0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1. ]]
epsilon:tests blyth$ 


*/



void test_divide_by_last_3d()
{
    NP* a = NP::Make<double>(20, 11, 2);  
    double* aa = a->values<double>(); 
    unsigned ni = a->shape[0] ; 
    unsigned nj = a->shape[1] ; 
    unsigned nk = a->shape[2] ; 

    for(unsigned i=0 ; i < ni ; i++)
    {
        for(unsigned j=0 ; j < nj ; j++)
        {
            for(unsigned k=0 ; k < nk ; k++)
            { 
                aa[nj*nk*i + j*nk + k] = k == 0 ? double(i*1000) + double(j) : double(i)*double(j) ; 
            }
        }
    }
    a->save("/tmp/NPdivide_by_lastTest/a.npy"); 
    a->divide_by_last<double>(); 
    a->save("/tmp/NPdivide_by_lastTest/b.npy"); 
}

/**

epsilon:tests blyth$ ipython -c "print(np.load('/tmp/NPdivide_by_lastTest/a.npy')[-1])"
[[19000.     0.]
 [19001.    19.]
 [19002.    38.]
 [19003.    57.]
 [19004.    76.]
 [19005.    95.]
 [19006.   114.]
 [19007.   133.]
 [19008.   152.]
 [19009.   171.]
 [19010.   190.]]
epsilon:tests blyth$ ipython -c "print(np.load('/tmp/NPdivide_by_lastTest/b.npy')[-1])"
[[19000.      0. ]
 [19001.      0.1]
 [19002.      0.2]
 [19003.      0.3]
 [19004.      0.4]
 [19005.      0.5]
 [19006.      0.6]
 [19007.      0.7]
 [19008.      0.8]
 [19009.      0.9]
 [19010.      1. ]]
epsilon:tests blyth$ 


**/


int main(int argc, char** argv)
{
    //test_divide_by_last_1d(); 
    //test_divide_by_last_2d(); 
    test_divide_by_last_3d(); 

    return 0 ;
}

