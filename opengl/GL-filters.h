//
// Created by bernard on 08/04/2022.
//

#ifndef ONE_COLOR_GL_FILTERS_H
#define ONE_COLOR_GL_FILTERS_H

typedef enum {
    FT_BW_Simple,
    FT_BW_HARD
} FilterType;

typedef void (*FilterFunction)(void *parameters);

typedef struct _GLFilter {
    FilterType type;
    void (*filter_function)(struct _GLFilter *parameters);
    void *parameters;
} GLFilter;

typedef struct {
    float KlR;
    float KlG;
    float KlB;
} GLPFilterBWNormal;

typedef enum {
    BWH_average,
    BWH_median
} BWHardType;

typedef struct {
    BWHardType type;
    float darkR;
    float darkG;
    float darkB;
    float lightR;
    float lightG;
    float lightB;
} GLPFilterBWHard;

extern GLPFilterBWNormal p_bw_normal1;
extern GLPFilterBWNormal p_bw_normal2;
extern GLPFilterBWNormal p_bw_normal3;

extern GLFilter bw_normal1;
extern GLFilter bw_normal2;
extern GLFilter bw_normal3;

void bw_normal_function(struct _GLFilter *parameters);

extern GLPFilterBWHard p_bw_hard_average;
extern GLPFilterBWHard p_bw_hard_averageR;
extern GLPFilterBWHard p_bw_hard_averageG;
extern GLPFilterBWHard p_bw_hard_averageB;
extern GLPFilterBWHard p_bw_hard_median;

extern GLFilter bw_hard_average;
extern GLFilter bw_hard_averageR;
extern GLFilter bw_hard_averageG;
extern GLFilter bw_hard_averageB;
extern GLFilter bw_hard_median;

void bw_hard_function(struct _GLFilter *parameters);

void run_GL_filter(GLFilter *filter);

void filter_bw_normal1(void);

void filter_bw_normal2(void);
void filter_bw_normal3(void);

void filter_bw_hard_black1(void);
void filter_bw_hard_black2(void);
void filter_bw_hard_blue(void);
void filter_bw_hard_red(void);
void filter_bw_hard_green(void);

void filter_average(void);

#endif //ONE_COLOR_GL_FILTERS_H
