cmake_minimum_required (VERSION 3.10)

project (ktest_radcli_integration_bin)

message("before: CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
set(CMAKE_LIBRARY_PATH "/usr/local/lib")
message("after: CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/user/home2")

unset(RADCLI_SEARCH_RESULT)
find_library(RADCLI_SEARCH_RESULT radcli REQUIRED)
message("RADCLI_SEARCH_RESULT: ${RADCLI_SEARCH_RESULT}")

#Set Clang compiler
#SET (CMAKE_C_COMPILER     clang)
#SET (CMAKE_CXX_COMPILER   clang++)

#Print the compiler
message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

message("CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

include(GNUInstallDirs)
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message("")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(CMAKE_BUILD_TYPE Debug)

add_library(ktest_freeradius_library SHARED kmain.cpp) 

add_executable (ktest_radcli_integration_bin kmain.cpp)
target_link_libraries(ktest_radcli_integration_bin radcli)

