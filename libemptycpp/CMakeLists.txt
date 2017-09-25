include(GenerateExportHeader)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/config.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
INCLUDE_DIRECTORIES(${EMPTYCPP_INCLUDE_DIR})

FILE(GLOB GLOB_HDRS "*.h")
FILE(GLOB UTILS_HDRS "utils/*.h")
FILE(GLOB UTILSA_HDRS "utils/async/*.h")

FILE(GLOB GLOB_SRC "*.cpp")
FILE(GLOB UTILS_SRC "utils/*.cpp")
FILE(GLOB UTILSA_SRC "utils/async/*.cpp")

source_group(utils FILES ${UTILS_HDRS} ${UTILS_SRC})
source_group(utils\\async FILES ${UTILSA_HDRS} ${UTILSA_SRC})
source_group(interfaces FILES ${INTERFACES_HDRS} ${INTERFACES_SRC})

SET(SRC  ${GLOB_HDRS} ${GLOB_SRC} 
	 ${UTILS_HDRS}  ${UTILS_SRC} 
	 ${UTILSA_HDRS} ${UTILSA_SRC}
     ${INTERFACES_HDRS} ${INTERFACES_SRC})

SET(EMPTYCPP_LIBS ${Boost_LIBRARIES} emptycpp CACHE STRING "emptycpp libs.")

add_library(emptycpp SHARED ${SRC})
TARGET_LINK_LIBRARIES(emptycpp ${CMAKE_THREAD_LIBS_INIT})
cotire(emptycpp)

GENERATE_EXPORT_HEADER(emptycpp
    BASE_NAME emptycpp
    EXPORT_MACRO_NAME EXPORT
    EXPORT_FILE_NAME st_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)
