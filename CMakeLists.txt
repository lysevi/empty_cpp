cmake_minimum_required (VERSION 3.1)
set(PROJECT "emptycpp")
project (${PROJECT} VERSION 0.0.1)

IF(NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE is not set, set to default = RELWITHDEBINFO")
    SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
ENDIF()

MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )


option(EMPTYCPP_ENABLE_TESTS "Enable testing." ON)
option(EMPTYCPP_ENABLE_DOUBLECHECKS "More checks in code." ON)
option(EMPTYCPP_ENABLE_BENCHMARKS "Enable benchmarks." ON)
option(EMPTYCPP_ASAN_UBSAN "Enable address & undefined behavior sanitizer for binary." OFF)
option(EMPTYCPP_MSAN "Enable memory sanitizer for binary." OFF)

if((EMPTYCPP_ASAN_UBSAN AND EMPTYCPP_MSAN))
  message(FATAL_ERROR "Sanitizers cannot be enabled simultaneously.")
endif()

MESSAGE(STATUS "Options: ")
MESSAGE(STATUS "EMPTYCPP_ENABLE_TESTS - " ${EMPTYCPP_ENABLE_TESTS})
MESSAGE(STATUS "EMPTYCPP_ENABLE_BENCHMARKS - " ${EMPTYCPP_ENABLE_BENCHMARKS})
MESSAGE(STATUS "EMPTYCPP_ENABLE_DOUBLECHECKS - " ${EMPTYCPP_ENABLE_DOUBLECHECKS})
MESSAGE(STATUS "EMPTYCPP_ASAN_UBSAN - " ${EMPTYCPP_ASAN_UBSAN})
MESSAGE(STATUS "EMPTYCPP_MSAN - " ${EMPTYCPP_MSAN})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/extern/cotire/CMake")

include(AddCXXCompilerFlag)
include(CompillerSettings)
include(cotire)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########## BOOST

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 


set(BOOST_DEP system filesystem)

IF(WIN32 AND MSVC)
  find_package(Boost 1.54.0 COMPONENTS ${BOOST_DEP} REQUIRED)
else()
  set(BOOST_DEP ${BOOST_DEP} program_options)
  find_package(Boost  REQUIRED ${BOOST_DEP})
ENDIF()

IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
else()
  MESSAGE(FATAL_ERROR "boost not found")
  EXIT()
ENDIF()


IF(EMPTYCPP_ENABLE_DOUBLECHECKS)
 add_definitions(-DDOUBLE_CHECKS)
ENDIF()

SET(EMPTYCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "emptycpp include dir.")
INCLUDE_DIRECTORIES(${EMPTYCPP_INCLUDE_DIR})
add_subdirectory (libemptycpp)

if(EMPTYCPP_ENABLE_TESTS)
   enable_testing()
endif(EMPTYCPP_ENABLE_TESTS)

if(EMPTYCPP_ENABLE_BENCHMARKS)
   set(BENCHMARK_ENABLE_TESTING OFF)
   add_subdirectory(extern/benchmark)
   include_directories(extern/benchmark/include)
   set_target_properties(benchmark PROPERTIES FOLDER Extern)
   add_subdirectory (microbenchmarks)
endif(EMPTYCPP_ENABLE_BENCHMARKS)

if(EMPTYCPP_ENABLE_TESTS)
   cmake_policy(SET CMP0048 OLD)
   include_directories(extern/Catch/include)
   add_subdirectory (unittests)
endif(EMPTYCPP_ENABLE_TESTS)


