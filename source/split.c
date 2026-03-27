//
// Created by user on 26. 3. 27..
//
#include "split.h"
typedef struct {
    size_t byte_per_file;
    size_t total_bytes;
    FILE *file;
}split_context;

void split_with_count(CMD_split* cmd,split_context* ctx);
void split_with_size(CMD_split* cmd,split_context* ctx);
uint64_t get_total_bytes(CMD_split* cmd);

void split_file(CMD_split* cmd) {

    split_context ctx = {0,};
    if (cmd->file_count != 0) {
        //file count
         ctx.total_bytes = get_total_bytes(cmd);
    }
    (void)ctx;
}

void split_with_count(CMD_split* cmd,split_context* ctx) {
    (void)cmd;
    (void)ctx;

}

uint64_t get_total_bytes(CMD_split* cmd) {

    //
    if (!cmd->input_path.is_dir) {
        FILE* fp = fopen(cmd->input_path.path_string, "rb");
        if (!fp) return 0;

        _fseeki64(fp, 0, SEEK_END);
        uint64_t size = _ftelli64(fp);

        printf("파일 크기: %lld 바이트\n", size);
        fclose(fp);
        return size;
    }
    return 0;
}