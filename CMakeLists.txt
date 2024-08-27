project(demo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2 -fPIC -fvisibility=hidden")

list(APPEND EXTRA_INCS "${PROJECT_SOURCE_DIR}/include")

list(APPEND EXTRA_INCS "${PROJECT_SOURCE_DIR}/include/curl")
list(APPEND EXTRA_INCS "${PROJECT_SOURCE_DIR}/include/hlog")
list(APPEND EXTRA_INCS "${PROJECT_SOURCE_DIR}/include/hpr")
list(APPEND EXTRA_INCS "${PROJECT_SOURCE_DIR}/include/libsafefunc")


list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/libs/x86/curl")
list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/libs/x86/hlog")
list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/libs/x86/hpr")
list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/libs/x86/openssl")
list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/libs/x86/libsafefunc")


aux_source_directory("${PROJECT_SOURCE_DIR}/src" MAIN_SRC)
add_executable(demo ${MAIN_SRC})

target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}")
target_include_directories(demo PUBLIC "${EXTRA_INCS}")
target_link_directories(demo    PUBLIC "${EXTRA_LIBS}")
target_link_libraries(demo PUBLIC hlog hpr safefunc dl z pthread curl nghttp2 ssl crypto)