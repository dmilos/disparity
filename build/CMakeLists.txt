cmake_minimum_required(VERSION 3.0)

set( PROJECT_EXE    DisparityExe   )
set( PROJECT_NAME   DisparityPrj   )

project( ${PROJECT_NAME} )


set( SOURCE_CPP  "../src/main.cpp" )
list( APPEND  SOURCE_CPP "../src/main.cpp" )
list( APPEND  SOURCE_CPP "../src/stereomatch.cpp" )
list( APPEND  SOURCE_CPP "../src/stereopatchmatch.cpp" )
list( APPEND  SOURCE_CPP "../src/stereopatchnormgraymatch.cpp" )
list( APPEND  SOURCE_CPP "../src/stereonormalmatch.cpp" )
list( APPEND  SOURCE_CPP "../src/stereomatchV1.cpp" )
list( APPEND  SOURCE_CPP "../src/stereomatchV2.cpp" )


list( APPEND  SOURCE_CPP "../src/square.cpp" )
list( APPEND  SOURCE_CPP "../src/compare.cpp" )
list( APPEND  SOURCE_CPP "../src/filter/bilateral.cpp" )

list( APPEND  SOURCE_CPP "../src/convolve/filter.cpp" )
list( APPEND  SOURCE_CPP "../src/convolve/lasagna.cpp" )
list( APPEND  SOURCE_CPP "../src/convolve/layer.cpp" )
list( APPEND  SOURCE_CPP "../src/convolve/stereoconvolvematch.cpp" )

list( APPEND  SOURCE_HPP "../src/filter/bilateral.hpp" )
list( APPEND  SOURCE_HPP "../src/stereomatchV1.hpp" )
list( APPEND  SOURCE_HPP "../src/stereomatchV2.hpp" )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(  ${PROJECT_EXE}  ${SOURCE_CPP}  ${SOURCE_HPP}  )

target_include_directories( ${PROJECT_EXE}  PUBLIC  "../src" )
target_include_directories( ${PROJECT_EXE}  PUBLIC  $ENV{COLOR_ROOT} )
target_include_directories( ${PROJECT_EXE}  PUBLIC  $ENV{MATH_ROOT} )
target_include_directories( ${PROJECT_EXE}  PUBLIC  $ENV{OPENCV__msvc__INCLUDE} )

set_property( TARGET ${PROJECT_EXE} PROPERTY CXX_STANDARD 17 )


target_link_libraries ( ${PROJECT_EXE}
    debug     $ENV{OPENCV__msvc_64_LIBFILE_DEBUG}
    optimized $ENV{OPENCV__msvc_64_LIBFILE_RELEASE}
 )

target_link_directories( ${PROJECT_EXE}
    PUBLIC $<$<CONFIG:DEBUG>:$ENV{OPENCV__msvc_64_LIBDIR_DEBUG}>
    PUBLIC $<$<CONFIG:RELEASE>:$ENV{OPENCV__msvc_64_LIBDIR_RELEASE}>
 )

set( OPENCV_BIN_DEBUG   $ENV{OPENCV__msvc_64_DLLDIR_DEBUG}   )
set( OPENCV_BIN_RELEASE $ENV{OPENCV__msvc_64_DLLDIR_RELEASE} )
configure_file( templatevcxproj.user.in ${PROJECT_EXE}.vcxproj.user   )

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_EXE} )