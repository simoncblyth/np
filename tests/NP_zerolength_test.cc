// name=NP_zerolength_test ; gcc $name.cc -I.. -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name

#include "NP.hh"

int main(int argc, char** argv)
{
    const char* a_path = "/tmp/a.npy" ; 
    const char* b_path = "/tmp/b.npy" ; 

    const NP* a = NP::Make<double>(0, 2) ; 
    a->save(a_path); 

    const NP* b = NP::Load(a_path) ; 
    b->save(b_path); 

    NP* c = NP::Make<double>( 2, 2 ); 

    double* cc = c->values<double>() ; 
    cc[0] = 10. ; 
    cc[1] = 100. ; 
    cc[2] = 20. ; 
    cc[3] = 100. ; 

    std::vector<const NP*> vv ; 
    vv.push_back(a); 
    vv.push_back(b); 
    vv.push_back(const_cast<const NP*>(c)); 

    NP* com = NP::Combine(vv); 
    com->save("/tmp/com.npy" );

    return 0 ; 
}

/**

    In [1]: com = np.load("/tmp/com.npy")

    In [2]: com
    Out[2]: 
    array([[[  0.,   0.],
            [  0.,   0.],
            [  0.,   0.]],

           [[  0.,   0.],
            [  0.,   0.],
            [  0.,   0.]],

           [[ 10., 100.],
            [ 20., 100.],
            [  0.,   0.]]])

    In [3]: com.shape
    Out[3]: (3, 3, 2)

    In [5]: com[:,-1,-1].view(np.uint64)
    Out[5]: array([0, 0, 2], dtype=uint64)

**/


