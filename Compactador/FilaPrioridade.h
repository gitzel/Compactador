/*
 *Cabeçalho da biblioteca Fila de Prioridade que armazena os Nos, onde existe um char para guardar o caracter, uma
 frequencia que guarda quantas vezes ele aparece e dois ponteiros de No que apontam para a esquerda e direita do No atual.
 Possui métodos para incluir, ordenar com base na frequencia, escrever no arquivo, montar uma arvore com base nos nós e sua
 frequência, além de métodos auxiliares ao processo.
 *Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/

#ifndef COMPACTADOR_FILAPRIORIDADE_H
#define COMPACTADOR_FILAPRIORIDADE_H

#include <stdio.h>
#include "Struct.h"

typedef struct {
    inteiro qtd, tamanho;
    No  *vetor;
}FilaPrioridade;

extern void inicieFila(FilaPrioridade *fila, inteiro tamanho);
extern void inserir(FilaPrioridade *fila,unsigned char caracter);
extern void inserirCompactado(FilaPrioridade *fila, unsigned char caracter, inteiro freq);
extern inteiro existe(FilaPrioridade *fila,unsigned char caracter);
extern void aumentarFrequencia(FilaPrioridade *fila, inteiro posicao);
extern void encerrar(FilaPrioridade *fila);
extern void printarFila(FilaPrioridade *, FILE *arq);
extern void ordenar(FilaPrioridade *fila);
extern char get(FilaPrioridade *fila, inteiro posicao);
extern No getRaiz(FilaPrioridade *fila);
extern void converterEmArvore(FilaPrioridade *fila);

#endif //COMPACTADOR_FILAPRIORIDADE_H
