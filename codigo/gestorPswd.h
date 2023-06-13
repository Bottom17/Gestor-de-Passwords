#ifndef GESTORPSWD_H
#define GESTORPSWD_H

#include <stdio.h>

// structures

// function prototypes
void mostraMenu(void); /* gerirMenu.c */
char* mostraIniciar(void);
void mostraProcurar(char *nome_site);
void mostraAdicionar(char *nome_site);
void mostraListarSites(void);
void mostraSair(void);

void procuraDados(char *nome_site); /* gerirDados.c */
void adicionaDados(char *nome_site, char *nome_utilizador, char *palavra_passe); 
void listaSites(void);
char* upperDados(char *nome_site);
char* encriptaPasse(char *passe_a_encriptar);
char* desencriptaPasse(char *passe_a_desencriptar);
char* encriptaUtilizador(char *utilizador_a_encriptar);
char* desencriptaUtilizador(char *utilizador_a_desencriptar);

long int tamanhoFicheiro(const char *nome_ficheiro); /* gerirFicheiro.c */
char* leFicheiro(const char *nome_ficheiro, const char *modo); 
void escreveFicheiroDados(char *nome_site, char *nome_utilizador, 
                         char *passe_encriptada);
void escreveFicheiroChave(char *chave_encriptada);

char* geraChaveCriptografica(void); /* gerirChave.c */
void verificaChaveMestra(char *chave_mestra);
char* desencriptaChaveCriptografica(char *chave_mestra);

// global variables
extern char *chave_criptografica; /* gerirMenu.c */
extern const int tamanho_dados;

extern const char *ficheiro_dados; /* gerirFicheiro.c */
extern const char *ficheiro_chave;
extern FILE *ficheiro;

extern const int tamanho_chave; /* gerirChave.c */

#endif /* GESTORPSWD_H */
