cmake_minimum_required(VERSION 3.18)
project(one-color C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

UNSET(CMAKE_C_FLAGS CACHE)
SET(CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)

find_package(PkgConfig)

include_directories(image-lib configuration)

#
# evas version
#
pkg_search_module(EVAS required ecore-evas evas  ecore eina ecore-file efl)

add_executable(one-color-evas
        evas/images.c)
target_link_libraries(one-color-evas ${EVAS_LIBRARIES})
target_include_directories(one-color-evas PUBLIC ${EVAS_INCLUDE_DIRS} evas)

#
# openGL version
#
add_executable(one-color-GL
        opengl/one-color-GL.c
        opengl/GL-Configuration.h
        opengl/GL-menus.c
        opengl/GL-menus.h
        opengl/GL-filters.c
        opengl/GL-filters.h
        opengl/GL_filter_definitions.c)
target_link_libraries(one-color-GL m glut GL GLU IL)
target_include_directories(one-color-GL PUBLIC opengl)

#
# test openGL
#
add_executable(opengl-load-image
        opengl/opengl-load-image.c)
target_link_libraries(opengl-load-image m glut GL GLU IL)

#
# command line interface version
#
add_executable(one-color
        one-color/one-color.c
        image-lib/filters.h
        image-lib/filters.c
        image-lib/image-files.c
        image-lib/image-files.h
        image-lib/color-tools.h
        image-lib/color-data.h
        image-lib/hsv-filter.c
        image-lib/hsv-filter.h
        configuration/main-configuration.h
        configuration/main-configuration.c)
target_link_libraries(one-color jpeg m)
