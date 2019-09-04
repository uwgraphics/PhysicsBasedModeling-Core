cmake_minimum_required(VERSION 2.8.9)
project(PhysBAM_Library)

set(Options_DIR ./cmake)
find_package(Options)

# Set a default build type if none was specified
set(default_build_type "Release")
message("build type : ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_definitions(-DNDEBUG)
endif()

if(${compile_id_types_as_int})
  add_definitions(-DCOMPILE_ID_TYPES_AS_INT)
endif()
if(${compile_without_dyadic_support})
  add_definitions(-DCOMPILE_WITHOUT_DYADIC_SUPPORT)
endif()
if(${compile_without_rle_support})
  add_definitions(-DCOMPILE_WITHOUT_RLE_SUPPORT)
endif()
if(${compile_without_zlib_support})
  add_definitions(-DCOMPILE_WITHOUT_ZLIB_SUPPORT)
endif()
if(${use_pthreads})
  add_definitions(-DUSE_PTHREADS)
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wno-unused-local-typedef -std=c++03")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -WX")
else() #("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-but-set-variable -std=gnu++03")
endif()

set(PublicLibraryPath "Public_Library")
#set(CommonLibraryPath "Common_Libraries")
include_directories(${PublicLibraryPath})
#include_directories(${CommonLibraryPath})

file(GLOB SUBDIRS ${PublicLibraryPath}/*/)

foreach(subdir ${SUBDIRS})
  get_filename_component(subdirName ${subdir} NAME)
  if(${subdirName} STREQUAL "PhysBAM_OpenGL")
    if(${use_opengl})
      file(GLOB_RECURSE PUBLIC_SRC "${subdir}/*.cpp" ${PUBLIC_SRC})
    else()
      message("excluded ${subdir}")
    endif()
  elseif(${subdirName} STREQUAL "PhysBAM_Rendering")
    if(${use_rendering})
      file(GLOB_RECURSE PUBLIC_SRC "${subdir}/*.cpp" ${PUBLIC_SRC})
    else()
      message("excluded ${subdir}")
    endif()
  else()
    file(GLOB_RECURSE PUBLIC_SRC "${subdir}/*.cpp" ${PUBLIC_SRC})
  endif()
endforeach()


# file(GLOB_RECURSE PUBLIC_SRC "Public_Library/*.cpp")
#file(GLOB_RECURSE COMMON_SRC "Common_Libraries/*.cpp")
add_library(Public_Library STATIC  ${PUBLIC_SRC})
set_property(TARGET Public_Library PROPERTY CXX_STANDARD 11)
#add_library(Common_Library STATIC  ${COMMON_SRC})
