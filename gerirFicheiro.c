#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestorPswd.h"

const char *nome_ficheiro = "passwords.txt";
FILE *ficheiro;

long int tamanhoFicheiro(const char *nome_fich)
{   
    long int tamanho_bytes;
    ficheiro = fopen(nome_ficheiro, "r"); 

    // Abrir ficheiro
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    // Recuperar tamanho em bytes do ficheiro
    fseek(ficheiro, 0L, SEEK_END);
    tamanho_bytes = ftell(ficheiro);

    return tamanho_bytes;
}

char* recuperaConteudoFich()
{
    long int tamanho_bytes = tamanhoFicheiro(nome_ficheiro);
    char *conteudo_ficheiro;

    ficheiro = fopen(nome_ficheiro, "r+"); 

    // Abrir ficheiro
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    conteudo_ficheiro = (char*)calloc(tamanho_bytes, sizeof(char));
    // Abrir ficheiro
    if(conteudo_ficheiro == NULL){
        printf("Couldn't allocate memory.\n");
        exit(1);
    }

    // Ler ficheiro
    fread(conteudo_ficheiro, sizeof(char), tamanho_bytes, ficheiro);

    // Fechar ficheiro
    fclose(ficheiro);

    return conteudo_ficheiro;
} 

void escreveConteudoFich(char *nome_site, char *nome_utilizador, char *palavra_passe)
{
    ficheiro = fopen(nome_ficheiro, "a"); 
    // Abrir ficheiro
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    // Escrever no ficheiro
    fprintf(ficheiro, "%s:%s:%s\n", nome_site, nome_utilizador, palavra_passe);
    // Fechar ficheiro
    fclose(ficheiro);
}
