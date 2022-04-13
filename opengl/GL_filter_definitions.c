//
// Created by bernard on 12/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#if defined(WITH_GLFW)
#include <GLFW/glfw3.h>
#else
#endif
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-filters.h"

/*
 * Normal black and white
 */

GLPFilterBWNormal p_bw_normal1 = {
        .KlR = 0.299f,
        .KlG = 0.587f,
        .KlB = 0.114f
};
GLPFilterBWNormal p_bw_normal2 = {
        .KlR = 0.2126f,
        .KlG = 0.7152f,
        .KlB = 0.0722f
};
GLPFilterBWNormal p_bw_normal3 = {
        .KlR = 0.2627f,
        .KlG = 0.6780f,
        .KlB = 0.0593f
};

GLFilter bw_normal1 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};
GLFilter bw_normal2 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};
GLFilter bw_normal3 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};

/*
 * hard black and white
 */

GLPFilterBWHard p_bw_hard_average = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};

const float dark = 120.0f;
GLPFilterBWHard p_bw_hard_averageR = {
        .type = BWH_average,
        .darkR = dark,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_averageG = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = dark,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_averageB = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = dark,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_median = {
        .type = BWH_median,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};

GLFilter bw_hard_average = {
       .type = FT_BW_HARD,
       .filter_function = bw_hard_function,
       .parameters = &p_bw_hard_average
};
GLFilter bw_hard_averageR = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageR
};
GLFilter bw_hard_averageG = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageG
};
GLFilter bw_hard_averageB = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageB
};
GLFilter bw_hard_median = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_median
};
