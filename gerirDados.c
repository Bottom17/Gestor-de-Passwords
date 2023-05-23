#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorPswd.h"

void verificaConta(char *user, char *pswd)
{
    const char *delimitar_dados = ";";
    char *nome_utilizador, *palavra_passe;
    char *separar_dados, *passe_encriptada;
    char *conteudo_ficheiro;

    nome_utilizador = user;
    palavra_passe = pswd;
    passe_encriptada = encriptaPasse(nome_utilizador, palavra_passe);
    conteudo_ficheiro = recuperaConteudoFich(); 

    /* Recuperar primeira informação do ficheiro delimitado por um ';' */
    separar_dados = strtok(conteudo_ficheiro, delimitar_dados);
    /* Recuperar o resto das informações */
    while(separar_dados != NULL){
        /* Se o nome de utilizador inserido for encontrado */
        if(strcmp(separar_dados, nome_utilizador) == 0){
            separar_dados = strtok(NULL, delimitar_dados);
            /* Verificar palavra-passe inserida */
            if (strcmp(separar_dados, passe_encriptada) == 0){
                printf("Conexão bem sucedida %s.\n", nome_utilizador);
                exit(1); 
            }
        }
        separar_dados = strtok(NULL, delimitar_dados);
    }
    /* Se a conta inserida não existir */
    puts("O utilizador ou palavra-passe não existem.");
}

void criaConta(char *user, char *pswd)
{
    /* Verificar que o nome de utilizador não existe */
    const char *delimitar_dados = ";";
    char *nome_utilizador, *palavra_passe;
    char *conteudo_ficheiro;
    char *separar_dados;
    
    nome_utilizador = user;
    palavra_passe = pswd;
    conteudo_ficheiro = recuperaConteudoFich(); 
    /* Recuperar primeira informação do ficheiro delimitado por um ';' */
    separar_dados = strtok(conteudo_ficheiro, delimitar_dados);
    
    /* Recuperar o resto das informações */
    while(separar_dados != NULL){
        /* Se o nome de utilizador inserido for encontrado */
        if(strcmp(separar_dados, nome_utilizador) == 0){
            puts("Esse utilizador já existe.");
            exit(1);
        }
        separar_dados = strtok(NULL, delimitar_dados);
    }
    escreveConteudoFich(nome_utilizador, palavra_passe);  
    printf("Seja muito bem-vindo %s!\n", nome_utilizador);
}

char * encriptaPasse(char *user, char *pswd)
{
    char *nome_utilizador, *passe_encriptada;
    int salto;
    
    nome_utilizador = user;
    passe_encriptada = pswd;
    /* Cifra de César baseado no tamanho do nome de utilizador inserido*/
    salto = strlen(nome_utilizador);
    
    for(int x=0; x<strlen(passe_encriptada); x++){
        *(passe_encriptada + x) += salto;
        if(*(passe_encriptada + x) >= 127){
            *(passe_encriptada + x) -= 127;
            *(passe_encriptada + x) += 33;
        }
    }
    return passe_encriptada;
}