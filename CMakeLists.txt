cmake_minimum_required (VERSION 3.1)
set(PROJECT "emptycpp")
project (${PROJECT} VERSION 0.0.1)

IF(NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE is not set, set to default = RELWITHDEBINFO")
    SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
ENDIF()

MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

if (NOT EXISTS conanbuildinfo.cmake)
  message(FATAL_ERROR "Conan needs to be executed: conan install <path_to_your_conanfile.txt>")
endif ()
 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cotire/CMake")

include(AddCXXCompilerFlag)
include(CompillerSettings)
include(cotire)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########## BOOST
IF(NOT HEADER_ONLY)
    list(FIND CONAN_DEFINES_BOOST "-DBOOST_USE_STATIC_LIBS" IS_STATIC)
    if(${IS_STATIC} GREATER -1)
        set(Boost_USE_STATIC_LIBS ON)
    else()
        set(Boost_USE_STATIC_LIBS OFF)
	endif()
endif()

add_definitions(-DBOOST_ASIO_NO_DEPRECATED)
find_package(Boost 1.69.0 COMPONENTS system date_time REQUIRED)

IF(Boost_FOUND)
else()	
  MESSAGE(FATAL_ERROR "boost not found")
  EXIT()
ENDIF()


IF(EMPTYCPP_ENABLE_DOUBLECHECKS)
 add_definitions(-DDOUBLE_CHECKS)
ENDIF()

SET(EMPTYCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
INCLUDE_DIRECTORIES(${EMPTYCPP_INCLUDE_DIR})

add_subdirectory (libemptycpp)

if(EMPTYCPP_ENABLE_TESTS)
   enable_testing()
endif(EMPTYCPP_ENABLE_TESTS)

if(EMPTYCPP_ENABLE_BENCHMARKS)
   add_definitions(-DEMPTYCPP_ENABLE_BENCHMARKS)
endif(EMPTYCPP_ENABLE_BENCHMARKS)

if(EMPTYCPP_ENABLE_TESTS)
   include_directories(extern/Catch2/single_include/catch2/)
   add_subdirectory (unittests)
endif(EMPTYCPP_ENABLE_TESTS)


