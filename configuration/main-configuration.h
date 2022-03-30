//
// Created by bernard on 29/03/2022.
//

#ifndef ONE_COLOR_MAIN_CONFIGURATION_H
#define ONE_COLOR_MAIN_CONFIGURATION_H

#include "hsv-filter.h"

extern const float hsv_Red;
extern const float hsv_Green;
extern const float hsv_Blue;
extern const float hsv_Yellow;

typedef enum {
    Filter_Grey,
    Filter_Red,
    Filter_Green,
    Filter_Blue,
    Filter_Yellow,
    Filter_Hue
} FilterType;

typedef struct {
    bool verbose;
    FilterType type;
    float delta;
    float hue;
} Global_Configuration;

extern Global_Configuration global_configuration;

#endif //ONE_COLOR_MAIN_CONFIGURATION_H
