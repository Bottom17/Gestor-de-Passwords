#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "gestorPswd.h"

const int tamanho_chave = 15; 

char* geraChaveCriptografica()
{
    char *chave_gerada; 
    int i = 0;
    int caractere_aleatorio;

    chave_gerada = (char*)calloc(tamanho_chave, sizeof(char));

    srand((unsigned)time(NULL));
         
    while (i < tamanho_chave) {
        // caractere_aleatorio = rand() % 83; 
        caractere_aleatorio = rand() % 93;
        caractere_aleatorio += 33;
        strncat(chave_gerada, (char*)&caractere_aleatorio, tamanho_chave);
        i++;
    }

    return chave_gerada;
}

void verificaChaveMestra(char *chave_mestra)
{
    int caractere_maiusculo = 0;
    int caractere_especial = 0;
    int caractere_numerico = 0;
    int i = 0;

    if (strlen(chave_mestra) != tamanho_chave) {
        printf("A chave mestra tem que ter %d caracteres\n", 
               tamanho_chave);
        printf("Pressione Enter para continuar: ");
        // Enquanto que o utilizador nao inserir 'Enter', esperar
        while(getchar() != '\n')
            ;
        mostraMenu();
    } 

    while(i < strlen(chave_mestra)){
        if(isupper((int)*(chave_mestra + i)))
            caractere_maiusculo++;
        if(isdigit((int)*(chave_mestra + i)))
            caractere_numerico++;
        if(ispunct((int)*(chave_mestra + i)))
            caractere_especial++;
        i++;
    }

    *(chave_mestra + i) = '\0';

    if(caractere_especial <= 0 || caractere_numerico <= 0 || caractere_maiusculo <= 0){
        puts("Volte a verificar os requirimentos para a palavra-passe mestra");
        printf("Pressione Enter para continuar: ");
        // Eliminar 'Enter' para evitar problemas com futuros inputs
        while(getchar() != '\n')
            ;
        mostraMenu();
    }

    else {
        puts("A chave mestra inserida respeita todos os requirimentos");
        printf("Pressione Enter para continuar: ");
        // Eliminar 'Enter' para evitar problemas com futuros inputs
        while(getchar() != '\n')
            ;
    }
}

char* desencriptaChaveCriptografica(char *chave_mestra)
{
    char *chave_criptografica_encriptada;
    char *chave_criptografica;
    int caractere_desencriptado;

    chave_criptografica = (char*)calloc(tamanho_chave, sizeof(char));
    chave_criptografica_encriptada = leFicheiro(ficheiro_chave, "r");

    for(int x=0; x<strlen(chave_mestra); x++){
        caractere_desencriptado = 0;
        caractere_desencriptado = *(chave_criptografica_encriptada + x) 
                                    - *(chave_mestra + x);
        while(caractere_desencriptado <= 33){
            caractere_desencriptado += 127;
            caractere_desencriptado -= 33;
        }
        // Acrescenta o caractere encriptado ao fim da string
        strncat(chave_criptografica, (char*)&caractere_desencriptado, tamanho_chave);
    }
    
    free(chave_criptografica_encriptada);
    chave_criptografica_encriptada = NULL;
    free(chave_mestra);
    chave_mestra = NULL;

    return chave_criptografica;
}



















