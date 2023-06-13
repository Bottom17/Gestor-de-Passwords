#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestorPswd.h"

int numero_execucao = 0;
const int tamanho_dados = 30;
char *chave_criptografica;

void mostraMenu()
{
    int escolha;
    char *site;

    site = (char*)calloc(tamanho_dados + 1, sizeof(char));
    
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
    puts("|             |3| Listar sites inseridos                |");
    puts("|             |4| Sair                                  |");
    puts("|-------------------------------------------------------|");
    printf("O que deseja fazer (1 - 4) ");
    scanf("%d", &escolha);
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;

    if(escolha == 1){
        system("clear");
        mostraProcurar(site);
    }
    else if(escolha == 2){
        system("clear");
        mostraAdicionar(site);
    }
    else if (escolha == 3) {
        system("clear");
        mostraListarSites();
    }
    else{
        system("clear");
        mostraSair();
    }
}

char* mostraIniciar()
{
    char *cripto_encriptada;
    char *mestra;

    // Se o ficheiro ainda nao tiver credenciais
    if (tamanhoFicheiro(ficheiro_dados) == 34) {
        chave_criptografica = geraChaveCriptografica();
        mestra = (char*)calloc(tamanho_chave + 1, sizeof(char));

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
        scanf("%s", mestra);
        // Eliminar 'Enter' para evitar problemas com futuros inputs
        while(getchar() != '\n')
            ;

        verificaChaveMestra(mestra);
        cripto_encriptada = encriptaPasse(mestra);
        escreveFicheiroChave(cripto_encriptada);

        free(chave_criptografica);
        chave_criptografica = NULL;
    }
        
    mestra = (char*)calloc(tamanho_chave + 1, sizeof(char));

    system("clear");
    puts("|-------------------------------------------------------|");
    puts("|               Gestor de palavras-passe                |");
    puts("|-------------------------------------------------------|");
    printf("Insira a sua chave mestra: ");
    scanf("%s", mestra);
    // Eliminar 'Enter' para evitar problemas com futuros inputs
    while(getchar() != '\n')
        ;
    verificaChaveMestra(mestra);
    chave_criptografica = desencriptaChaveCriptografica(mestra);

   return chave_criptografica;
}

void mostraProcurar(char *nome_site)
{
    puts("---------------------------------------------------------");
    puts("         |Procurar credenciais de site existente|        ");
    puts("---------------------------------------------------------");
    printf("Nome do site: ");
    scanf("%s", nome_site);
    // upperNomeSite(nome_site) - input do utilizador transformado 
    // em maiusculas
    while(getchar() != '\n')
        ;
    procuraDados(upperDados(nome_site));
}

void mostraAdicionar(char *nome_site)
{
    char *utilizador;
    char *passe;

    utilizador = (char*)calloc(tamanho_dados, sizeof(char));
    passe = (char*)calloc(tamanho_dados, sizeof(char));

    puts("---------------------------------------------------------");
    puts("                 |Adicionar novo site|                   ");
    puts("---------------------------------------------------------");
    printf("Nome do novo site: ");
    scanf("%s", nome_site);
    printf("Nome de utilizador: ");
    scanf("%s", utilizador);
    printf("Palavra-passe: ");
    scanf("%s", passe);
    while(getchar() != '\n')
        ;
    // upperNomeSite(nome_site) - input do utilizador transformado 
    // em maiusculas
    adicionaDados(upperDados(nome_site), encriptaUtilizador(utilizador), 
                  encriptaPasse(passe));
}

void mostraListarSites()
{
    puts("---------------------------------------------------------");
    puts("                |Listar sites inseridos|                 ");
    puts("---------------------------------------------------------");
    listaSites();
}

void mostraSair()
{
    free(chave_criptografica);
    chave_criptografica = NULL;

    exit(0);
}
