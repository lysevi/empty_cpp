INCLUDE_DIRECTORIES(${EMPTYCPP_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

MESSAGE(STATUS "Microbenchmarks")

FILE(GLOB HDRS "*.h")
FILE(GLOB SRC "*.cpp")

add_executable(microbenchmarks ${HDRS} ${SRC})
TARGET_LINK_LIBRARIES(microbenchmarks ${EMPTYCPP_LIBS} benchmark)
set_target_properties(microbenchmarks PROPERTIES FOLDER Benchmarks)

add_test(microbenchmarks ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/microbenchmarks) 
cotire(microbenchmarks)