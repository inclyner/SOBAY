#ifndef HEADER_H
#define HEADER_H

#include "users_lib.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAXUSERS 20
#define MAXPROM 10
#define MAXITEMS 30

struct user{
    char username[100];
    pid_t userPid;
};

typedef struct item item, *pitem;
struct item{
    int id;
    char nome[100];
    char categoria[100];
    int valorBase;
    int comprarJa;
    char userVende[100];
    int durLeilao;
    char userCompra[100];
    pitem prox;
};


#endif