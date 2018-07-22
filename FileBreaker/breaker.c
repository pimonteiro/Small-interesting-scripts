#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void help(){
    printf("No arguments given. Please .......\n");
}

int readln(int fd, char* buffer){
    char total[1024];
    char buff[1];
    int r = read(fd, &buff, 1);
    int ret = r;
    int i = 0;
    while(r > 0 && buff[r-1] != '\n' && buff[r-1] != EOF){
        printf("%s\n", total);
        total[i] = buff;
        r = read(fd, &buff, 1);
        ret += r;
    }

    buffer = total;

    return ret;
}

void execute_round_robin_distribuition(int fd, int n){
    int final[n];
    int current = 1;
    for(int i = 0; i < n; i++){
        char* name;
        sprintf(name, "file%d", i);
        final[i] = open(name, O_CREAT, O_WRONLY);
    }
    
    //Maybe escrever na primeira linha o modo de distribuiçao usado? TODO
    char* buff;
    int r = readln(fd, buff);
    while(r > 0){
        write(final[current++], &buff, r);
        if(current > n) current = 1;
        r = readln(fd, buff);
    }

    for(int i = 0; i < n; i++) close(final[i]);
}


int main(int argc, char** argv){
    if(argc < 1){
        help();
    }
    int fd = open(argv[1], O_RDONLY);
    
    int n = atoi(argv[2]);
    execute_round_robin_distribuition(fd, n);

    close(fd);
    return 0;
}