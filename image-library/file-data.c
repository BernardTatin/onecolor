//
// Created by bernard on 25/04/22.
//

#include <stdbool.h>
#include <stdio.h>

#include "file-data.h"
#include "file-tools.h"

char *program_name = NULL;
char *img_source = NULL;
char *img_base_source = NULL;
char *img_destination = NULL;

bool init_file_data(const int argc, char **argv) {
    program_name = get_base_name(argv[0]);
    if (argc != 3) {
        fprintf(stderr, "Usage: %s image_source image_destination\n",
                program_name);
        return false;
    }

    img_source = argv[1];
    img_base_source = get_base_name(img_source);
    img_destination = argv[2];
    return true;
}
