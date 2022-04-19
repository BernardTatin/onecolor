cmake_minimum_required(VERSION 3.18)
project(one-color C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

UNSET(CMAKE_C_FLAGS CACHE)
SET(CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)

find_package(PkgConfig)


#
# evas version
#
pkg_search_module(EVAS required ecore-evas evas  ecore eina ecore-file efl)
pkg_search_module(IL required IL)


add_executable(one-color-evas
        evas/one-color-evas.c evas/evas-configuration.c evas/evas-configuration.h DevIL/dev-IL-tools.c DevIL/dev-IL-tools.h)
target_link_libraries(one-color-evas
        ${EVAS_LIBRARIES}
        ${IL_LIBRARIES})
target_include_directories(one-color-evas PUBLIC
        evas
        DevIL
        ${EVAS_INCLUDE_DIRS}
        ${IL_INCLUDE_DIRS})

#
# openGL version
#
pkg_search_module(GL required opengl )
add_executable(one-color-GL
        opengl/one-color-GL.c
        opengl/GL-Configuration.h
        opengl/GL-menus.c
        opengl/GL-menus.h
        opengl/GL-filters.c
        opengl/GL-filters.h
        opengl/GL_filter_definitions.c DevIL/dev-IL-tools.c DevIL/dev-IL-tools.h)
target_link_libraries(one-color-GL m glut ${GL_LIBRARIES}  ${IL_LIBRARIES} )
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
target_include_directories(one-color PUBLIC image-lib configuration)
