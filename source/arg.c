//
// Created by tgian on 26. 3. 26..
//

#include "../include/arg.h"
#include "../include/global.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


bool check_argument_length(int argc, char* argv[]);
bool parse_CMD_help(int argc, char* argv[], void** out_cmd_data);
bool parse_CMD_split(int argc, char* argv[], void** out_cmd_data);
bool parse_CMD_join(int argc, char* argv[], void** out_cmd_data);
bool is_unsigned_integer(const char* str, size_t size);

enum CMD_ID parse(int argc, char* argv[], void** out_cmd_data) {

    if (argc < 2)
        return none;

    if (!check_argument_length(argc,argv))
        return none;

    //parse --help / --split / --join

    enum CMD_ID cmd_id = none;

    if (strcmp(argv[1],"--help") == 0) {

        bool result = parse_CMD_help(argc,argv,out_cmd_data);
        if (!result) {
            printf("fail to parse --help");
        }
        else
            cmd_id = help;
    }
    else if (strcmp(argv[1],"--split") == 0) {

         bool result = parse_CMD_split(argc,argv,out_cmd_data);
        if (!result) {
            printf("fail to parse --split");
        }
        else
        cmd_id = split;
    }
    else if (strcmp(argv[1],"--join") == 0) {

        bool result = parse_CMD_join(argc,argv,out_cmd_data);
        if (!result) {
            printf("fail to parse --join");
        }
        else
            cmd_id = join;
    }


    return cmd_id;


}

bool parse_CMD_help(const int argc, char* argv[], void** out_cmd_data) {

    //fsplit --help
    if (argc == 2) {

        CMD_help cmd_data = {help,"",0};
        copy_CMD(*out_cmd_data,&cmd_data,help);

        return true;
    }

    //fsplit --help <cmd>
    if (argc == 3) {

        CMD_help cmd_data = {
            .id = help
        };

        const size_t len = strlen(argv[2]);

        strncpy(cmd_data.cmd, argv[2], len);
        cmd_data.cmd[len] = '\0';
        cmd_data.cmd_length = len;

        copy_CMD(*out_cmd_data,&cmd_data,help);

        return true;
    }

    return false;
}


bool parse_CMD_split(int argc, char* argv[], void** out_cmd_data) {

    if (argc < 3)
        return false;

    CMD_split cmd_data = {
        .id             = split
    };

    construct_path(&cmd_data.input_path,argv[2],strlen(argv[2]));

    char current_option = '\0';
    int current_arg_type = 0;

    // arg_type 0 : name
    // arg_type 1 : int
    // arg_type 2 : string

    for (int idx = 3; idx < argc && idx < MAX_ARGUMENT_COUNT; idx++) {

        if (current_arg_type == 0) {

            if (strcmp(argv[idx],"-s") == 0) {
                current_arg_type = 1;
                current_option = 's';
            }
            else if (strcmp(argv[idx],"-c") == 0) {
                current_arg_type = 1;
                current_option = 'c';
            }
            else if (strcmp(argv[idx],"-o") == 0) {
                current_arg_type = 2;
                current_option = 'o';
            }
        }
        else if (current_arg_type == 1) {

            bool is_uint = is_unsigned_integer(argv[idx],strlen(argv[idx]));
            if (!is_uint)
                return false;

            long int_argv = strtol(argv[idx],NULL,10);

            if (current_option == 's') {
                cmd_data.file_size = int_argv;
            }
            else if (current_option == 'c') {
                cmd_data.file_count = int_argv;
            }

            current_arg_type = 0;
            current_option = '\0';
        }
        else if (current_arg_type == 2 && current_option == 'o') {

            construct_path(&cmd_data.output_path,argv[idx],strlen(argv[idx]));
        }

    }

    copy_CMD(*out_cmd_data,&cmd_data,split);
    return true;
}


bool parse_CMD_join(int argc, char* argv[], void** out_cmd_data) {

    //fsplit --join <path>
    if (argc == 3) {

        CMD_join cmd_data = {.id = join };
        construct_path(&cmd_data.input_path,argv[2],strlen(argv[2]));
        copy_CMD(*out_cmd_data,&cmd_data,join);

        return true;
    }

    //fsplit --help <cmd>
    if (argc == 5) {

        CMD_join cmd_data = {.id = join};
        construct_path(&cmd_data.input_path,argv[2],strlen(argv[2]));
        
        if (strcmp(argv[3],"-o") != 0)
            return false;

        construct_path(&cmd_data.output_path,argv[4],strlen(argv[4]));

        copy_CMD(*out_cmd_data,&cmd_data,join);
        return true;
    }

    return false;
}


bool check_argument_length(int argc, char* argv[]) {

    for (int i = 1; i < argc; i++) {
        if (strnlen_s(argv[i],MAX_CMD_BUFFER_LENGTH - 1) == MAX_CMD_BUFFER_LENGTH - 1) {
            return false;
        }
    }

    return true;
}


bool is_unsigned_integer(const char* str, size_t size) {

    for (size_t idx = 0; idx < size; idx++) {
        if (!(str[idx] >= '0' && str[idx] <= '9')) {
            return false;
        }
    }

    return true;
}
