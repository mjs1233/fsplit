
#include "main.h"

int main(int argc, char* argv[]) {

    void* cmd_buffer = NULL;
    alloc_CMD(&cmd_buffer);
    enum CMD_ID id = parse(argc,argv,&cmd_buffer);
    printf("%d",(int)id);


    free_CMD(&cmd_buffer);

    return 0;
}