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

typedef struct _MainData {
    Ecore_Evas *ecore_evas;
    Evas *evas;
    Evas_Object *image;
    Evas_Object *background;
    Evas_Object *txt_key_help;
    Evas_Object *txt_help;
} MainData;

typedef unsigned char u8;
typedef struct __attribute__((__packed__)) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct {
    float r;
    float g;
    float b;
} fRGB;

typedef struct {
    float h;
    float s;
    float v;
} HSV;

typedef struct {
    ILuint image_name;

    int width;
    int height;
    int number_of_pixels;

    int byte_per_pixel;
    int format;

    float ratio;

    RGBA *original_pixels;
    RGBA *screen_pixels;
    HSV *hsv;
    fRGB *rgb;
} EV_image;

extern MainData main_data;
extern EV_image main_image;

#endif //ONE_COLOR_EVAS_CONFIGURATION_H
