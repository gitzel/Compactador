//
// Created by u18194 on 25/10/2019.
//

#ifndef COMPACTADOR_FILAPRIORIDADE_H
#define COMPACTADOR_FILAPRIORIDADE_H
#include "Struct.h"

typedef struct {
    int qtd, tamanho;
    No  *vetor;
}FilaPrioridade;

extern void inicieFila(FilaPrioridade *fila, int tamanho);
extern void inserir(FilaPrioridade *fila, char caracter);
extern void inserirCompactado(FilaPrioridade *fila, char caracter, int freq);
extern int existe(FilaPrioridade *fila, char caracter);
extern void aumentarFrequencia(FilaPrioridade *fila, int posicao);
extern void encerrar();
extern void ordenar(FilaPrioridade *fila);
extern char get(FilaPrioridade *fila, int posicao);
extern void converterEmArvore(FilaPrioridade *fila);

#endif //COMPACTADOR_FILAPRIORIDADE_H
