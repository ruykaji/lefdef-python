cmake_minimum_required(VERSION 3.19)
project(lefdef LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/external/def/include
    ${CMAKE_SOURCE_DIR}/external/lef/include
    ${CMAKE_SOURCE_DIR}/src
)

find_library(DEF NAMES libdef.a PATHS ${CMAKE_SOURCE_DIR}/external/def/lib)
find_library(LEF NAMES liblef.a PATHS ${CMAKE_SOURCE_DIR}/external/lef/lib)

file(GLOB GLOBAL ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(test test.cpp ${GLOBAL})
target_link_libraries(test PRIVATE ${DEF} ${LEF})

add_library(lefdef SHARED ${GLOBAL})
target_link_libraries(lefdef PRIVATE ${DEF} ${LEF})
install(TARGETS lefdef DESTINATION ${CMAKE_SOURCE_DIR}/lefdef/lib/)