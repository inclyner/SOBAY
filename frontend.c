#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>



int main(int argc, char **argv){
    setbuf(stdout, NULL);
    char *secondWord, *thirdWord, *aux, delim[]=" ", *pBase,*compreJa, *dur,aut[30],*myfifo = "myfifo", answer[30];
    int feedback=1, terminate =0,fd;
    if(argc!=3){
        printf("Wrong number of arguments\n");
        exit(0);
    }
    printf("Name: %s\n", argv[1]);
    printf("Password: %s\n", argv[2]);
   /* strcat(argv[1], " ");
    strcat(argv[1], argv[2]);
    strcpy(aut, argv[1]);


    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
    write(fd, aut, strlen(aut)+1);
    close(fd);
    fd = open(myfifo, O_RDONLY);
    write(fd, answer, strlen(answer)+1);
    if(atoi(answer)==1) { printf("Wrong Credencials\nPlease try again\n"); exit(0); }*/


    do{
        char command[100];
        printf("Command: ");
        fgets(command, sizeof(command), stdin);
        secondWord=NULL; thirdWord=NULL;

        aux = strtok(command, delim);

        if(strstr(aux, "time")){
            printf("Time\n");
        }else if(strstr(aux, "sell")){
            printf("Sell\n");
            secondWord = strtok(NULL, delim);
            thirdWord = strtok(NULL, delim);
            pBase = strtok(NULL, delim);
            compreJa = strtok(NULL, delim);
            dur = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            printf("ThirdArgumment: %s", thirdWord);
            printf("pBase: %s", pBase);
            printf("compreJa: %s", compreJa);
            printf("Dur: %s", dur);
            if(secondWord==NULL||compreJa==NULL || dur==NULL||pBase==NULL || thirdWord==NULL)
                printf("Comando Inválido\n");
        }else if(strstr(aux, "cash")){
            printf("Cash\n");
        }else if(strstr(aux, "list")){
            printf("List\n");
        }else if(strstr(aux, "licat")){
            printf("Licat\n");
            secondWord = strtok(NULL, delim);
            printf("Second Argumment: %s", secondWord);
            if(secondWord==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "lisel")){
            printf("Lisel\n");
            secondWord = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            if(secondWord==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "litime")){
            printf("Litime\n");
            secondWord = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            if(secondWord==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "lival")){
            printf("Lival\n");
            secondWord = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            if(secondWord==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "add")){
            printf("Add\n");
            secondWord = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            if(secondWord==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "buy")){
            printf("Buy\n");
            secondWord = strtok(NULL, delim);
            thirdWord = strtok(NULL, delim);
            printf("SecondArgumment: %s", secondWord);
            printf("ThirdArgumment: %s", thirdWord);
            if(secondWord==NULL || thirdWord ==NULL) printf("Comando Inválido\n");
        }else if(strstr(aux, "exit")){
            printf("Exit\n");
            terminate=1;
        }else printf("Comando Inválido\n");

    }while(terminate!=1);

    return 0;
}
