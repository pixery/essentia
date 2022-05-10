cmake_minimum_required(VERSION 3.22.1)

project("essentia")

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "essentia/src/*.cpp")
file(GLOB_RECURSE C_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "essentia/src/*.c")

include_directories("essentia/src")
include_directories("essentia/src/essentia")
include_directories("essentia/src/essentia/scheduler")
include_directories("essentia/src/essentia/streaming")
include_directories("essentia/src/essentia/streaming/algorithms")
include_directories("essentia/src/essentia/utils")
include_directories("essentia/src/3rdparty")
include_directories("essentia/src/3rdparty/spline")
include_directories("essentia/src/3rdparty/nnls")
include_directories("essentia/src/3rdparty/kiss_fft130")
include_directories("essentia/src/3rdparty/cephes/bessel")
include_directories("/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3")

add_library(essentia SHARED ${C_SOURCES} ${CPP_SOURCES} EssentiaWrapper.cpp)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries(essentia log)
