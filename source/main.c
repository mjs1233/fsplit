
#include "main.h"

int main(int argc, char* argv[]) {

    printf("____");
    void* cmd_buffer = NULL;
    alloc_CMD(&cmd_buffer);
    enum CMD_ID id = parse(argc,argv,&cmd_buffer);

    if (id == help) {

        CMD_help* argument = cmd_buffer;
        printf("help : <CMD = %s> <CMD_LEN = %lld>",argument->cmd,argument->cmd_length);
    }
    else if (id == split) {
        CMD_split* argument = cmd_buffer;
        printf("split : <in path = %s> <count = %d> <size = %d> <out path = %s>",argument->input_path.path_string,argument->file_count,argument->file_size,argument->output_path.path_string);
        split_file(argument);

    }
    else if (id == join) {
        CMD_join* argument = cmd_buffer;
        printf("join : <in path = %s> <out path = %s>",argument->input_path.path_string,argument->output_path.path_string);
    }


    free_CMD(&cmd_buffer);

    return 0;
}