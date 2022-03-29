cmake_minimum_required(VERSION 3.21)
project(one-color C)

set(CMAKE_C_STANDARD 11)

include_directories(image-lib)
add_executable(one-color
        one-color/one-color.c
        image-lib/filters.h
        image-lib/filters.c
        image-lib/image-files.c
        image-lib/image-files.h
        image-lib/color-tools.h
        image-lib/color-data.h
        image-lib/hsv-filter.c
        image-lib/hsv-filter.h)
target_link_libraries(one-color jpeg m)
