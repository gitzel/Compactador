//
// Created by u18194 on 25/10/2019.
//

#ifndef COMPACTADOR_COMPACTADOR_H
#define COMPACTADOR_COMPACTADOR_H

#include <stdio.h>
#include "Struct.h"

typedef struct {
    inteiro quantosBits;
    char *byte;
}Codigo;

typedef struct {
    No  *raiz;
    Codigo *codigo;
    inteiro qtd;
}Compactador;

static inteiro tamanhoCodigo;

extern void inicieCompactador(Compactador *compactador, No *inicio);
extern inteiro qtdFolhas(Compactador *compactador);
inteiro quantasFolhas(No *atual);
void percorrer(Compactador *compactador, No *atual, char *codigo, inteiro qtd, FILE *arq);
extern void compactarArquivo(Compactador *compactador, FILE *arq, FILE *entrada);
extern void descompactarArquivo(Compactador *compactador, FILE *entrada, FILE *saida);
boolean ehFolha(No *no);
inteiro altura(No *atual);
extern void print(char c);

#endif //COMPACTADOR_COMPACTADOR_H
