#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"

void procuraDados(char *nome_site)
{
    char *conteudo_ficheiro;
    char *separar_dados;
    char *passe_desencriptada;
    char *utilizador_desencriptado;
    
    conteudo_ficheiro = leFicheiro(ficheiro_dados, "r");
    separar_dados = strtok(conteudo_ficheiro, " ");

    // Recuperar o resto dos sites
    while(separar_dados != NULL){
        // Se o nome do site inserido for encontrado
        if(strcmp(separar_dados, nome_site) == 0){
            separar_dados = strtok(NULL, " ");
            utilizador_desencriptado = desencriptaUtilizador(separar_dados);
            printf("Nome de utilizador: %s\n", utilizador_desencriptado);
            separar_dados = strtok(NULL, "\n");
            passe_desencriptada = desencriptaPasse(separar_dados);
            printf("Palavra-passe: %s\n", passe_desencriptada);

            free(conteudo_ficheiro);
            free(passe_desencriptada);
            free(utilizador_desencriptado);
            free(nome_site);
            conteudo_ficheiro = NULL;
            passe_desencriptada = NULL;
            utilizador_desencriptado = NULL;
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

void adicionaDados(char *nome_site, char *utilizador_encriptado, char *passe_encriptada)
{
    char *conteudo_ficheiro;
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
            free(utilizador_encriptado);
            free(passe_encriptada);
            conteudo_ficheiro = NULL;
            nome_site = NULL;
            utilizador_encriptado = NULL;
            passe_encriptada = NULL;

            mostraMenu();
        }
        separar_dados = strtok(NULL, "\n");
        separar_dados = strtok(NULL, " ");
    }
    escreveFicheiroDados(nome_site, utilizador_encriptado, passe_encriptada);
    printf("Credenciais para o site '%s' foram inseridas com sucesso!\n",
           nome_site);
    printf("Pressione Enter para continuar: ");
    while(getchar() != '\n')
        ;

    free(conteudo_ficheiro);
    conteudo_ficheiro = NULL;
    free(nome_site);
    nome_site = NULL;
    printf("nome site: %s\n", nome_site);
    free(utilizador_encriptado);
    utilizador_encriptado = NULL;
    printf("nome utilizador: %s\n", utilizador_encriptado);
    free(passe_encriptada);
    passe_encriptada = NULL;
    printf("passe: %s\n", passe_encriptada);

    mostraMenu();
}

void listaSites()
{
    int linha = 1, numero_site;
    char *conteudo_ficheiro;
    char *separar_dados1, *separar_dados2;
    char *nome_site;

    conteudo_ficheiro = leFicheiro(ficheiro_dados, "r");
    separar_dados1 = strtok(conteudo_ficheiro, " ");
    nome_site = (char*)calloc(tamanho_dados + 1, sizeof(char));

    // Recuperar o resto dos sites
    while(separar_dados1 != NULL){
        separar_dados1 = strtok(NULL, "\n");
        separar_dados1 = strtok(NULL, " ");
        if(separar_dados1 == NULL)
            break;
        printf("|%d| - %s\n", linha, separar_dados1);
        linha++;
    }

    free(conteudo_ficheiro);
    linha = 0;

    conteudo_ficheiro = leFicheiro(ficheiro_dados, "r");
    separar_dados2 = strtok(conteudo_ficheiro, " ");

    printf("Insira o numero do site para o qual deseja visualizar as credenciais: ");
    scanf("%d", &numero_site);
    while (linha != numero_site) {
        separar_dados2 = strtok(NULL, "\n");
        separar_dados2 = strtok(NULL, " ");
        if(separar_dados2 == NULL){
            puts("Esse numero nao esta na lista!");
            break;
        }
        linha++;
    }

    free(conteudo_ficheiro);
    strcpy(nome_site, separar_dados2);
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;
    procuraDados(nome_site);
}

char* upperDados(char *dados)
{
    int i = 0;

    // Transformar nome do site em maiusculas 
    while(i < strlen(dados)){
        // *(upper_dados + i) = toupper(*(dados + i));
        *(dados + i) = toupper(*(dados + i));
        i++;
    }

    return dados;
}

char* encriptaPasse(char *passe_a_encriptar)
{
    int caractere_encriptado, x;
    char *passe_encriptada;

    passe_encriptada = (char*)calloc(strlen(passe_a_encriptar) + 1, 
                                      sizeof(char));

    for(x=0; x<strlen(passe_a_encriptar); x++){
        caractere_encriptado = 0;
        caractere_encriptado = *(passe_a_encriptar + x) + *(chave_criptografica + x);
        while(caractere_encriptado >= 127){
            caractere_encriptado -= 127;
            caractere_encriptado += 33;
        }
        // Acrescenta o caractere encriptado 
        strncat(passe_encriptada, (char*)&caractere_encriptado, strlen(passe_a_encriptar));
    }

    *(passe_encriptada + x) = '\0';

    free(passe_a_encriptar);
    passe_a_encriptar = NULL;

    return passe_encriptada;
}

char* desencriptaPasse(char *passe_a_desencriptar)
{
    int caractere_desencriptado, x;
    char *passe_desencriptada;
 
    passe_desencriptada = (char*)calloc(strlen(passe_a_desencriptar) + 1, 
                                        sizeof(char));

    for(x=0; x<strlen(passe_a_desencriptar); x++){
        caractere_desencriptado = 0;
        caractere_desencriptado = *(passe_a_desencriptar + x) 
                                    - *(chave_criptografica + x);
        while(caractere_desencriptado <= 33){
            caractere_desencriptado += 127;
            caractere_desencriptado -= 33;
        }
        // Acrescenta o caractere encriptado ao fim da array 
        strncat(passe_desencriptada, (char*)&caractere_desencriptado, 
                strlen(passe_a_desencriptar));
    }

    *(passe_desencriptada + x) = '\0';

    return passe_desencriptada;
}

char* encriptaUtilizador(char *utilizador_a_encriptar)
{
    int caractere_encriptado, x;
    char *utilizador_encriptado;

    utilizador_encriptado = (char*)calloc(strlen(utilizador_a_encriptar) + 1, 
                                          sizeof(char));

    for(x=0; x<strlen(utilizador_a_encriptar); x++){
        caractere_encriptado = 0;
        caractere_encriptado = *(utilizador_a_encriptar + x) + 
                                 (8 * strlen(utilizador_a_encriptar));
        while(caractere_encriptado >= 127){
            caractere_encriptado -= 127;
            caractere_encriptado += 33;
        }
        // Acrescenta o caractere encriptado 
        strncat(utilizador_encriptado, (char*)&caractere_encriptado, 
                strlen(utilizador_a_encriptar));
    }

    *(utilizador_encriptado + x) = '\0';

    free(utilizador_a_encriptar);
    utilizador_a_encriptar = NULL;

    return utilizador_encriptado;
}

char *desencriptaUtilizador(char *utilizador_a_desencriptar)
{
    int caractere_desencriptado, x;
    char *utilizador_desencriptado;
 
    utilizador_desencriptado = (char*)calloc(strlen(utilizador_a_desencriptar) + 1, 
                                             sizeof(char));

    for(x=0; x<strlen(utilizador_a_desencriptar); x++){
        caractere_desencriptado = 0;
        caractere_desencriptado = *(utilizador_a_desencriptar + x) - 
                                    (8 * strlen(utilizador_a_desencriptar));
        while (caractere_desencriptado <= 33) {
            caractere_desencriptado += 127;
            caractere_desencriptado -= 33;
        }
        // Acrescenta o caractere encriptado ao fim da array 
        strncat(utilizador_desencriptado, (char*)&caractere_desencriptado, 
                strlen(utilizador_a_desencriptar));
    }

    *(utilizador_desencriptado + x) = '\0';


    return utilizador_desencriptado;
}
