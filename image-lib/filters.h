//
// Created by bernard on 21/03/2022.
//

#ifndef ONECOLOR_FILTERS_H
#define ONECOLOR_FILTERS_H

ImageLib_Error exec_filter(ImageLib_RawImage* lpInput, ImageLib_RawImage** lpOutput);

ImageLib_Error filter_gray_scale(ImageLib_RawImage* lpInput, ImageLib_RawImage** lpOutput);
ImageLib_Error filter_hue(ImageLib_RawImage* lpInput, ImageLib_RawImage** lpOutput);


#endif //ONECOLOR_FILTERS_H
