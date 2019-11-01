//
// Created by u18194 on 01/11/2019.
//

#ifndef COMPACTADOR_DESCOMPACTADOR_H
#define COMPACTADOR_DESCOMPACTADOR_H

#include <stdio.h>
#include "Struct.h"

typedef struct {
    No  *raiz;
    inteiro  qtdLixo;
}Descompactador;

extern void  setLixo(Descompactador *descompactador, FILE *arq);
extern void inicieDescompactador(Descompactador *descompactador, No *inicio);
extern void descompactarArquivo(Descompactador *descompactador, FILE *entrada, FILE *saida);
boolean isFolha(No *no);

#endif //COMPACTADOR_DESCOMPACTADOR_H
