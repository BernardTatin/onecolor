//
// Created by bernard on 21/03/2022.

#include <stdio.h>
#include <stdlib.h>

#include "color-data.h"
#include "image-files.h"
#include "filters.h"
#include "hsv-filter.h"

static void do_help(const int exit_code) {
    fprintf(stderr, "one-color [-0|-R|-V|-B|-Y|-h hue] jpegin jpegout\n");
    exit(exit_code);
}

static inline float get_float_arg(char *arg) {
    char *end_ptr;
    float f = strtof(arg, &end_ptr);
    if (end_ptr == arg) {
        fprintf(stderr, "Float argument expected, get %s instead\n", arg);
        do_help(1);
    }
    return f;
}

int main(int argc, char **argv) {
    ImageLib_Error (*filter)(
            ImageLib_RawImage* lpInput,
            ImageLib_RawImage** lpOutput) = NULL;
    if (argc < 3) {
        do_help(1);
    } else {
        int idx = 1;
        while (*argv[idx] == '-') {
            switch (argv[1][idx]) {
                case '0': filter = filter_gray_scale;
                    break;
                case 'R': filter = hsv_filter_red;
                    break;
                case 'G': filter = hsv_filter_green;
                    break;
                case 'B': filter = hsv_filter_blue;
                    break;
                case 'Y': filter = hsv_filter_yellow;
                    break;
                case 'h': filter = hsv_filter_normal;
                    idx++;
                    if (idx >= argc) {
                        do_help(1);
                    }
                    main_HSV_filter.h = get_float_arg(argv[idx]);
                    break;
                default:
                    fprintf(stderr, "Bad filter name (%s)\n", argv[1]);
                    break;
            }
            idx++;
        }
        ImageLib_RawImage *image = loadJpegImageFile(argv[idx]);
        ImageLib_RawImage *grey_image;
        if (image == NULL) {
            fprintf(stderr, "Cannot read %s\n", argv[idx]);
            exit (1);
        }
        idx++;
        filter(image, &grey_image);
        storeJpegImageFile(grey_image, argv[idx]);
    }
    return 0;
}
