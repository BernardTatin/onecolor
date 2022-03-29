//
// Created by bernard on 21/03/2022.
//

#ifndef ONECOLOR_FILTERS_H
#define ONECOLOR_FILTERS_H

ImageLib_Error filter_gray_scale(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);

ImageLib_Error hsv_filter_red(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);
ImageLib_Error hsv_filter_green(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);
ImageLib_Error hsv_filter_blue(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);
ImageLib_Error hsv_filter_yellow(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);
ImageLib_Error hsv_filter_normal(
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput);

#endif //ONECOLOR_FILTERS_H
