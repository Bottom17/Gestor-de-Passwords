#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"

int numero_execucao = 0;
char *chave_criptografica;

void mostraMenu()
{
    int escolha;
    
    if(numero_execucao == 0){
        chave_criptografica = mostraIniciar();
        numero_execucao++;
    }

    system("clear");
    puts("|-------------------------------------------------------|");
    puts("|               Gestor de palavras-passe                |");
    puts("|-------------------------------------------------------|");
    puts("|             |1| Conexão a conta existente             |");
    puts("|             |2| Criar nova conta                      |");
    puts("|             |3| Sair                                  |");
    puts("|-------------------------------------------------------|");
    printf("O que deseja fazer (1 - 3)? ");
    scanf("%d", &escolha);
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;

    if(escolha == 1){
        mostraProcurar(chave_criptografica);
    }
    else if(escolha == 2){
        mostraAdicionar(chave_criptografica);
    }
    else{
        mostraSair(chave_criptografica);
    }
}

char* mostraIniciar()
{
    char *chave_criptografica_encriptada;
    char *chave_mestra;

    chave_mestra = (char*)calloc(tamanho_chave, sizeof(char));

    // Se o ficheiro ainda nao tiver credenciais
    if (tamanhoFicheiro(ficheiro_dados) == 34) {
        chave_criptografica = geraChaveCriptografica();

        system("clear");
        puts("|-------------------------------------------------------|");
        puts("|               Gestor de palavras-passe                |");
        puts("|-------------------------------------------------------|");
        puts("|              LEIA COM ATENCAO POR FAVOR!              |");
        puts("|-------------------------------------------------------|");
        puts("| PARA DIFICULTAR O ACESSO DE TERCEIROS AOS SEUS DADOS  |");
        puts("|  VAI TER DE DIGITAR UMA CHAVE MESTRA COM A QUAL VAI   |");
        puts("|        CONSEGUIR ACEDER OS DADOS ARMAZENADOS!!        |");
        puts("|  ARMAZENE ESTA PALAVRA-PASSE NUM SITIO MUITO SEGURO!  |");
        puts("|-------------------------------------------------------|");
        puts("|           REQUIRIMENTOS PARA CHAVE MESTRA:            |");
        puts("|               NUMERO DE CARACTERES: 15                |");
        puts("|          CARACTERES MAIUSCULOS: NO MINIMO 1           |");
        puts("|           CARACTERES ESPECIAIS: NO MINIMO 1           |");
        puts("|                 DIGITOS: NO MINIMO 1                  |");
        puts("|-------------------------------------------------------|");
        printf("Insira a nova chave mestra: ");
        scanf("%s", chave_mestra);
        // Eliminar 'Enter' para evitar problemas com futuros inputs
        while(getchar() != '\n')
            ;

        verificaChaveMestra(chave_mestra);
        chave_criptografica_encriptada = encriptaDados(chave_criptografica, 
                                                       chave_mestra);
        escreveFicheiroChave(chave_criptografica_encriptada);

        free(chave_criptografica);
        chave_criptografica = NULL;
    }
        
    system("clear");
    puts("|-------------------------------------------------------|");
    puts("|               Gestor de palavras-passe                |");
    puts("|-------------------------------------------------------|");
    printf("Insira a sua chave mestra: ");
    scanf("%s", chave_mestra);
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;
    verificaChaveMestra(chave_mestra);
    chave_criptografica = desencriptaChaveCriptografica(chave_mestra);

   return chave_criptografica;
}

void mostraProcurar(char *chave_criptografica)
{
    char nome_site[40];

    system("clear");
    puts("---------------------------------------------------------");
    puts("               |Conexão a conta existente|               ");
    puts("---------------------------------------------------------");
    printf("Nome do site: ");
    scanf("%s", nome_site);
    // upperNomeSite(nome_site) - input do utilizador transformado 
    // em maiusculas
    while(getchar() != '\n')
        ;
    procuraDados(upperDados(nome_site), chave_criptografica);
}

void mostraAdicionar(char *chave_criptografica)
{
    char nome_site[40];
    char nome_utilizador[40];
    char palavra_passe[40];

    system("clear");
    puts("---------------------------------------------------------");
    puts("                   |Criar nova conta|                    ");
    puts("---------------------------------------------------------");
    printf("Novo site: ");
    scanf("%s", nome_site);
    printf("Nome de utilizador: ");
    scanf("%s", nome_utilizador);
    printf("Palavra-passe: ");
    scanf("%s", palavra_passe);
    while(getchar() != '\n')
        ;
    // upperNomeSite(nome_site) - input do utilizador transformado 
    // em maiusculas
    adicionaDados(chave_criptografica, upperDados(nome_site), nome_utilizador, 
                  palavra_passe);

    printf("%s\n", chave_criptografica);
    while(getchar() != '\n')
        ;

    mostraMenu();
}

void mostraSair(char *chave_criptografica)
{
    char escolha_sair;

    system("clear");
    puts("---------------------------------------------------------");
    puts("                         |Sair|                          ");
    puts("---------------------------------------------------------");
    printf("Pretende sair? Se sim insira 'S': ");
    scanf("%c", &escolha_sair);

    escolha_sair = toupper(escolha_sair);  
    if(escolha_sair == 'S'){
        free(chave_criptografica);
        chave_criptografica = NULL;

        exit(1);
    }
}
