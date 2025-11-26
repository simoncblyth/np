cmake_minimum_required(VERSION 3.14)
project(MyCurlProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++17 instead of -std=gnu++17

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")

message(STATUS "CURL library search paths: ${CMAKE_PREFIX_PATH}")
find_package(CURL REQUIRED)

# After find_package, dump everything CMake knows
message(STATUS "CURL_FOUND:        ${CURL_FOUND}")
message(STATUS "CURL_INCLUDE_DIRS: ${CURL_INCLUDE_DIRS}")
message(STATUS "CURL_LIBRARIES:    ${CURL_LIBRARIES}")
message(STATUS "CURL_VERSION:     ${CURL_VERSION_STRING}")

# Also read the version directly from curl.h if possible
if(CURL_INCLUDE_DIRS)
    file(STRINGS "${CURL_INCLUDE_DIRS}/curl/curl.h" _curl_version_str
         REGEX "^#define[\t ]+LIBCURL_VERSION[\t ]+\".*\"")
    string(REGEX REPLACE ".*\"(.*)\"" "\\1" CURL_VERSION_FROM_HEADER "${_curl_version_str}")
    message(STATUS "libcurl version from curl.h: ${CURL_VERSION_FROM_HEADER}")
endif()


add_executable(${PROJECT_NAME}
    np_curl_test.cc
)

target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../..)

