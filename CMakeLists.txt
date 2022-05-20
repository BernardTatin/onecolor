cmake_minimum_required(VERSION 3.18)
project(one-color C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

UNSET(CMAKE_C_FLAGS CACHE)
SET(CMAKE_C_FLAGS "-Wall -Wextra -pedantic" CACHE STRING "" FORCE)

find_package(PkgConfig)


pkg_search_module(IL required IL)
pkg_search_module(GLFW required glfw3)
pkg_search_module(GL required opengl)

#
# one-color-nuke, current version
#
add_executable(one-color-nuke
        Nuklear/one-color-nuke.c
        Nuklear/ocn-configuration.c Nuklear/ocn-configuration.h
        Nuklear/Nuklear-src/nuklear.h
        Nuklear/Nuklear-src/full-nuklear.c
        Nuklear/Nuklear-src/nuklear_glfw_gl3.h
        Nuklear/Nuklear-src/nuklear-config.h
        DevIL/dev-IL-tools.c DevIL/dev-IL-tools.h
        tools/file-tools.c tools/file-tools.h
        image-library/basic-data.c image-library/basic-data.h
        image-library/colors.c image-library/colors.h
        filtering/filtering.c filtering/filtering.h
        tools/file-data.c tools/file-data.h
        Nuklear/ocn-glfw3.c Nuklear/ocn-glfw3.h
        Nuklear/main-dialog.c Nuklear/main-dialog.h
        Nuklear/picture-window.c
        opengl/image-tools.c opengl/image-tools.h
        image-library/basic-geometry.c image-library/basic-geometry.h
        image-library/basic-types.h Nuklear/nk_tools.h)
target_link_libraries(one-color-nuke m glut ${GLFW_LIBRARIES} ${IL_LIBRARIES} GL m GLU GLEW)
target_include_directories(one-color-nuke PUBLIC
        filtering
        DevIL
        tools
        image-library
        Nuklear
        Nuklear/Nuklear-src
        ${IL_INCLUDE_DIRS})
target_compile_definitions(one-color-nuke PUBLIC WITH_NUKE)


#
# openGL version
#
add_executable(one-color-GL
        opengl/one-color-GL.c
        opengl/GL-Configuration.h
        opengl/GL-menus.c opengl/GL-menus.h
        filtering/GL-filters.c filtering/GL-filters.h
        opengl/GL_filter_definitions.c
        DevIL/dev-IL-tools.c DevIL/dev-IL-tools.h
        tools/file-tools.c tools/file-tools.h
        image-library/basic-data.c image-library/basic-data.h
        image-library/colors.c image-library/colors.h
        filtering/filtering.c filtering/filtering.h
        tools/file-data.c tools/file-data.h
        opengl/image-tools.c opengl/image-tools.h image-library/basic-geometry.c image-library/basic-geometry.h image-library/basic-types.h)
target_link_libraries(one-color-GL m glut ${GL_LIBRARIES} ${IL_LIBRARIES})
target_include_directories(one-color-GL PUBLIC
        filtering
        opengl
        DevIL
        image-library
        tools
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
        filtering/filters.h
        filtering/filters.c
        old-image-lib/image-files.c
        old-image-lib/image-files.h
        old-image-lib/color-tools.h
        old-image-lib/color-data.h
        filtering/hsv-filter.c
        filtering/hsv-filter.h
        image-library/colors.c image-library/colors.h
        configuration/main-configuration.h
        configuration/main-configuration.c)
target_link_libraries(one-color jpeg m)
target_include_directories(one-color PUBLIC
        filtering
        image-library
        old-image-lib
        configuration)
