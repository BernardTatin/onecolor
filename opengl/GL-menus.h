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
    Menu_BW_Luminance,
    Menu_BW_Average,
    Menu_BW_No_Saturation
} Menu_Values;

void createMenu(void);

#endif //ONE_COLOR_GL_MENUS_H
