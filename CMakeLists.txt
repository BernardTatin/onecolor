cmake_minimum_required(VERSION 3.18)
project(one-color C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

UNSET(CMAKE_C_FLAGS CACHE)
SET(CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)

find_package(PkgConfig)


pkg_search_module(IL required IL)
pkg_search_module(EVAS required ecore-evas evas  ecore eina ecore-file efl)
pkg_search_module(GLFW required  glfw3)
pkg_search_module(GL required opengl )

add_executable(one-color-nuke
        Nuklear/one-color-nuk.c
        Nuklear/Nuklear-src/nuklear.h
        Nuklear/Nuklear-src/full-nuklear.c
        Nuklear/Nuklear-src/nuklear_glfw_gl3.h
        Nuklear/Nuklear-src/nuklear-config.h
        image-library/colors.c
        image-library/colors.h image-library/filtering.c image-library/filtering.h)
target_link_libraries(one-color-nuke m  ${GLFW_LIBRARIES} ${IL_LIBRARIES}  GL m GLU GLEW)
target_include_directories(one-color-nuke PUBLIC
        DevIL
        tools
        image-library
        Nuklear
        Nuklear/Nuklear-src
        ${IL_INCLUDE_DIRS})
target_compile_definitions(one-color-nuke PUBLIC WITH_NUKE)

#
# evas version
#
add_executable(one-color-evas
        evas/one-color-evas.c
        evas/evas-configuration.c
        evas/evas-configuration.h
        DevIL/dev-IL-tools.c
        DevIL/dev-IL-tools.h
        evas/evas-scene.c
        evas/evas-scene.h
        evas/widgets.c
        evas/widgets.h
        tools/file-tools.c
        tools/file-tools.h
        evas/evas-tools.c
        evas/evas-tools.h
        image-library/basic-data.c
        image-library/basic-data.h
        image-library/debug.h
        image-library/colors.c
        image-library/colors.h image-library/filtering.c image-library/filtering.h)
target_link_libraries(one-color-evas
        ${EVAS_LIBRARIES}
        ${IL_LIBRARIES})
target_include_directories(one-color-evas PUBLIC
        evas
        DevIL
        tools
        image-library
        ${EVAS_INCLUDE_DIRS}
        ${IL_INCLUDE_DIRS})
target_compile_definitions(one-color-evas PUBLIC WITH_EVAS)

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
        opengl/GL_filter_definitions.c
        DevIL/dev-IL-tools.c
        DevIL/dev-IL-tools.h
        image-library/basic-data.c
        image-library/basic-data.h
        image-library/colors.c
        image-library/colors.h image-library/filtering.c image-library/filtering.h)
target_link_libraries(one-color-GL m glut ${GL_LIBRARIES}  ${IL_LIBRARIES} )
target_include_directories(one-color-GL PUBLIC
        opengl
        DevIL
        image-library
        )
target_compile_definitions(one-color-GL PUBLIC WITH_GL)

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
