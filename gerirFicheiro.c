#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "gestorPswd.h"

const char *nome_ficheiro = "passwords.txt";
FILE *ficheiro;

long int tamanhoFicheiro(const char *nome_fich)
{   
    long int tamanho_ficheiro = 0;
    ficheiro = fopen("passwords.txt", "r"); 
    /* Abrir ficheiro */
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    /* Recuperar tamanho do ficheiro */
    fseek(ficheiro, 0L, SEEK_END);
    tamanho_ficheiro = ftell(ficheiro);

    return tamanho_ficheiro;
}

char * recuperaConteudoFich()
{
    long int tamanho = tamanhoFicheiro(nome_ficheiro) * sizeof(char);
    char conteudo[tamanho];
    char *conteudo_ficheiro;

    conteudo_ficheiro = conteudo;
    ficheiro = fopen("passwords.txt", "r"); 
    /* Abrir ficheiro */
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    /* Ler ficheiro */
    fread(conteudo, sizeof(char), tamanhoFicheiro(nome_ficheiro), ficheiro);
    /* Fechar ficheiro */
    fclose(ficheiro);
    return conteudo_ficheiro;
} 

void escreveConteudoFich(char *user, char *pswd)
{
    char *nome_utilizador, *palavra_passe;
    char *passe_encriptada;

    nome_utilizador = user;
    palavra_passe = pswd;
    passe_encriptada = encriptaPasse(nome_utilizador, palavra_passe);

    ficheiro = fopen("passwords.txt", "a"); 
    /* Abrir ficheiro */
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    /* Escrever no ficheiro */
    fprintf(ficheiro, "%s;%s;", nome_utilizador, passe_encriptada);
    /* Fechar ficheiro */
    fclose(ficheiro);
}
