//
// Created by bernard on 21/03/2022.
// from:
//      https://www.tspi.at/2020/03/20/libjpegexample.html
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


#include "color-data.h"
#include "color-tools.h"
#include "filters.h"
#include "hsv-filter.h"

ImageLib_Error hsv_filter_red(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    main_HSV_filter.h = hsv_Red;
    return hsv_filter(&main_HSV_filter, lpInput, lpOutput);
}

ImageLib_Error hsv_filter_green(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    main_HSV_filter.h = hsv_Green;
    return hsv_filter(&main_HSV_filter, lpInput, lpOutput);
}

ImageLib_Error hsv_filter_blue(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    main_HSV_filter.h = hsv_Blue;
    return hsv_filter(&main_HSV_filter, lpInput, lpOutput);
}

ImageLib_Error hsv_filter_yellow(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    main_HSV_filter.h = hsv_Yellow;
    return hsv_filter(&main_HSV_filter, lpInput, lpOutput);
}

ImageLib_Error hsv_filter_normal(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    return hsv_filter(&main_HSV_filter, lpInput, lpOutput);
}

ImageLib_Error filter_gray_scale(ImageLib_RawImage* lpInput, ImageLib_RawImage** lpOutput) {
    unsigned long int pixelNumber = lpInput->width*lpInput->height;
    (*lpOutput) = make_lpOutput(lpInput);

    for(unsigned int i = 0; i < pixelNumber; i++) {
        /* Do a grayscale transformation */
        unsigned long  i3 = i*3;
        unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );
        Rout(i3) = luma;
        Gout(i3) = luma;
        Bout(i3) = luma;
    }

    return imageLibE_Ok;
}
