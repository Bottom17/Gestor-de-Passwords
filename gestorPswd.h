#ifndef GESTORPSWD_H
#define GESTORPSWD_H

#include <stdio.h>

// structures

// function prototypes
void mostraMenu(void); /* gerirMenu.c */

void procuraConta(char *nome_site); /* gerirDados.c */
void adicionaConta(char *nome_site, char *nome_utilizador, char *palavra_passe); 
char* upperNomeSite(char *nome_site);
char* encriptaPasse(char *nome_utilizador, char *passe_desencriptada);
char* desencriptaPasse(char *nome_utilizador, char *passe_encriptada);

char* recuperaConteudoFich(void); /* gerirFicheiro.c */
long int tamanhoFicheiro(const char *nome_fich);
void escreveConteudoFich(char *nome_site, char *nome_utilizador, char *palavra_passe);

// global variables
extern const char *nome_ficheiro; /* gerirFicheiro.c */
extern FILE *ficheiro;

#endif /* GESTORPSWD_H */
