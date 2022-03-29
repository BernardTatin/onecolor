//
// Created by bernard on 25/03/2022.
//

#ifndef ONECOLOR_HSV_FILTER_H
#define ONECOLOR_HSV_FILTER_H

typedef struct {
    float h;
    float s;
    float v;
} HSV;

typedef struct {
    float h;
    float delta;
} HSVFilter;

extern const float default_HSV_delta;
extern HSVFilter main_HSV_filter;

extern const float hsv_Red;
extern const float hsv_Green;
extern const float hsv_Blue;
extern const float hsv_Yellow;

ImageLib_Error hsv_filter(
        const HSVFilter *filter,
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);

#endif //ONECOLOR_HSV_FILTER_H
