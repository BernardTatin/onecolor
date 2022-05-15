/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2022.  Bernard Tatin                                         *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 ******************************************************************************/

//
// Created by bernard on 21/03/2022.
// from:
//      https://www.tspi.at/2020/03/20/libjpegexample.html
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <jpeglib.h>

#include "color-data.h"
#include "image-files.h"
#include "main-configuration.h"

ImageLib_RawImage *loadJpegImageFile(char *lpFilename) {
    struct jpeg_decompress_struct info;
    struct jpeg_error_mgr         err;

    if (global_configuration.verbose) {
        fprintf(stdout, "Reading %s\n", lpFilename);
    }
    ImageLib_RawImage *lpNewImage;

    unsigned long int imgWidth, imgHeight;
    int               numComponents;

    unsigned long int dwBufferBytes;
    unsigned char     *lpData;

    unsigned char *lpRowBuffer[1];

    FILE *fHandle;

    fHandle = fopen(lpFilename, "rb");
    if (fHandle == NULL) {
#ifdef DEBUG
        fprintf(stderr, "%s:%u: Failed to read file %s\n", __FILE__, __LINE__, lpFilename);
#endif
        return NULL;
    }

    info.err = jpeg_std_error(&err);
    jpeg_create_decompress(&info);

    jpeg_stdio_src(&info, fHandle);
    jpeg_read_header(&info, TRUE);

    jpeg_start_decompress(&info);
    imgWidth      = info.output_width;
    imgHeight     = info.output_height;
    numComponents = info.num_components;

#ifdef DEBUG
    fprintf(
            stderr,
            "%s:%u: Reading JPEG with dimensions %lu x %lu and %u components\n",
            __FILE__, __LINE__,
            imgWidth, imgHeight, numComponents
        );
#endif

    dwBufferBytes = imgWidth * imgHeight * 3; /* We only read RGB, not A */
    lpData        = (unsigned char *) malloc(sizeof(unsigned char) * dwBufferBytes);

    lpNewImage = (ImageLib_RawImage *) malloc(sizeof(ImageLib_RawImage));
    lpNewImage->numComponents = numComponents;
    lpNewImage->width         = imgWidth;
    lpNewImage->height        = imgHeight;
    lpNewImage->lpData        = lpData;

    /* Read scanline by scanline */
    while (info.output_scanline < info.output_height) {
        lpRowBuffer[0] = (unsigned char *) (&lpData[3 * info.output_width * info.output_scanline]);
        jpeg_read_scanlines(&info, lpRowBuffer, 1);
    }

    jpeg_finish_decompress(&info);
    jpeg_destroy_decompress(&info);
    fclose(fHandle);

    return lpNewImage;
}

int storeJpegImageFile(ImageLib_RawImage *lpImage, char *lpFilename) {
    struct jpeg_compress_struct info;
    struct jpeg_error_mgr       err;

    unsigned char *lpRowBuffer[1];

    FILE *fHandle;

    if (global_configuration.verbose) {
        fprintf(stdout, "Writing %s\n", lpFilename);
    }
    fHandle = fopen(lpFilename, "wb");
    if (fHandle == NULL) {
        fprintf(stderr, "%s:%u Failed to open output file %s\n", __FILE__, __LINE__, lpFilename);
        return 1;
    }

    info.err = jpeg_std_error(&err);
    jpeg_create_compress(&info);

    jpeg_stdio_dest(&info, fHandle);

    info.image_width      = lpImage->width;
    info.image_height     = lpImage->height;
    info.input_components = 3;
    info.in_color_space   = JCS_RGB;

    jpeg_set_defaults(&info);
    jpeg_set_quality(&info, 100, TRUE);

    jpeg_start_compress(&info, TRUE);

    /* Write every scanline ... */
    while (info.next_scanline < info.image_height) {
        lpRowBuffer[0] = &(lpImage->lpData[info.next_scanline * (lpImage->width * 3)]);
        jpeg_write_scanlines(&info, lpRowBuffer, 1);
    }

    jpeg_finish_compress(&info);
    fclose(fHandle);

    jpeg_destroy_compress(&info);
    return 0;
}
