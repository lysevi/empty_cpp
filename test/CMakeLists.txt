include_directories(..)

add_library(test_common STATIC test_common.cpp test_common.h)

MESSAGE(STATUS "Test: " ${name})

macro(TEST_CASE name src)
MESSAGE(STATUS " +" ${name})
add_executable(${name} ${src})
TARGET_LINK_LIBRARIES(${name} test_common library utils  ${Boost_LIBRARIES})
add_test(${name} ${name})
endmacro(TEST_CASE)



TEST_CASE(empty_test empty.cpp)
