//
// Created by bernard on 29/03/2022.
//

#include <stdbool.h>

#include "color-data.h"
#include "filters.h"
#include "hsv-filter.h"
#include "main-configuration.h"

const float hsv_Red      =   0.0f;
const float hsv_Green    = 120.0f;
const float hsv_Blue     = 240.0f;
const float hsv_Yellow   =  60.0f;

const float default_HSV_delta = 30.0f;

Global_Configuration global_configuration = {
    .verbose = false,
    .type = Filter_Grey,
    .delta = default_HSV_delta,
    .hue = hsv_Red,
};
