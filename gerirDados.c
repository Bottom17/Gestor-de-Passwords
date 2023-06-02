#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"

void procuraConta(char *nome_site)
{
    char *conteudo_ficheiro;
    char *separar_dados;
    char *passe_desencriptada;
    char *nome_utilizador;
    
    conteudo_ficheiro = recuperaConteudoFich();
    separar_dados = strtok(conteudo_ficheiro, ":");
    nome_utilizador = (char*)malloc(40 * sizeof(char));

    // Recuperar o resto dos sites
    while(separar_dados != NULL){
        // Se o nome do site inserido for encontrado
        if(strcmp(separar_dados, nome_site) == 0){
            separar_dados = strtok(NULL, ":");
            printf("Nome de utilizador: %s\n", separar_dados);
            strcpy(nome_utilizador, separar_dados);
            separar_dados = strtok(NULL, "\n");
            printf("Palavra-passe: %s\n", desencriptaPasse(nome_utilizador,
                                                           separar_dados));
            free(conteudo_ficheiro);
            free(nome_utilizador);
            exit(1);
        }
        separar_dados = strtok(NULL, "\n");
        separar_dados = strtok(NULL, ":");
    }

    // Se o site inserido não existir
    printf("Não foi registada nenhuma conta para o site '%s'\n", nome_site);
    free(conteudo_ficheiro);
    free(nome_utilizador);
}

void adicionaConta(char *nome_site, char *nome_utilizador, char *palavra_passe)
{
    char *conteudo_ficheiro;
    char *passe_encriptada;
    char *separar_dados;

    conteudo_ficheiro = recuperaConteudoFich(); 
    passe_encriptada = encriptaPasse(nome_utilizador, palavra_passe);

    // Recuperar primeiro site delimitado por ':'
    separar_dados = strtok(conteudo_ficheiro, ":");

    // Recuperar o resto dos sites 
    while(separar_dados != NULL){
        // Se o nome do site inserido for encontrado
        if(strcmp(separar_dados, nome_site) == 0){
            puts("Esse site já foi inserido.");
            free(conteudo_ficheiro);
            exit(1);
        }
        separar_dados = strtok(NULL, "\n");
        separar_dados = strtok(NULL, ":");
    }

    // upperNomeSite(nome_site) - Guardar o nome do site em maiusculas 
    escreveConteudoFich(nome_site, nome_utilizador, passe_encriptada);
    printf("Credenciais para o site '%s' foram inseridas com sucesso!\n",
           nome_site);
    free(conteudo_ficheiro);
    free(passe_encriptada);
}

char* upperNomeSite(char *nome_site)
{
    char *upper_site;
    int i = 0;

    upper_site = (char*)calloc(strlen(nome_site), sizeof(char));

    // Transformar nome do site em maiusculas 
    while(i < strlen(nome_site)){
        *(upper_site + i) = toupper(*(nome_site + i));
        i++;
    }

    return upper_site;
}

char* encriptaPasse(char *nome_utilizador, char *passe_desencriptada)
{
    int salto;
    int caractere_encriptado;
    char *passe_encriptada;
 
    passe_encriptada = (char*)calloc(strlen(passe_desencriptada), sizeof(char));

    // Cifra de César baseada no tamanho do nome de utilizador inserido
    salto = strlen(nome_utilizador);

    for(int x=0; x<strlen(passe_desencriptada); x++){
        caractere_encriptado = *(passe_desencriptada + x) + salto;
        if(caractere_encriptado >= 127){
            caractere_encriptado -= 127;
            caractere_encriptado += 33;
            // Se caractere for ':'
            if(caractere_encriptado == 58){
                caractere_encriptado += 1;
            }
        }
        // Se caractere for ':'
        if(caractere_encriptado == 58){
            caractere_encriptado += 1;
        }

        // Acrescenta o caractere encriptado ao fim do apontador 
        strcat(passe_encriptada, (char*)&caractere_encriptado);
    }

    return passe_encriptada;
}

char* desencriptaPasse(char *nome_utilizador, char *passe_encriptada)
{
    int salto;
    int caractere_desencriptado;
    char *passe_desencriptada;
 
    passe_desencriptada = (char*)calloc(strlen(passe_encriptada), sizeof(char));

    // Cifra de César baseada no tamanho do nome de utilizador inserido
    salto = strlen(nome_utilizador);

    for(int x=0; x<strlen(passe_encriptada); x++){
        caractere_desencriptado = *(passe_encriptada + x) - salto;
        if(caractere_desencriptado <= 33){
            caractere_desencriptado += 127;
            caractere_desencriptado -= 33;
            // Se caractere for ':'
            if(caractere_desencriptado == 58){
                caractere_desencriptado -= 1;
            }
        }
        // Se caractere for ':'
        if(caractere_desencriptado == 58){
            caractere_desencriptado -= 1;
        }

        // Acrescenta o caractere encriptado ao fim do apontador 
        strcat(passe_desencriptada, (char*)&caractere_desencriptado);
    }

    return passe_desencriptada;
}
