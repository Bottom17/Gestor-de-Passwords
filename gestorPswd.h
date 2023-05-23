#ifndef GESTORPSWD_H
#define GESTORPSWD_H

#include <stdio.h>

/* structures */

/* function prototypes */
void mostraMenu(void); /* gerirMenu.c */
void verificaConta(char *user, char *pswd); /* gerirDados.c */
void criaConta(char *user, char *pswd); 
char * encriptaPasse(char *user, char *pswd);
char * recuperaConteudoFich(void); /* gerirFicheiro.c */
long int tamanhoFicheiro(const char *nome_fich);
void escreveConteudoFich(char *user, char *pswd);

/* global variables */
extern const char *nome_ficheiro; /* gerirFicheiro.c */
extern FILE *ficheiro;

#endif /* GESTORPSWD_H */
