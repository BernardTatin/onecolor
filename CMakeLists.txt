cmake_minimum_required(VERSION 3.21)
project(onecolor C)

set(CMAKE_C_STANDARD 11)

add_executable(onecolor main.c filters.h filters.c image-files.c image-files.h color-tools.h color-data.h hsv-filter.c hsv-filter.h)
target_link_libraries(onecolor jpeg m)
