#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"


void mostraMenu()
{
    int escolha;
    char escolha_sair;
    char nome_utilizador[20];
    char palavra_passe[20];

    while(escolha_sair != 'S'){
        /* Parte visual do menu */
        puts("--------------------------------");
        puts("    Gestor de palavras-passe    ");
        puts("--------------------------------");
        puts("|1| Conexão a conta existente");
        puts("|2| Criar nova conta");
        printf("O que deseja fazer (1 - 2)? ");
        scanf("%d", &escolha);
        /* Eliminar 'Enter' para evitar problemas com futuros inputs */
        while(getchar() != '\n')
            ;

        putchar('\n');
        /* Conexão a conta existente */
        if(escolha == 1){
            puts("           |Opção nº1|          ");
            puts("--------------------------------");
            printf("Nome de utilizador: ");
            scanf("%s", nome_utilizador);
            printf("Palavra-passe: ");
            scanf("%s", palavra_passe);
            verificaConta(nome_utilizador, palavra_passe);
            break;
        }
        /* Criar nova conta */
        else if(escolha == 2){
            puts("           |Opção nº2|          ");
            puts("--------------------------------");
            printf("Novo nome de utilizador: ");
            scanf("%s", nome_utilizador);
            printf("Nova palavra-passe: ");
            scanf("%s", palavra_passe);
            criaConta(nome_utilizador, palavra_passe);
            break;
        }
        /* Se nenhum dos dois acima */
        else{
            printf("Pretende sair? Se sim insira 'S': ");
            scanf("%c", &escolha_sair);
            escolha_sair = toupper(escolha_sair);  
            if(escolha_sair == 'S')
                exit(1);
        }
    }
}



