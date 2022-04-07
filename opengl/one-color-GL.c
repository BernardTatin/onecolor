//
// Created by bernard on 06/04/2022.
//
// Code heavily copied from The Little Body at:
//      https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/5

#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"


int width = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

int nFrames = 0;


static GLWindow mainWindow = {
    .value = 2
};

void menuFunc0(int num) {
    mainWindow.value = num;

    glutPostRedisplay();
}

void menuFunc1(int num) {
    if (num == 0) {
        glutDestroyWindow(mainWindow.window);
        exit(0);
    } else {
        mainWindow.value = num;
    }

    glutPostRedisplay();
}

void createMenu(void) {
    mainWindow.submenu_id = glutCreateMenu(menuFunc0);
    glutAddMenuEntry("submenu1", 2);
    glutAddMenuEntry("submenu2", 3);
    glutAddMenuEntry("submenu3", 4);
    glutAddMenuEntry("submenu4", 5);

    mainWindow.menu_id = glutCreateMenu(menuFunc1);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", mainWindow.submenu_id);
    glutAddMenuEntry("Quit", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void displayFunc() {

    // printf("Frame %d ", ++nFrames);

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Operate on model-view matrix
    glMatrixMode(GL_MODELVIEW);

    /* Draw a full screen mapped quad */
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, 0);
    glTexCoord2i(0, 1);
    glVertex2i(0, height);
    glTexCoord2i(1, 1);
    glVertex2i(width, height);
    glTexCoord2i(1, 0);
    glVertex2i(width, 0);
    glEnd();

    glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeFunc(GLsizei new_width, GLsizei new_height) {

    // printf("reshape(%d, %d) ", new_width, new_height );

    // Set the viewport to cover the new window
    glViewport(0, 0, width = new_width, height = new_height);
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
ILuint LoadImage(char *filename) {
    ILuint image;
    ILboolean success;

    ilGenImages(1, &image);    /* Generation of one image name */
    ilBindImage(image);        /* Binding of image name */


    /* Loading of the image filename by DevIL */
    success = ilLoadImage(filename);
    if (success) {
        /* Convert every colour component into unsigned byte */
        /* You can replace IL_RGB with IL_RGBA if your image contains alpha channel */

        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if (!success) {
            return -1;
        }
    } else
        return -1;

    return image;
}

int main(int argc, char **argv) {

    GLuint texID;
    GLImage image;

    if (argc != 2) {
        fprintf(stderr,"%s image1.[jpg,bmp,tga,...]\n", argv[0] );
        return 0;
    }

    /* GLUT init */
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height

    mainWindow.window = glutCreateWindow(argv[1]);      // Create window with the name of the executable

    createMenu();

    glutDisplayFunc(displayFunc);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshapeFunc);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    /* Initialization of DevIL */
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
        fprintf(stderr, "wrong DevIL version\n");
        return -1;
    }
    ilInit();


    /* load the file picture with DevIL */
    image.image_name = LoadImage(argv[1]);
    if (image.image_name == -1) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return -1;
    }
    image.width = ilGetInteger(IL_IMAGE_WIDTH);
    image.height = ilGetInteger(IL_IMAGE_HEIGHT);
    image.byte_per_pixel = ilGetInteger(IL_IMAGE_BPP);
    image.format = ilGetInteger(IL_IMAGE_FORMAT);
    fprintf(stdout,"\nImage bits/pix: %d, width: %d, height: %d, format: %d\n",
           image.byte_per_pixel,
           image.width,
           image.height,
           image.format);
    /* OpenGL texture binding of the image loaded by DevIL  */
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
                 image.byte_per_pixel,
                 image.width,
                 image.height,
                 0,
                 image.format,
                 GL_UNSIGNED_BYTE,
                 ilGetData()); /* Texture specification */

    /* Main loop */
    glutMainLoop();

    /* Delete used resources and quit */
    /* Because we have already copied image data into texture data we can release memory used by image. */
    ilDeleteImages(1, &image.image_name);
    glDeleteTextures(1, &texID);

    return 0;
}
