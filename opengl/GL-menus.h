//
// Created by bernard on 08/04/2022.
//

#ifndef ONE_COLOR_GL_MENUS_H
#define ONE_COLOR_GL_MENUS_H

typedef enum {
    Menu_Quit,
    Menu_Clear,
    Menu_BW_Normal1,
    Menu_BW_Normal2,
    Menu_BW_Normal3,
    Menu_BW_Hard1,
    Menu_BW_Hard2,
    Menu_BW_Hard_Red,
    Menu_BW_Hard_Green,
    Menu_BW_Hard_Blue,
    Menu_BW_Average,
    Menu_BW_No_Saturation
} Menu_Values;

void createMenu(void);
#if defined(WITH_GLFW)
void on_key(GLFWwindow* window, int key, int scancode, int action, int mods);
#else
void on_key(unsigned char key, int x, int y);
#endif


#endif //ONE_COLOR_GL_MENUS_H
