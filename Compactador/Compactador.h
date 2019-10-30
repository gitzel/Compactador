//
// Created by u18194 on 25/10/2019.
//

#ifndef COMPACTADOR_COMPACTADOR_H
#define COMPACTADOR_COMPACTADOR_H

#include <stdio.h>
#include "Struct.h"

typedef struct {
    int quantosBits;
    int  freq;
    char qual;
    char *codigo;
}Codigo;

typedef struct {
    No  *raiz;
    Codigo *codigo;
    int qtd;
}Compactador;

static int tamanhoCodigo;

extern void inicieCompactador(Compactador *compactador, No *inicio);
extern void percorrerInOrdem(Compactador *compactador);
extern int qtdFolhas(Compactador *compactador);
int quantasFolhas(No *atual);
void percorrer(Compactador *compactador, No *atual, char codigo[], int qtd);
extern void compactarArquivo(Compactador *compactador, FILE *arq);
extern void descompactarArquivo(Compactador *compactador, FILE *entrada, FILE *saida);
#endif //COMPACTADOR_COMPACTADOR_H
