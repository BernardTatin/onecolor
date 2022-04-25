//
// Created by bernard on 25/04/22.
//

#ifndef ONE_COLOR_MAIN_DIALOG_H
#define ONE_COLOR_MAIN_DIALOG_H

#include "ocn-configuration.h"

#define MAIN_DIALOG_WIDTH   230
#define MAIN_DIALOG_HEIGHT  WINDOW_HEIGHT
#define PIC_WINDOW_WIDTH    (WINDOW_WIDTH - MAIN_DIALOG_WIDTH)
#define PIC_WINDOW_HEIGHT   WINDOW_HEIGHT

bool create_main_dialog(void);
bool create_picture_window(void);

#endif //ONE_COLOR_MAIN_DIALOG_H
