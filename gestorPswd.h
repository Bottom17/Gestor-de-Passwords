#ifndef GESTORPSWD_H
#define GESTORPSWD_H

#include <stdio.h>

// structures

// function prototypes
void mostraMenu(void); /* gerirMenu.c */
char* mostraIniciar(void);
void mostraProcurar(char *chave_criptografica);
void mostraAdicionar(char *chave_criptografica);
void mostraSair(char *chave_criptografica);

void procuraDados(char *nome_site, char *chave_criptografica); /* gerirDados.c */
void adicionaDados(char *chave_criptografica,char *nome_site, char *nome_utilizador, char *palavra_passe); 
char* upperDados(char *nome_site);
char* encriptaDados(char *chave_criptografica, char *dados_a_encriptar);
char* desencriptaDados(char *chave_criptografica, char *dados_a_desencriptar);

long int tamanhoFicheiro(const char *nome_fich); /* gerirFicheiro.c */
char* leFicheiro(const char *nome_ficheiro, const char *modo); 
void escreveFicheiroDados(char *nome_site, char *nome_utilizador, 
                         char *passe_encriptada);
void escreveFicheiroChave(char *chave_encriptada);

char* geraChaveCriptografica(void); /* gerirChave.c */
void verificaChaveMestra(char *chave_mestra);
char* desencriptaChaveCriptografica(char *chave_mestra);

// global variables
extern char *chave_criptografica; /* gerirMenu.c */

extern const char *ficheiro_dados; /* gerirFicheiro.c */
extern const char *ficheiro_chave;
extern FILE *ficheiro;

extern const int tamanho_chave; /* gerirChave.c */

#endif /* GESTORPSWD_H */
