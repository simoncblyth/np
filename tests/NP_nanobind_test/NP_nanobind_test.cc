/**
NP_nanobind_test.cc
=====================

https://nanobind.readthedocs.io/en/latest/basics.html#basics
https://nanobind.readthedocs.io/en/latest/ndarray.html

Experiement with C++ Python binding with nanobind

**/

#include "NP_nanobind.h"



struct Dog
{
    std::string name;
    std::string bark() const ;
};
inline std::string Dog::bark() const
{
    return name + ": woof!" ;
}



namespace nb = nanobind;
using namespace nb::literals;

using RGBImage = nb::ndarray<uint8_t, nb::shape<-1, -1, 3>, nb::device::cpu>;

void process3(RGBImage data)
{
    // treble brightness of the MxNx3 RGB image
    for (size_t y = 0; y < data.shape(0); ++y)
        for (size_t x = 0; x < data.shape(1); ++x)
            for (size_t ch = 0; ch < 3; ++ch)
                data(y, x, ch) = (uint8_t) std::min(255, data(y, x, ch) * 3);
}

nb::ndarray<nb::numpy, float> create_3d(size_t rows, size_t cols, size_t depth)
{
    size_t sz = rows * cols * depth ;
    float* data = new float[sz];
    for (size_t i = 0; i < sz; ++i) data[i] = (float)i;

    // delete data when owner capsule expires
    nb::capsule owner(data, [](void *p) noexcept { delete[] (float *)p ; });

    std::initializer_list<size_t> shape = {rows, cols, depth };

    return nb::ndarray<nb::numpy, float>( data, shape, owner );
}


// First arg is the module name which must match the first arg to nanobind_add_module in CMakeLists.txt
NB_MODULE(py_NP_nanobind_test, m)
{
    m.attr("the_answer") = 42;
    m.doc() = "A simple example python extension";

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

            return nb::ndarray<nb::numpy, float, nb::ndim<2>>(
                   data,
                   { rows, cols },
                   owner
            );
        }
    );
}


