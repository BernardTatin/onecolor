cmake_minimum_required(VERSION 3.21)
project(onecolor C)

set(CMAKE_C_STANDARD 11)

add_executable(onecolor
        onecolor/onecolor.c
        imglib/filters.h
        imglib/filters.c
        imglib/image-files.c
        imglib/image-files.h
        imglib/color-tools.h
        imglib/color-data.h
        imglib/hsv-filter.c
        imglib/hsv-filter.h)
target_link_libraries(onecolor jpeg m)
