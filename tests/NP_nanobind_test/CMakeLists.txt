cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(name NP_nanobind_test)
project(${name} VERSION 0.1.0 LANGUAGES CXX CUDA)

find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

find_package(nanobind CONFIG)
message(STATUS "${name} nanobind_ROOT  : ${nanobind_ROOT} ")
message(STATUS "${name} nanobind_FOUND : ${nanobind_FOUND} ")

set(py_ext py_${name})
if(nanobind_FOUND)
   nanobind_add_module(${py_ext} ${name}.cc)

   target_include_directories(${py_ext} PUBLIC ../..)

   #target_link_libraries(${py_ext} PUBLIC ${name})

   install(TARGETS ${py_ext} LIBRARY DESTINATION py)
endif()

#[=[
Use from python with: "import py_NP_nanobind_test as nbt"
#]=]


