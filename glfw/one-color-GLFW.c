//
// Created by bernard on 06/04/2022.
//
// Code heavily copied from The Little Body at:
//      https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/5

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#if defined(WITH_GLFW)
#include <GLFW/glfw3.h>
#else
#endif
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-menus.h"
#include "DevIL-Tools.h"

GLWindow mainWindow = {
    .width = DEFAULT_WIDTH,
    .height = DEFAULT_HEIGHT,
    .value = 2
};
GLImage mainImage;


static inline void quad_vertex(const int tx, const int ty,
                               const int vx, const int vy) {
    glTexCoord2i(tx, ty);
    glVertex2i(vx, vy);
}

static inline void unit_quad(void) {
    int width = mainWindow.width;
    int height = mainWindow.height;
    int left = 0;
    int top = 0;
    float nh = (float)height;
    float nw = mainImage.ratio * (float)height;
    if (nw > (float)width) {
        float fTop;
        float r = (float)width / nw;
        nh = roundf(nh * r);
        nw = (float)width;
        fTop = roundf(0.5f * ((float)mainWindow.height - nh));
        top = (int)fTop;
    } else {
        float fLeft;
        nw = roundf(nw);
        fLeft = roundf(0.5f * ((float)mainWindow.width - nw));
        left = (int)fLeft;
    }
    width = (int)nw + left;
    height = (int)nh + top;

    quad_vertex(0, 0, left, top);
    quad_vertex(0, 1, left, height);
    quad_vertex(1, 1, width, height);
    quad_vertex(1, 0, width, top);
}
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
static void displayFunc() {
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Operate on model-view matrix
    glMatrixMode(GL_MODELVIEW);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 mainImage.byte_per_pixel,
                 mainImage.width,
                 mainImage.height,
                 0,
                 mainImage.format,
                 GL_UNSIGNED_BYTE,
                 mainImage.screen_pixels); /* Texture specification */
    /* Draw a full screen mapped quad */
    glBegin(GL_QUADS);
    unit_quad();
    glEnd();


#if !defined(WITH_GLFW)
    glutSwapBuffers();
#endif
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
static void reshapeFunc(GLsizei new_width, GLsizei new_height) {

    // printf("reshape(%d, %d) ", new_width, new_height );

    mainWindow.width = new_width;
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

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
    fprintf(stderr, "GLFW error: %s\n",
        description);
}

int main(int argc, char **argv) {
    GLuint texID;

#if defined(WITH_GLFW)
    fprintf(stdout, "With GLFW\n");
#endif
    if (argc != 2) {
        fprintf(stderr,"%s image1.[jpg,bmp,tga,...]\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mainWindow.window = glfwCreateWindow(640, 480, argv[1], NULL, NULL);
    if (!mainWindow.window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(mainWindow.window);
    glfwSetKeyCallback(mainWindow.window, on_key);

    // createMenu();

    // glutDisplayFunc(displayFunc);       // Register callback handler for window re-paint event
    // glutReshapeFunc(reshapeFunc);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    initGL(mainWindow.width, mainWindow.height);

    /* Initialization of DevIL */
    if (!DevIL_init()) {
        exit(EXIT_FAILURE);
    }

    /* load the file picture with DevIL */
    if (!LoadImage(&mainImage, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "\nImage bits/pix: %d, width: %d, height: %d, format: %d\n",
            mainImage.byte_per_pixel,
            mainImage.width,
            mainImage.height,
            mainImage.format);
    /* OpenGL 2D generic init */
    initGL(mainWindow.width, mainWindow.height);
    /* OpenGL texture binding of the mainImage loaded by DevIL  */
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
                 mainImage.byte_per_pixel,
                 mainImage.width,
                 mainImage.height,
                 0,
                 mainImage.format,
                 GL_UNSIGNED_BYTE,
                 mainImage.screen_pixels); /* Texture specification */

    {
        u8 *fgl_version = glGetString(GL_VERSION);

        if (fgl_version != NULL) {
            fprintf(stdout, "Current Open GL version: %s (%s)\n",
                    gl_version, fgl_version);
        } else {
            fprintf(stdout, "Current Open GL version: %s (%s)\n",
                    gl_version, "????");
        }
    }
    /* Main loop */
//    glutMainLoop();
    while (!glfwWindowShouldClose(mainWindow.window)) {
        int width, height;
        glfwGetFramebufferSize(mainWindow.window, &width, &height);
        displayFunc();
        glfwSwapBuffers(mainWindow.window);
        glfwPollEvents();
    }
    /* Delete used resources and quit */
    /* Because we have already copied mainImage data into texture data we can release memory used by mainImage. */
    ilDeleteImages(1, &mainImage.image_name);
    glDeleteTextures(1, &texID);
    glfwDestroyWindow(mainWindow.window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
