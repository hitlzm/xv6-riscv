#include "kernel/types.h"
#include "user/user.h"

void sieve(int pipefd[2]);

int main(){
    int pipefd[2];

    pipe(pipefd);

    if(fork() == 0){
        close(pipefd[1]);
        sieve(pipefd);
    } else {
        close(pipefd[0]);

        for(int i = 2; i <= 35; i++){
            write(pipefd[1], &i, sizeof(int));
        }

        close(pipefd[1]);
        wait(0);
    }

    exit(0);
}


void sieve(int pipefd[2]) {
    int prime;
    int num;
    int newpipe[2];

    if(read(pipefd[0], &prime, sizeof(int)) == 0)
        exit(0);

    printf("prime %d\n", prime);

    pipe(newpipe);

    if(fork() == 0){
        close(newpipe[1]);
        sieve(newpipe);
    } else {
        close(newpipe[0]);

        while(read(pipefd[0], &num, sizeof(int)) != 0){
            if(num % prime != 0){
                write(newpipe[1], &num, sizeof(int));
            }
        }

        close(newpipe[1]);
        wait(0);
    }
}
