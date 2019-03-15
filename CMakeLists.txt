cmake_minimum_required(VERSION 2.8.9)
project (HelloWorld)

include_directories(include)
aux_source_directory(src SRC_FILES)
add_executable(exec_test ${SRC_FILES})
