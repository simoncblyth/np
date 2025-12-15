cmake_minimum_required(VERSION 3.14)
set(name np_curl_test)
project(${name} LANGUAGES CXX)
include(GNUInstallDirs)

list(APPEND CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})

message("${name}.ENV{CMAKE_PREFIX_PATH} contents:")
foreach(p $ENV{CMAKE_PREFIX_PATH})
    message("   → ${p}")
endforeach()

message("${name}.CMAKE_PREFIX_PATH contents:")
foreach(p ${CMAKE_PREFIX_PATH})
    message("   → ${p}")
endforeach()




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++17 instead of -std=gnu++17

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")

message(STATUS "CURL library search paths: ${CMAKE_PREFIX_PATH}")
find_package(CURL 8.12.1 QUIET)   # QUIET = don’t print "not found" yet

if(CURL_FOUND)
    message(STATUS "Found suitable libcurl ${CURL_VERSION} (${CURL_LIBRARIES})")
    message(STATUS "CURL_FOUND:        ${CURL_FOUND}")
    message(STATUS "CURL_VERSION:      ${CURL_VERSION}")
    message(STATUS "CURL_VERSION_STRING: ${CURL_VERSION_STRING}")
    message(STATUS "CURL_INCLUDE_DIRS: ${CURL_INCLUDE_DIRS}")

    if(CURL_INCLUDE_DIRS)
        file(STRINGS "${CURL_INCLUDE_DIRS}/curl/curl.h" _curl_version_str
             REGEX "^#define[\t ]+LIBCURL_VERSION[\t ]+\".*\"")
        string(REGEX REPLACE ".*\"(.*)\"" "\\1" CURL_VERSION_FROM_HEADER "${_curl_version_str}")
        message(STATUS "libcurl version from curl.h: ${CURL_VERSION_FROM_HEADER}")
    endif()
else()
    message(STATUS "No suitable libcurl ≥ 8.12.1 found in default paths ...")
endif()

add_executable(${PROJECT_NAME}
    np_curl_test.cc
)

if(CURL_FOUND)
   target_compile_definitions( ${name} PRIVATE WITH_CURL )
   target_link_libraries(${name} PRIVATE CURL::libcurl)
endif()


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../..)


install(TARGETS ${name} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET ${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Final binary → ${CMAKE_INSTALL_PREFIX}/bin/${name}"
    COMMAND ${CMAKE_COMMAND} -E echo "   → run: cmake --install ."
)


