//
// Created by tgian on 26. 3. 26..
//

#ifndef FILESPLITER_PATH_H
#define FILESPLITER_PATH_H
#include "../include/global.h"

#include <stdbool.h>
#include <inttypes.h>


typedef struct {

    char path_string[MAX_PATH_LENGTH + 1];
    size_t path_length;
    bool is_dir;
} path;


void construct_path(path* new_path,const char* path_string, size_t buffer_length);


#endif //FILESPLITER_PATH_H