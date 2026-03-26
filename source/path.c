//
// Created by tgian on 26. 3. 26..
//

#include "../include/path.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_directory(const char* path);

void construct_path(path* new_path,const char* path_string, size_t buffer_length) {

    if (buffer_length > MAX_PATH_LENGTH)
        buffer_length = MAX_PATH_LENGTH;

    size_t path_string_length = strnlen_s(path_string,buffer_length);

    (void)strncpy(new_path->path_string, path_string, path_string_length);

    new_path->path_length = path_string_length;
    new_path->is_dir = is_directory(path_string);
}


#ifdef _WIN32
#include <windows.h>

static bool is_directory(const char* path) {

    const DWORD attributes = GetFileAttributesA(path);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}
//POSIX
#else
//todo...
#endif