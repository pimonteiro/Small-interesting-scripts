#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SIZEOFPROGRAM 10
void help(){
    printf("No arguments given\n. Please.");
}

char** build_new_argv(int n, char** old){
    char** ret = malloc(sizeof(char*) * n);
    ret[0] = malloc(sizeof(SIZEOFPROGRAM));
    int i;
    for(i = 1; i < n; i++){
        ret[i] = malloc(strlen(old[i] + 1));
        strcpy(ret[i], old[i]);
    }
    return ret;
}


int main(int argc, char** argv){
    if(argc < 1){
        help();
    }

    printf("[1] - Break into various files.\n");
    printf("[2] - Rebuild file.\n");
    char ch[1];
    read(0, &ch, 1);
    int choice = atoi(ch);

    int flag = 0;
    while(!flag){
        if(choice == 1){
            printf("How many files do you want to break to?\n");
            char tmp[1];
            read(0, &tmp, 1);
            
            int f = fork();
            if(f == 0){
                execlp("./breaker", "breaker", argv[1], tmp, NULL);
                perror("Could not execute fork.\n");
                _exit(-1);
            }
            else{
                printf("Breaking file......."); //Algoritmo de espera para ficar bonito
                wait(NULL); //Aplicar conceitos de SO para caso dê erro no filho o pai nao dizer que correu tudo bem  TODO
                flag = 1;
            }
        }
        else if(choice == 2){
                int f = fork();
                if (f == 0){
                    char** tmp = build_new_argv(argc, argv);
                    execvp("rebuilder", tmp);
                }
                else{
                    printf("Rebuilding the original file.......");
                    wait(NULL);
                    flag = 1;
                }
                
            }
            else{
                printf("Invalid option. Please choose again.\n");
            }
    }
    
    return 0;
}