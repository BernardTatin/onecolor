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
// Original code (with an addition of a printf) from The Little Body found at:
//      https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/5

#include <IL/il.h>
#include <GL/glut.h>
#include <math.h>


#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

int nFrames = 0;


static int window;
static int menu_id;
static int submenu_id;
static int value = 2;

typedef enum {
    OR_Landscape,           // width > height, ratio > 1.0
    OR_Square,              // width = height, ratio = 1.0
    OR_Portrait             // width < height, ratio < 1.0
}          TEOrientation;

typedef struct {
    int           width;    // real image dimension
    int           height;
    float         ratio;    // width / height
    TEOrientation orientation;
}          TSImage;

TSImage image_dims;

void menuFunc0(int num) {
    value = num;

    glutPostRedisplay();
}

void menuFunc1(int num) {
    if (num == 0) {
        glutDestroyWindow(window);
        exit(0);
    } else {
        value = num;
    }

    glutPostRedisplay();
}

void createMenu(void) {
    submenu_id = glutCreateMenu(menuFunc0);
    glutAddMenuEntry("submenu1", 2);
    glutAddMenuEntry("submenu2", 3);
    glutAddMenuEntry("submenu3", 4);
    glutAddMenuEntry("submenu4", 5);

    menu_id = glutCreateMenu(menuFunc1);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


static inline void map_tex_point(const float s, const float t,
                                 const int x, const int y) {
    glTexCoord2f(s, t);
    glVertex2i(x, y);
}

static inline void map_tex_square(const float delta_x, const float delta_y,
                                  const int x1, const int y1,
                                  const int x2, const int y2) {
    map_tex_point(0.0f - delta_x, 0.0f - delta_y,
                  x1, y1);
    map_tex_point(1.0f + delta_x, 0.0f - delta_y,
                  x2, y1);
    map_tex_point(1.0f + delta_x, 1.0f + delta_y,
                  x2, y2);
    map_tex_point(0.0f - delta_x, 1.0f + delta_y,
                  x1, y2);
}

static inline float compute_delta(const int dim) {
    const float f_dim = (float) dim;
    if (dim > 128) {
        return 24.0f / f_dim;
    } else {
        return 0.0f;
    }
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void displayFunc() {
    int   max_dim = width;
    int   min_dim = width;
    float delta_x, delta_y;
    float w_dim, h_dim;

    if (height > max_dim) {
        max_dim = height;
    } else if (height < min_dim) {
        min_dim = height;
    } else {
    }

    delta_x = compute_delta(width);
    delta_y = compute_delta(height);

    w_dim = (float) width;
    h_dim = roundf((float) width / image_dims.ratio);
    if (h_dim > (float) height) {
        h_dim = (float) height;
        w_dim = roundf(h_dim * image_dims.ratio);
    }
    fprintf(stdout, "%-10s: x2 %4d y2 %4d r %5.3f -> %5.3f\n",
            "landscape", (int) w_dim, (int) h_dim, image_dims.ratio, w_dim / h_dim);

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Operate on model-view matrix
    glMatrixMode(GL_MODELVIEW);

    /* Draw a fullscreen mapped quad */
    glBegin(GL_QUADS);
    {
        map_tex_square(delta_x, delta_y,
                       0, 0,
                       (int) w_dim, (int) h_dim);
    }
    glEnd();

    glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeFunc(GLsizei newwidth, GLsizei newheight) {

    //printf("reshape(%d, %d) \n", newwidth, newheight);

    // Set the viewport to cover the new window
    glViewport(0, 0, width = newwidth, height = newheight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}


/* Initialize OpenGL Graphics */
void initGL(int w, int h) {
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

/* Load an image using DevIL and return the devIL handle (-1 if failure) */
ILboolean LoadImage(char *filename, ILuint *image) {
    ILboolean success;

    ilGenImages(1, image);    /* Generation of one image name */
    ilBindImage(*image);        /* Binding of image name */


    /* Loading of the image filename by DevIL */
    success = ilLoadImage(filename);
    if (success) {
        /* Convert every colour component into unsigned byte */
        /* You can replace IL_RGB with IL_RGBA if your image contains alpha channel */

        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if (!success) {
            return IL_FALSE;
        }
    } else {
        return IL_FALSE;
    }

    image_dims.width  = ilGetInteger(IL_IMAGE_WIDTH);
    image_dims.height = ilGetInteger(IL_IMAGE_HEIGHT);
    image_dims.ratio  = (float) image_dims.width / (float) image_dims.height;
    if (image_dims.width < image_dims.height) {
        image_dims.orientation = OR_Portrait;
    } else if (image_dims.height == image_dims.width) {
        image_dims.orientation = OR_Square;
        image_dims.ratio       = 1.0f;
    } else {
        image_dims.orientation = OR_Landscape;
    }
    return IL_TRUE;
}

int main(int argc, char **argv) {

    GLuint texid;
    ILuint image;

    if (argc < 2) {
        printf("%s image1.[jpg,bmp,tga,...] \n", argv[0]);
        return EXIT_SUCCESS;
    }

    /* GLUT init */
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height

    window = glutCreateWindow(argv[0]);      // Create window with the name of the executable

    createMenu();

    glutDisplayFunc(displayFunc);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshapeFunc);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    /* Initialization of DevIL */
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
        printf("wrong DevIL version \n");
        return EXIT_FAILURE;
    }
    ilInit();


    /* load the file picture with DevIL */
    if (!LoadImage(argv[1], &image)) {
        printf("Can't load picture file %s by DevIL \n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("\nImage bits/pix: %d, width: %d, height: %d\n",
           ilGetInteger(IL_IMAGE_BPP),
           ilGetInteger(IL_IMAGE_WIDTH),
           ilGetInteger(IL_IMAGE_HEIGHT));
    /* OpenGL texture binding of the image loaded by DevIL  */
    glGenTextures(1, &texid); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D,
                  texid); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for minifying filter */
    /*
     * <PLAY>
     * playing with texture parameters
     */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_BORDER);
    /* gives some color to the border */
    float borderColor[] = {
            0.6f, 0.3f, 0.4f, 1.0f
    };
    glTexParameterfv(GL_TEXTURE_2D,
                     GL_TEXTURE_BORDER_COLOR,
                     borderColor);
    /*
     * </PLAY>
     */
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 ilGetInteger(IL_IMAGE_BPP),
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT),
                 1,
                 ilGetInteger(IL_IMAGE_FORMAT),
                 GL_UNSIGNED_BYTE,
                 ilGetData()); /* Texture specification */

    /* Main loop */
    glutMainLoop();

    /* Delete used resources and quit */
    ilDeleteImages(1,
                   &image); /* Because we have already copied image data into texture data we can release memory used by image. */
    glDeleteTextures(1, &texid);

    return EXIT_SUCCESS;
}
