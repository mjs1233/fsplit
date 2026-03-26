//
// Created by tgian on 26. 3. 26..
//

#ifndef FILESPLITER_CMD_H
#define FILESPLITER_CMD_H

#include "../include/path.h"
#include "../include/global.h"


enum CMD_ID {
    none,
    help,
    split,
    join
};

//--help <cmd>
typedef struct {

    enum CMD_ID id;
    char cmd[MAX_CMD_BUFFER_LENGTH];
    size_t cmd_length;

}CMD_help;

/*
 --split <path> <option...>

 option
 -s {integer} : set single .spf file size in kb  (not works with -c)
 -c {integer} : set count of .spf file (not works with -s)
 -o {path} : output path
 */
typedef struct {

    enum CMD_ID id;
    path input_path;
    int file_size;
    int file_count;
    path output_path;

}CMD_split;

/*
 --join <path> <option...>

if path is dir ---> find every .spf in dir and join them

 option
 -o {path} : output path
 */
typedef struct {

    enum CMD_ID id;
    path input_path;
    path output_path;

}CMD_join;

//change if larger struct is implemented
#define CMD_STRUCT_SIZE sizeof(CMD_split)

/*
    allocate memory space for CMD_... struct

    return: (bool) true if alloc success
 */
bool alloc_CMD(void** buffer);


/*
    move src to dest with internal size calc based on id
    nothing happen when id == none

    return: (void)
*/
void copy_CMD(void* dest,const void* src,enum CMD_ID id);


/*
    free buffer

    return: (void)
*/
void free_CMD(void** buffer);

#endif //FILESPLITER_CMD_H