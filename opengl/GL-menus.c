//
// Created by bernard on 08/04/2022.
//


#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <IL/il.h>
#if defined(WITH_GLFW)
#include <GLFW/glfw3.h>
#else
#endif
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-menus.h"
#include "GL-filters.h"

static void exec_option(const Menu_Values option) {
    bool redraw = true;
    switch (option) {
        case Menu_BW_Normal1:
            filter_bw_normal1();
            break;
        case Menu_BW_Normal2:
            filter_bw_normal2();
            break;
        case Menu_BW_Normal3:
            filter_bw_normal3();
            break;
        case Menu_BW_Hard1:
            filter_bw_hard_black1();
            break;
        case Menu_BW_Hard2:
            filter_bw_hard_black2();
            break;
        case Menu_BW_Hard_Red:
            filter_bw_hard_red();
            break;
        case Menu_BW_Hard_Green:
            filter_bw_hard_green();
            break;
        case Menu_BW_Hard_Blue:
            filter_bw_hard_blue();
            break;
        case Menu_BW_Average:
            filter_average();
            break;
        case Menu_Quit:
#if !defined(WITH_GLFW)
            glutDestroyWindow(mainWindow.window);
            exit(0);
#else
            glfwSetWindowShouldClose(mainWindow.window, GL_TRUE);
            break;
#endif
        case Menu_Clear:
            memcpy(mainImage.screen_pixels,
                   mainImage.original_pixels,
                   mainImage.number_of_pixels * sizeof(RGBA));
            glutPostRedisplay();
            break;
        default:
            fprintf(stderr, "Unknown option %d\n", (int)option);
            redraw = false;
            break;
    }
#if !defined(WITH_GLFW)
    if (redraw) {
        glutPostRedisplay();
    }
#endif
}

static void menuBlackAndWhite(int num) {
    exec_option((Menu_Values)num);
}

static void menuMain(int num) {
    exec_option((Menu_Values)num);
}

static void exec_key(const int key, const int mods) {
    switch (key) {
        case 'c':
            exec_option(Menu_Clear);
            break;
        case 27:
        case 'q':
            exec_option(Menu_Quit);
            break;
        case 'r':
        case 'R':
            exec_option(Menu_BW_Hard_Red);
            break;
        case 'g':
        case 'G':
            exec_option(Menu_BW_Hard_Green);
            break;
        case 'b':
        case 'B':
            exec_option(Menu_BW_Hard_Blue);
            break;
        default:
            break;
    }
}

#if defined(WITH_GLFW)
void on_key(GLFWwindow* window, int iKey, int scancode, int action, int mods) {
    int key = 0;
    if (action == GLFW_PRESS) {
        fprintf(stdout, "key pressed %c (%d) mods %04x key %c (%d)\n",
                iKey, (int) iKey, mods, key, key);
        const char* keyName = glfwGetKeyName(iKey, 0);
        if (keyName != NULL && *(keyName + 1) == 0) {
            key = *keyName;
        } else {
            switch (iKey) {
                case GLFW_KEY_ESCAPE:
                    key = 27;
                    break;
                case GLFW_KEY_ENTER:
                    key = 13;
                    break;
                default:
                    key = 1;
                    break;
            }
        }
        fprintf(stdout, "key pressed %c (%d) mods %04x key %c (%d)\n",
                iKey, (int) iKey, mods, key, key);
        exec_key(key, mods);
        fprintf(stdout, "key pressed %c (%d) mods %04x key %c (%d)\n",
                iKey, (int) iKey, mods, key, key);
    }
}
#else
void on_key(unsigned char key, int x, int y) {
        exec_key(key, 0);
}
#endif

void createMenu(void) {
    mainWindow.submenu_id = glutCreateMenu(menuBlackAndWhite);
    glutAddMenuEntry("Normal 1", Menu_BW_Normal1);
    glutAddMenuEntry("Normal 2", Menu_BW_Normal2);
    glutAddMenuEntry("Normal 3", Menu_BW_Normal3);
    glutAddMenuEntry("Average", Menu_BW_Average);
    glutAddMenuEntry("Hard 1", Menu_BW_Hard1);
    glutAddMenuEntry("Hard 2", Menu_BW_Hard2);
    glutAddMenuEntry("Hard Red :r", Menu_BW_Hard_Red);
    glutAddMenuEntry("Hard Green :g", Menu_BW_Hard_Green);
    glutAddMenuEntry("Hard Blue :b", Menu_BW_Hard_Blue);
    glutAddMenuEntry("Suppress saturation", Menu_BW_No_Saturation);

    mainWindow.menu_id = glutCreateMenu(menuMain);
    glutAddMenuEntry("Clear :c", Menu_Clear);
    glutAddSubMenu("Black and White", mainWindow.submenu_id);
    glutAddMenuEntry("Quit :q", Menu_Quit);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
