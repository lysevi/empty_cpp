INCLUDE_DIRECTORIES(${emptycpp_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

MESSAGE(STATUS "Unittests")

FILE(GLOB HDRS "*.h")
FILE(GLOB SRC "*.cpp")

add_executable(unittests ${HDRS} ${SRC})
TARGET_LINK_LIBRARIES(unittests ${Boost_LIBRARIES} ${EMPTYCPP_LIBS})

add_test(unittests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittests) 
set_target_properties(unittests PROPERTIES FOLDER Tests)
cotire(unittests)
target_compile_definitions(unittests PUBLIC  -DCATCH_CONFIG_ENABLE_BENCHMARKING)