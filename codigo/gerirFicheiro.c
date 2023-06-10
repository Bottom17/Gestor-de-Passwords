#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestorPswd.h"

const char *ficheiro_dados = "passwords.txt";
const char *ficheiro_chave = "chave.txt";
FILE *ficheiro;

long int tamanhoFicheiro(const char *nome_ficheiro)
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

char* leFicheiro(const char *nome_ficheiro, const char *modo)
{
    long int tamanho_bytes;
    char *conteudo_ficheiro;

    tamanho_bytes = tamanhoFicheiro(nome_ficheiro);
    conteudo_ficheiro = (char*)calloc(tamanho_bytes, sizeof(char));
    if(conteudo_ficheiro == NULL){
        printf("Couldn't allocate memory.\n");
        exit(1);
    }

    ficheiro = fopen(nome_ficheiro, modo); 
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", nome_ficheiro);
        exit(1);
    }

    fread(conteudo_ficheiro, sizeof(char), tamanho_bytes, ficheiro);
    fclose(ficheiro);

    return conteudo_ficheiro;
} 

void escreveFicheiroDados(char *site, char *utilizador, char *passe_encriptada)
{
    ficheiro = fopen(ficheiro_dados, "a"); 
    if(ficheiro == NULL){
        printf("Couldn't open file %s\n", ficheiro_dados);
        exit(1);
    }

    fprintf(ficheiro, "%s %s %s\n", site, utilizador, passe_encriptada);
    fclose(ficheiro);

    free(passe_encriptada);
    passe_encriptada = NULL;
}

void escreveFicheiroChave(char *chave_criptografica_encriptada)
{
    ficheiro = fopen(ficheiro_chave, "w");
    if(ficheiro == NULL){
        puts("Erro relacionado com um ficheiro");
        exit(1);
    }

    fwrite(chave_criptografica_encriptada, sizeof(char), tamanho_chave, ficheiro);
    fclose(ficheiro);

    free(chave_criptografica_encriptada);
    chave_criptografica_encriptada = NULL;
}

