//
// Created by bernard on 08/04/2022.
//


#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-menus.h"
#include "GL-filters.h"

static void menuBlackAndWhite(int num) {
    Menu_Values menu_option = (Menu_Values)num;
    mainWindow.value = num;
    switch (menu_option) {
        case Menu_BW_Normal1:
            filter_bw_normal1();
            break;
        case Menu_BW_Normal2:
            filter_bw_normal2();
            break;
        case Menu_BW_Normal3:
            filter_bw_normal3();
            break;
        case Menu_BW_Average:
            filter_average();
            break;
        default:
            fprintf(stderr, "Unknown B&W filter\n");
            break;
    }
    glutPostRedisplay();
    fprintf(stdout, "Selected menu: %d\n", num);
}

static void menuMain(int num) {
    Menu_Values menu_option = (Menu_Values)num;
    mainWindow.value = num;
    switch (menu_option) {
        case Menu_Quit:
            glutDestroyWindow(mainWindow.window);
            exit(0);
            break;
        case Menu_Clear:
            memcpy(mainImage.screen_pixels,
                   mainImage.original_pixels,
                   mainImage.number_of_pixels * sizeof(RGBA));
            glutPostRedisplay();
            break;
        default:
            fprintf(stderr, "Bad menu choice\n");
            break;
    }
}

void createMenu(void) {
    mainWindow.submenu_id = glutCreateMenu(menuBlackAndWhite);
    glutAddMenuEntry("Normal 1", Menu_BW_Normal1);
    glutAddMenuEntry("Normal 2", Menu_BW_Normal2);
    glutAddMenuEntry("Normal 3", Menu_BW_Normal3);
    glutAddMenuEntry("Average", Menu_BW_Average);
    glutAddMenuEntry("Luminance", Menu_BW_Luminance);
    glutAddMenuEntry("Suppress saturation", Menu_BW_No_Saturation);

    mainWindow.menu_id = glutCreateMenu(menuMain);
    glutAddMenuEntry("Clear", Menu_Clear);
    glutAddSubMenu("Black and White", mainWindow.submenu_id);
    glutAddMenuEntry("Quit", Menu_Quit);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
