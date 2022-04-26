//
// Created by bernard on 25/04/22.
//

#ifndef ONE_COLOR_MAIN_DIALOG_H
#define ONE_COLOR_MAIN_DIALOG_H

#include "ocn-configuration.h"
#include "basic-geometry.h"

#define MAIN_DIALOG_WIDTH   230
#define MAIN_DIALOG_HEIGHT  WINDOW_HEIGHT
#define PIC_WINDOW_WIDTH    (WINDOW_WIDTH - MAIN_DIALOG_WIDTH)
#define PIC_WINDOW_HEIGHT   WINDOW_HEIGHT

bool show_main_dialog(OCDimensions win_dimensions);
bool show_picture_window(OCDimensions win_dimensions);

#endif //ONE_COLOR_MAIN_DIALOG_H
