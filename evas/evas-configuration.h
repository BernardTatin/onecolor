//
// Created by bernard on 19/04/22.
//

#ifndef ONE_COLOR_EVAS_CONFIGURATION_H
#define ONE_COLOR_EVAS_CONFIGURATION_H

extern const int default_width;
extern const int default_height;
extern const int dx;
extern const int dy;

extern char *program_name;
extern char *img_source;
extern char *img_base_source;
extern char *img_destination;

#include "basic-data.h"

typedef struct _MainData {
    Ecore_Evas *ecore_evas;
    Evas *evas;
    Evas_Object *image;
    Evas_Object *background;
    Evas_Object *txt_key_help;
    Evas_Object *txt_help;
} MainData;



extern MainData main_data;
extern TheImage main_image;

#endif //ONE_COLOR_EVAS_CONFIGURATION_H
