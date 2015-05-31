cmake_minimum_required(VERSION 2.8)
project(tmxparser)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("Configuring tmxparser version ${VERSION}")
configure_file(
  "${PROJECT_SOURCE_DIR}/src/Tmx.h.in"
  "${PROJECT_BINARY_DIR}/Tmx.h"
  )

option(USE_MINIZ "Use miniz.c instead of zlib" OFF)

if (USE_MINIZ)
    add_definitions(-DUSE_MINIZ)
endif (USE_MINIZ)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h
                          ${PROJECT_BINARY_DIR}/Tmx.h)

if (USE_MINIZ)
    set(SOURCES ${SOURCES} ${PROJECT_SOURCE_DIR}/src/miniz.c)
endif (USE_MINIZ)

find_package(TinyXML2)

if (NOT USE_MINIZ)
    find_package(ZLIB)
endif (NOT USE_MINIZ)

set(LIB_CFLAGS "-pedantic -Wall -Werror=strict-prototypes -Werror=old-style-definition -Werror=missing-prototypes")

if (NOT USE_MINIZ)
    list(APPEND ${LIB_CFLAGS} "-Werror")
endif (NOT USE_MINIZ)

set(EXAMPLE_CFLAGS "-pedantic -Werror -Wall")
#include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(tmxparser_static STATIC ${SOURCES} ${HEADERS})
set_target_properties(tmxparser_static PROPERTIES
  OUTPUT_NAME tmxparser
  COMPILE_FLAGS ${LIB_CFLAGS})

add_library(tmxparser SHARED ${SOURCES} ${HEADERS})
set_target_properties(tmxparser PROPERTIES
  SOVERSION ${VERSION_MAJOR}
  VERSION ${VERSION}
  COMPILE_FLAGS ${LIB_CFLAGS})

target_link_libraries(tmxparser ${TINYXML2_LIBRARIES})
include_directories(${TINYXML2_INCLUDE_DIR})

if (NOT USE_MINIZ)
    target_link_libraries(tmxparser ${ZLIB_LIBRARIES})
    include_directories(${ZLIB_INCLUDE_DIRS})
endif (NOT USE_MINIZ)

add_executable(test test/test.cpp)
set_target_properties(test PROPERTIES
  COMPILE_FLAGS ${EXAMPLE_CFLAGS})
target_link_libraries(test tmxparser ${TINYXML2_LIBRARIES})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

install(FILES ${HEADERS} DESTINATION include/tmxparser)
install(TARGETS tmxparser tmxparser_static DESTINATION lib)

configure_file(src/tmxparser.pc.in tmxparser.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tmxparser.pc DESTINATION lib/pkgconfig)
