cmake_minimum_required(VERSION 3.17.0)
project(curser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES "src/*")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR msg)
include(CPack)
