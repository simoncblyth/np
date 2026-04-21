#include "NPFold.h"

template<typename T>
NP* make_array(size_t ni, size_t pad )
{
    NP* a = NP::Make<T>(ni, 2);
    T* aa = a->values<T>();
    const T zero(0.);
    for(size_t i=0 ; i < ni ; i++ )
    {
        bool is_padding = i < pad || ( i > ni - pad ) ;
        T domain = T(1+i) ;
        T value = is_padding ? zero : T(1+i) ;
        aa[2*i+0] = domain ;
        aa[2*i+1] = value ;
    }
    return a ;
}

int main()
{
    const NP* a0 = make_array<float>(100, 10);  // some padding
    const NP* b0 = make_array<float>(100, 0);  // no padding
    const NP* c0 = make_array<float>(100, 100); // all padding

    const NP* d0 = make_array<double>(100, 10);  // some padding
    const NP* e0 = make_array<double>(100, 0);  // no padding
    const NP* f0 = make_array<double>(100, 100); // all padding

    NPFold* f = new NPFold ;

    f->add("a0", a0); f->add("a1", NP::MakePCopyStripZeroPadding(a0));
    f->add("b0", b0); f->add("b1", NP::MakePCopyStripZeroPadding(b0));
    f->add("c0", c0); f->add("c1", NP::MakePCopyStripZeroPadding(c0));

    f->add("d0", d0); f->add("d1", NP::MakePCopyStripZeroPadding(d0));
    f->add("e0", e0); f->add("e1", NP::MakePCopyStripZeroPadding(e0));
    f->add("f0", f0); f->add("f1", NP::MakePCopyStripZeroPadding(f0));

    f->save("$FOLD");

    return 0;
}
