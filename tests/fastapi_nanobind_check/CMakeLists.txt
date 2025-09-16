cmake_minimum_required(VERSION 3.18)
project(my_ext)

find_package(Python REQUIRED COMPONENTS Interpreter Development)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

message(STATUS "${name} nanobind_ROOT  : ${nanobind_ROOT} ")

find_package(nanobind CONFIG REQUIRED)
message(STATUS "${name} nanobind_FOUND : ${nanobind_FOUND} ")


nanobind_add_module(my_ext NB_STATIC my_ext.cpp)
#target_link_libraries(my_ext PRIVATE nanobind::nanobind)

nanobind_add_stub(my_ext_stub
    MODULE my_ext
    OUTPUT my_ext.pyi
    PYTHON_PATH ${CMAKE_CURRENT_BINARY_DIR}
)




