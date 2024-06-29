#include "header.h"

void preenche(pitem lista_items, int id, char nome[100], char categoria[100], int atual, int ja, int durLeilao, char vende[100],
              char compra[100]) {

    lista_items->id = id;
    strcpy(lista_items->nome,nome);
    strcpy(lista_items->categoria,categoria);
    lista_items->valorBase=atual;
    lista_items->comprarJa = ja;
    lista_items->durLeilao = durLeilao;
    strcpy(lista_items->userVende, vende);
    strcpy(lista_items->userCompra, compra);
    lista_items->prox = NULL;

}
pitem insere_final(pitem lista_items, int id, char nome[100], char categoria[100], int valorBase, int comprarJa, int durLeilao,
                   char userVende[100], char userCompra[100]) {

    pitem novo, aux;
    novo= malloc(sizeof (item));
    if(novo==NULL){
        printf("Erro na alocacao de memoria\n");
        return lista_items;
    }
    preenche(novo,id, nome, categoria, valorBase, comprarJa, durLeilao, userVende, userCompra);
    if(lista_items==NULL) lista_items = novo;
    else{
        aux = lista_items;
        while(aux->prox !=NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return lista_items;
}

void liberta_items(pitem lista_items){
    pitem aux;
    while (lista_items!=NULL){
        aux=lista_items;
        lista_items=lista_items->prox;
        free(aux);
    }

}

void erroVariavel(char varName[]){
    printf("Erro na variavel %s\n", varName);
    exit(0);
}

void fileNotExists(char fileName[]){
    printf("Ficheiro %s não existe\n", fileName);
    exit(0);
}

void mostra_info(pitem lista_items){
    while(lista_items!=NULL){
        printf("%d %s %s %d %d %d %s %s\n", lista_items->id, lista_items->nome, lista_items->categoria, lista_items->valorBase, lista_items->comprarJa, lista_items->durLeilao, lista_items->userVende, lista_items->userCompra);
        lista_items=lista_items->prox;
    }
}

int sizeList(pitem lista_items){
    int count=0;
    pitem p = lista_items;
    while(p!=NULL){
        count++;
        p = p->prox;
    }
    return count;
}

pitem readFileItems(char fileName[], pitem lista_items){
    FILE *f = fopen(fileName, "r");
    int id, comprarJa, valorBase, durLeilao, lido;
    char nome[100], categoria[100], userVende[100], userCompra[100];
    int i=0;
    while(fscanf(f, "%d %s %s %d %d %d %s %s", &id, nome, categoria, &valorBase,&comprarJa,&durLeilao, userVende, userCompra)!=EOF && i<MAXITEMS) {
        lista_items = insere_final(lista_items,id, nome, categoria, valorBase, comprarJa, durLeilao, userVende, userCompra);
        i = sizeList(lista_items);
        printf("Tamanho lista %d\n", i);
    }
    fclose(f);
    return lista_items;
}

void readFileProm(char fileName[], char* proms[]){
    int i =0;

}

int main(int argc, char **argv){
    if(argc!=1){
        printf("Wrong Number of Arguments\n");
        exit(0);
    }
    char *fusers, *fprom,*fitems, *aux, *secondWord, delim[]=" ", arrProm[MAXPROM],firstProm[30], str[30],command[100]="",aux_char[100];
    int exit =0, fd_rec[2], temp=0, nUsers=0, i=0;
    union sigval val;
    struct user usersLogin[MAXUSERS];

    pitem lista_items = NULL;
    pipe(fd_rec);
    setbuf(stdout,NULL);
    //Variaveis de Ambiente
    fusers = getenv("FUSERS");
    if(fusers==NULL) erroVariavel("FUSERS");
    if(access(fusers, F_OK)!=0) fileNotExists(fusers);

    fprom = getenv("FPROMOTERS");
    if(fprom==NULL) erroVariavel("FPROMOTERS");
    if(access(fprom, F_OK)!=0) fileNotExists(fusers);
    else{
        FILE *f = fopen(fprom, "r");
        fgets(firstProm, 30, f);
        printf("%s\n", firstProm);
    }
    firstProm[strlen(firstProm)-1] = '\0';
    fitems = getenv("FITEMS");
    if(fitems!=NULL) {
        if(access(fitems, F_OK)!=0) fileNotExists(fusers);
        lista_items = readFileItems(fitems, lista_items);
    }



    while(temp!=5) {
        printf("What do you want to test?(1-comandos; 2-promotor; 3-utilizadores; 4-items; 5-exit)\n");
        //scanf("%d", &temp);
        fgets(aux_char, sizeof(aux_char), stdin);
        temp=atoi(aux_char);
        fflush(stdin);
        if (temp == 1) {
            do {
                printf("Command: ");
                
		        fgets(command, sizeof(command), stdin);
                secondWord = NULL;
                aux = strtok(command, delim);
                if (strstr(aux, "users")) {
                    printf("Users\n");
                } else if (strstr(aux, "list")) {
                    printf("List\n");
                } else if (strstr(aux, "reprom")) {
                    printf("Reprom\n");
                } else if (strstr(aux, "prom")) {
                    printf("Prom\n");
                } else if (strstr(aux, "cancel")) {
                    printf("Cancel\n");
                    secondWord = strtok(NULL, delim);
                    printf("Second Argumment: %s\n", secondWord);
                    if (secondWord == NULL) printf("Comando Inválido\n");
                } else if (strstr(aux, "kick")) {
                    printf("Kick\n");
                    secondWord = strtok(NULL, delim);
                    printf("SecondArgumment: %s\n", secondWord);
                    if (secondWord == NULL) printf("Comando Inválido\n");
                } else if (strstr(aux, "close")) {
                    printf("Close\n");
                    exit = 1;
               }  else printf("Comando Inválido\n");
            } while (exit != 1);
        }
        else if (temp == 2) {
           while(i<2) {
                int pid = fork();
                if (pid == 0) {
                    close(STDOUT_FILENO);
                    dup(fd_rec[1]);
                    close(fd_rec[1]);
                    close(fd_rec[0]);
                    execlp(firstProm, firstProm, NULL);
                    perror("Prom não encontrado\n");
                    return -1;
                } else if (pid > 0) {
                    close(fd_rec[1]);
                    int sizeP = read(fd_rec[0], str, sizeof(str) - 1);
                    str[sizeP] = '\0';
                    printf("%s\n", str);
                }i++;
                if(i==2) sigqueue(pid, SIGINT, val);
           }
        }

        else if (temp == 3) {
            nUsers = loadUsersFile(fusers);
            printf("Lidos %d utilizadores\n", nUsers);
            printf("Saldo user: %d\n", getUserBalance("user"));
            printf("Saldo user1: %d\n", getUserBalance("user1"));
            printf("Saldo user2: %d\n", getUserBalance("user2"));
            printf("Saldo user3: %d\n", getUserBalance("user3"));

            updateUserBalance("user", getUserBalance("user")-1);
            updateUserBalance("user1", getUserBalance("user1")-1);
            updateUserBalance("user2", getUserBalance("user2")-1);
            updateUserBalance("user3", getUserBalance("user3")-1);

            saveUsersFile(fusers);

        }
        else if (temp == 4) {
            mostra_info(lista_items);
        }
        i=0;
    }

    close(fd_rec[0]);
    close(fd_rec[1]);
    liberta_items(lista_items);
    return 0;}
