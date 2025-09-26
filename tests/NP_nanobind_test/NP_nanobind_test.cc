/**
NP_nanobind_test.cc
=====================

https://nanobind.readthedocs.io/en/latest/basics.html#basics
https://nanobind.readthedocs.io/en/latest/ndarray.html

Experiment with C++ Python binding with nanobind

**/

#include "NP_nanobind.h"
namespace nb = nanobind;
using namespace nb::literals;




struct Dog
{
    std::string name;
    std::string bark() const ;
};
inline std::string Dog::bark() const
{
    return name + ": woof!" ;
}

 //  https://nanobind.readthedocs.io/en/latest/api_core.html#parameterized-wrapper-classes

struct Processor
{
    Processor();

    nb::ndarray<nb::numpy> process(nb::ndarray<nb::numpy> in);
    nb::ndarray<nb::numpy> process_via_NP(nb::ndarray<nb::numpy> in);
    nb::tuple              process_via_NP_with_meta(nb::ndarray<nb::numpy> _in, nb::str _meta);
};

inline Processor::Processor()
{
}

inline  nb::ndarray<nb::numpy> Processor::process(nb::ndarray<nb::numpy> in)
{
    std::cout << "[Processor::process\n";
    nanobind::dlpack::dtype in_dtype = in.dtype();
    if( in_dtype != nanobind::dtype<float>() ) return nb::ndarray<nb::numpy>(in);

    size_t ndim = in.ndim();
    std::vector<size_t> shape(ndim);
    for(size_t d=0 ; d < ndim ; d++) shape[d] = in.shape(d);
    size_t sz = in.size();

    std::cout << "-Processor::process ndim " << ndim << " sz " << sz << "\n";

    float* in_data = (float*)in.data();
    float* out_data = new float[sz];
    for(size_t i=0 ; i < sz ; i++) out_data[i] = 1000.f + 2.f*in_data[i] ;

    int64_t *strides = nullptr ;
    nb::capsule owner(out_data, [](void *p) noexcept { delete[] (float *)p ; });
    nb::ndarray<nb::numpy> out = nb::ndarray<nb::numpy>( out_data, ndim, shape.data(), owner, strides, in_dtype );

    std::cout << "]Processor::process\n";
    return out ;
}

inline  nb::ndarray<nb::numpy> Processor::process_via_NP(nb::ndarray<nb::numpy> _in)
{
    std::cout << "[Processor::process_via_NP\n";

    NP* in = NP_nanobind::NP_copy_of_numpy_array(_in);
    NP* out = NP::MakeLike(in);
    out->set_meta<int>("answer", 42 );  // HMM: how for this to survive ?
    std::cout << "-Processor::process_via_NP set_meta called \n";


    float* ii = in->values<float>();
    float* oo = out->values<float>();
    NP::INT nv = in->num_values();
    for(NP::INT i=0 ; i < nv ; i++) oo[i] = 1000.f + 2.f*ii[i] ;


    nb::ndarray<nb::numpy> _out = NP_nanobind::numpy_array_view_of_NP(out) ;

    std::cout << "]Processor::process_via_NP\n";
    return _out ;
}

inline  nb::tuple Processor::process_via_NP_with_meta(nb::ndarray<nb::numpy> _in, nb::str _in_meta)
{
    std::cout << "[Processor::process_via_NP_with_meta\n";

    NP* in = NP_nanobind::NP_copy_of_numpy_array_with_meta(_in, _in_meta);
    std::cout << "-Processor::process_via_NP_with_meta in.meta[" << in->meta << "]\n" ;

    NP* out = NP::MakeLike(in);
    out->set_meta<int>("answer", 42 );  // HMM: how for this to survive ?
    std::cout << "-Processor::process_via_NP_with_meta set_meta called \n";

    float* ii = in->values<float>();
    float* oo = out->values<float>();
    NP::INT nv = in->num_values();
    for(NP::INT i=0 ; i < nv ; i++) oo[i] = 1000.f + 2.f*ii[i] ;

    nb::tuple _out = NP_nanobind::numpy_array_view_of_NP_with_meta(out);
    std::cout << "]Processor::process_via_NP_with_meta\n";
    return _out ;
}



using RGBImage = nb::ndarray<uint8_t, nb::shape<-1, -1, 3>, nb::device::cpu>;

void process3(RGBImage data)
{
    // treble brightness of the MxNx3 RGB image
    for (size_t y = 0; y < data.shape(0); ++y)
        for (size_t x = 0; x < data.shape(1); ++x)
            for (size_t ch = 0; ch < 3; ++ch)
                data(y, x, ch) = (uint8_t) std::min(255, data(y, x, ch) * 3);
}

nb::ndarray<float, nb::numpy> create_3d(size_t rows, size_t cols, size_t depth)
{
    size_t sz = rows * cols * depth ;
    float* data = new float[sz];
    for (size_t i = 0; i < sz; ++i) data[i] = (float)i;

    // delete data when owner capsule expires
    nb::capsule owner(data, [](void *p) noexcept { delete[] (float *)p ; });

    std::initializer_list<size_t> shape = {rows, cols, depth };

    return nb::ndarray<float, nb::numpy>( data, shape, owner );
}


// First arg is the module name which must match the first arg to nanobind_add_module in CMakeLists.txt
NB_MODULE(py_NP_nanobind_test, m)
{
    m.attr("the_answer") = 42;
    m.doc() = "A simple example python extension";

    nb::class_<Processor>(m, "Processor")
        .def(nb::init<>())
        .def("process", &Processor::process)
        .def("process_via_NP", &Processor::process_via_NP)
        .def("process_via_NP_with_meta", &Processor::process_via_NP_with_meta)
        ;

    nb::class_<Dog>(m, "Dog")
        .def(nb::init<>())
        .def(nb::init<const std::string &>())
        .def("bark", &Dog::bark)
        .def_rw("name", &Dog::name)
        .def("__repr__", [](const Dog &p) { return "<my_ext.Dog named '" + p.name + "'>"; })
        .def("bark_later", [](const Dog &p) {
                 auto callback = [name = p.name] { nb::print(nb::str("{}: woof!").format(name));};
                 return nb::cpp_function(callback);
         })
         ;


    m.def("inspect", [](const nb::ndarray<>& a) {
        printf("Array data pointer : %p\n", a.data());
        printf("Array dimension : %zu\n", a.ndim());
        for (size_t i = 0; i < a.ndim(); ++i) {
            printf("Array dimension [%zu] : %zu\n", i, a.shape(i));
            printf("Array stride    [%zu] : %ld\n", i, a.stride(i));
        }
        printf("Device ID = %u (cpu=%i, cuda=%i)\n", a.device_id(),
            int(a.device_type() == nb::device::cpu::value),
            int(a.device_type() == nb::device::cuda::value)
        );
        printf("Array dtype: int16=%i, uint32=%i, float32=%i\n",
            a.dtype() == nb::dtype<int16_t>(),
            a.dtype() == nb::dtype<uint32_t>(),
            a.dtype() == nb::dtype<float>()
        );
    });

    m.def("process", [](RGBImage data)
    {
        // Double brightness of the MxNx3 RGB image
        for (size_t y = 0; y < data.shape(0); ++y)
            for (size_t x = 0; x < data.shape(1); ++x)
                for (size_t ch = 0; ch < 3; ++ch)
                    data(y, x, ch) = (uint8_t) std::min(255, data(y, x, ch) * 2);
    });

    m.def("process3", &process3 );

    m.def("create_3d", &create_3d );

    m.def("example_numpy_array_view_of_NP", &NP_nanobind::example_numpy_array_view_of_NP );

    m.def("roundtrip_numpy_array_via_NP", &NP_nanobind::roundtrip_numpy_array_via_NP );


    m.def("create_2d",
        [](size_t rows, size_t cols)
        {
            // Allocate a memory region and initialize it
            float *data = new float[rows * cols];
            for (size_t i = 0; i < rows * cols; ++i) data[i] = (float) i;

            // Delete 'data' when the 'owner' capsule expires
            nb::capsule owner(data,
               [](void *p) noexcept
               {
                    delete[] (float *) p;
               }
            );

            return nb::ndarray<float, nb::numpy, nb::ndim<2>>(
                   data,
                   { rows, cols },
                   owner
            );
        }
    );
}


