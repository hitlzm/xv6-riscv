#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char buf[512];
    char *xargv[MAXARG];
    int i;

    // 先把原来的参数复制过去
    for(i = 1; i < argc; i++){
        xargv[i - 1] = argv[i];
    }

    int n = i - 1;
    int idx = 0;
    char c;

    while(read(0, &c, 1) == 1){
        if(c == '\n'){
            buf[idx] = 0;
            xargv[n] = buf;
            xargv[n + 1] = 0;

            int pid = fork();
            if(pid == 0){
                exec(argv[1], xargv);
                fprintf(2, "xargs: exec failed\n");
                exit(1);
            } else {
                wait(0);
            }

            idx = 0;
        } else {
            buf[idx++] = c;
        }
    }

    exit(0);
}
