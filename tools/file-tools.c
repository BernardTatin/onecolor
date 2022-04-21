//
// Created by bernard on 21/04/22.
//

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "file-tools.h"

char *get_base_name(const char *full_file_name) {
    char *tmp_file_name = strdup(full_file_name);
    char *base_name = strdup(basename(tmp_file_name));
    free(tmp_file_name);
    return base_name;
}
