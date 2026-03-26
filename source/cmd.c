//
// Created by tgian on 26. 3. 26..
//

#include "../include/cmd.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool alloc_CMD(void** buffer) {

    *buffer = malloc(CMD_STRUCT_SIZE);

    if (*buffer == NULL) {
        return false;
    }
    return true;
}

void copy_CMD(void* dest,const void* src,enum CMD_ID id) {


    switch (id) {
        case none:
            return;

        case help:
        (void)memcpy(dest,src,sizeof(CMD_help));
            return;

        case split:
        (void)memcpy(dest,src,sizeof(CMD_split));
            return;

        case join:
        (void)memcpy(dest,src,sizeof(CMD_join));
    }

}

void free_CMD(void** buffer) {

    free(*buffer);
}