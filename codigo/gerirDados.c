#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"

void procuraDados(char *nome_site, char *chave_criptografica)
{
    char *conteudo_ficheiro;
    char *separar_dados;
    char *passe_desencriptada;
    
    conteudo_ficheiro = leFicheiro(ficheiro_dados, "r");
    separar_dados = strtok(conteudo_ficheiro, " ");

    // Recuperar o resto dos sites
    while(separar_dados != NULL){
        // Se o nome do site inserido for encontrado
        if(strcmp(separar_dados, nome_site) == 0){
            printf("chave criptografica1: %s\n", chave_criptografica);
            separar_dados = strtok(NULL, " ");
            printf("Nome de utilizador: %s\n", separar_dados);
            separar_dados = strtok(NULL, "\n");
            passe_desencriptada = desencriptaDados(chave_criptografica,
                                                   separar_dados);
            printf("Palavra-passe: %s\n", passe_desencriptada);

            free(conteudo_ficheiro);
            free(passe_desencriptada);
            free(nome_site);
            conteudo_ficheiro = NULL;
            passe_desencriptada = NULL;
            nome_site = NULL;

            printf("Pressione Enter para continuar: ");
            // Eliminar 'Enter' para evitar problemas com futuros inputs
            while(getchar() != '\n')
                ;
            mostraMenu();
        }
        separar_dados = strtok(NULL, "\n");
        separar_dados = strtok(NULL, " ");
    }

    // Se o site inserido não existir
    printf("Não foi registada nenhuma conta para o site '%s'\n", nome_site);

    free(conteudo_ficheiro);
    free(nome_site);
    conteudo_ficheiro = NULL;
    nome_site = NULL;

    printf("Pressione Enter para continuar: ");
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;
    mostraMenu();
}

void adicionaDados(char *chave_criptografica, char *nome_site, char *nome_utilizador, char *palavra_passe)
{
    char *conteudo_ficheiro;
    char *passe_encriptada;
    char *separar_dados;

    conteudo_ficheiro = leFicheiro(ficheiro_dados, "r+"); 
    // Recuperar primeiro site delimitado por ' '
    separar_dados = strtok(conteudo_ficheiro, " ");

    // Recuperar o resto dos sites 
    while(separar_dados != NULL){
        // Se o nome do site inserido for encontrado
        if(strcmp(separar_dados, nome_site) == 0){
            puts("Esse site já foi inserido.");
            printf("Pressione Enter para continuar: ");
            // Eliminar 'Enter' para evitar problemas com futuros inputs
            while(getchar() != '\n')
                ;

            free(conteudo_ficheiro);
            free(nome_site);
            conteudo_ficheiro = NULL;
            nome_site = NULL;

            mostraMenu();
        }
        separar_dados = strtok(NULL, "\n");
        separar_dados = strtok(NULL, " ");
    }
    escreveFicheiroDados(nome_site, nome_utilizador, 
                         encriptaDados(chave_criptografica, palavra_passe));
    printf("Credenciais para o site '%s' foram inseridas com sucesso!\n",
           nome_site);
    printf("Pressione Enter para continuar: ");
    while(getchar() != '\n')
        ;

    free(conteudo_ficheiro);
    free(nome_site);
    conteudo_ficheiro = NULL;
    nome_site = NULL;

    mostraMenu();
}

char* upperDados(char *dados)
{
    char *upper_dados;
    int i = 0;

    upper_dados = (char*)calloc(strlen(dados), sizeof(char));

    // Transformar nome do site em maiusculas 
    while(i < strlen(dados)){
        *(upper_dados + i) = toupper(*(dados + i));
        i++;
    }

    return upper_dados;
}

char* encriptaDados(char* chave_criptografica, char *dados_a_encriptar)
{
    int caractere_encriptado;
    char *dados_encriptados;

    dados_encriptados = (char*)calloc(strlen(dados_a_encriptar), 
                                      sizeof(char));

    for(int x=0; x<strlen(dados_a_encriptar); x++){
        caractere_encriptado = 0;
        caractere_encriptado = *(dados_a_encriptar + x) + *(chave_criptografica + x);
        while(caractere_encriptado >= 127){
            caractere_encriptado -= 127;
            caractere_encriptado += 33;
        }
        // Acrescenta o caractere encriptado 
        strncat(dados_encriptados, (char*)&caractere_encriptado, strlen(dados_a_encriptar));
    }

    return dados_encriptados;
}

char* desencriptaDados(char *chave_criptografica, char *dados_a_desencriptar)
{
    int caractere_desencriptado;
    char *dados_desencriptados;
 
    dados_desencriptados = (char*)calloc(strlen(dados_a_desencriptar), sizeof(char));

    for(int x=0; x<strlen(dados_a_desencriptar); x++){
        caractere_desencriptado = *(dados_a_desencriptar + x) 
                                    - *(chave_criptografica + x);
        while(caractere_desencriptado <= 33){
            caractere_desencriptado += 127;
            caractere_desencriptado -= 33;
        }
        // Acrescenta o caractere encriptado ao fim da array 
        strncat(dados_desencriptados, (char*)&caractere_desencriptado, 
                strlen(dados_a_desencriptar));
    }


    return dados_desencriptados;
}
