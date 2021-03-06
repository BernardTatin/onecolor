/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2022.  Bernard Tatin                                         *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 ******************************************************************************/

//
// Created by bernard on 06/04/2022.
//
// Code heavily copied from The Little Body at:
//      https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/5

#include <math.h>
#include <stdbool.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "file-data.h"
#include "GL-Configuration.h"
#include "GL-menus.h"
#include "dev-IL-tools.h"
#include "basic-geometry.h"
#include "image-tools.h"

int nFrames = 0;

GLWindow mainWindow = {
        .width = DEFAULT_WIDTH,
        .height = DEFAULT_HEIGHT,
        .value = 2
};


static inline void quad_vertex(const int tx, const int ty,
                               const int vx, const int vy) {
    glTexCoord2i(tx, ty);
    glVertex2i(vx, vy);
}

static inline void unit_quad(void) {
    OCDimensions dimensions = {
            .width = mainWindow.width,
            .height = mainWindow.height
    };
    OCRectangle  rectangle;
    scale_image(dimensions, main_image.ratio, &rectangle);

    quad_vertex(0, 0, rectangle.left, rectangle.top);
    quad_vertex(0, 1, rectangle.left, rectangle.height);
    quad_vertex(1, 1, rectangle.width, rectangle.height);
    quad_vertex(1, 0, rectangle.width, rectangle.top);
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
static void displayFunc() {

    // printf("Frame %d ", ++nFrames);

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Operate on model-view matrix
    glMatrixMode(GL_MODELVIEW);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 main_image.byte_per_pixel,
                 main_image.width,
                 main_image.height,
                 0,
                 main_image.format,
                 GL_UNSIGNED_BYTE,
                 main_image.screen_pixels); /* Texture specification */
    /* Draw a full screen mapped quad */
    glBegin(GL_QUADS);
    unit_quad();
    glEnd();

    glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
static void reshapeFunc(GLsizei new_width, GLsizei new_height) {

    // printf("reshape(%d, %d) ", new_width, new_height );

    mainWindow.width  = new_width;
    mainWindow.height = new_height;
    // Set the viewport to cover the new window
    glViewport(0, 0, mainWindow.width, mainWindow.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, mainWindow.width, mainWindow.height, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}


/* Initialize OpenGL Graphics */
static void initGL(int w, int h) {
    glViewport(0, 0, w, h); // use a screen size of WIDTH x HEIGHT
    glEnable(GL_TEXTURE_2D);     // Enable 2D texturing

    glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
    glLoadIdentity();
    glOrtho(0.0, w, h, 0.0, 0.0, 100.0);

    glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}


int main(int argc, char **argv) {
    GLuint texID;

    if (!init_file_data(argc, argv)) {
        return EXIT_FAILURE;
    }

    /* GLUT init */
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(mainWindow.width, mainWindow.height);   // Set the window's initial width & height

    mainWindow.window = glutCreateWindow(argv[1]);      // Create window with the name of the executable

    createMenu();
    glutKeyboardFunc(on_key);
    glutSpecialFunc(on_special_keys);

    glutDisplayFunc(displayFunc);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshapeFunc);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    //    initGL(mainWindow.width, mainWindow.height);

    /* Initialization of DevIL */
    if (!init_DevIL()) {
        fprintf(stderr, "wrong DevIL version\n");
        return EXIT_FAILURE;
    }

    /* load the file picture with DevIL */
    if (!LoadImage(&main_image, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return EXIT_FAILURE;
    }
    /* OpenGL 2D generic init */
    initGL(mainWindow.width, mainWindow.height);
    /* OpenGL texture binding of the main_image loaded by DevIL  */
    glGenTextures(1, &texID); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D, texID); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 main_image.byte_per_pixel,
                 main_image.width,
                 main_image.height,
                 0,
                 main_image.format,
                 GL_UNSIGNED_BYTE,
                 main_image.screen_pixels); /* Texture specification */

    {
        const u8 *fgl_version = glGetString(GL_VERSION);

        if (fgl_version != NULL) {
            fprintf(stdout, "Current Open GL version: %s (%s)\n",
                    gl_version, fgl_version);
        } else {
            fprintf(stdout, "Current Open GL version: %s (%s)\n",
                    gl_version, "????");
        }
    }
    /* Main loop */
    glutMainLoop();

    /* Delete used resources and quit */
    /* Because we have already copied main_image data into texture data we can release memory used by main_image. */
    ilDeleteImages(1, &main_image.image_name);
    glDeleteTextures(1, &texID);

    return 0;
}
