
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

// Function that doubles elements of a 1D NumPy array
nb::ndarray<nb::numpy, double> process_array(nb::ndarray<nb::numpy, double> input) {
    // Ensure input is 1D
    if (input.ndim() != 1) {
        throw nb::type_error("Input array must be 1D");
    }
    size_t size = input.shape(0);
    // Create output array
    double* output_data = new double[size];
    const double* input_data = input.data();
    for (size_t i = 0; i < size; ++i) {
        output_data[i] = input_data[i] * 2.0;
    }
    // Return NumPy array (nanobind handles memory)
    return nb::ndarray<nb::numpy, double>(output_data, {size}, nb::handle());
}

NB_MODULE(my_ext, m) {
    m.def("process_array", &process_array, nb::arg("input").sig("numpy.ndarray"), nb::sig("def process_array(input: numpy.ndarray) -> numpy.ndarray"));
}

