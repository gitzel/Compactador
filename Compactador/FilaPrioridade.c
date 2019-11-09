/*
  * Implementação da biblioteca Fila de Prioridade que armazena os Nos, onde existe um char para guardar o caracter, uma
  frequencia que guarda quantas vezes ele aparece e dois ponteiros de No que apontam para a esquerda e direita do No atual.
  Possui métodos para incluir, ordenar com base na frequencia, escrever no arquivo, montar uma arvore com base nos nós e sua
  frequência, além de métodos auxiliares ao processo.
  * Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
 */


#include "FilaPrioridade.h"
#include <stdio.h>
#include <stdlib.h>


void inserir (FilaPrioridade *fila, unsigned char caracter)
{
    inteiro posicao = existe(fila, caracter);

    if(posicao == -1)
    {
        No novoNo;
        novoNo.caracter = caracter;
        novoNo.frequencia = 1;
        novoNo.esq = NULL;
        novoNo.dir = NULL;
        fila->vetor[fila->qtd] = novoNo;
        fila->qtd++;
    }else
        aumentarFrequencia(fila, posicao);
}

void inserirCompactado(FilaPrioridade *fila,unsigned char caracter, inteiro frequencia)
{
    No novoNo;
    novoNo.caracter = caracter;
    novoNo.frequencia = frequencia;
    novoNo.esq = NULL;
    novoNo.dir = NULL;
    fila->vetor[fila->qtd] = novoNo;
    fila->qtd++;
}

void printarFila(FilaPrioridade *fila, FILE *arq) {
    for(int i = 0; i < fila->qtd; i++)
    {
        fwrite(&fila->vetor[i].caracter, sizeof(unsigned char), 1, arq);
        fwrite(&fila->vetor[i].frequencia, sizeof(inteiro), 1, arq);
    }
}

void ordenar(FilaPrioridade *fila){
    inteiro min, outer, inner;
    No temp;

    for (outer = 0; outer < fila->qtd; outer++)
    {
        min = outer;

        for (inner = outer + 1; inner < fila->qtd; inner++)
            if (fila->vetor[inner].frequencia < fila->vetor[min].frequencia)
                min = inner;

        if(outer != min)
        {
            temp = fila->vetor[outer];
            fila->vetor[outer] = fila->vetor[min];
            fila->vetor[min] = temp;
        }
    }
}

inteiro existe (FilaPrioridade *fila, unsigned char caracter)
{
    inteiro i;
    for(i =0; i<fila->qtd; i++)
        if(fila->vetor[i].caracter == caracter)
            return i;

    return -1;
}

void aumentarFrequencia (FilaPrioridade *fila, inteiro posicao)
{
    fila->vetor[posicao].frequencia++;
}

void inicieFila(FilaPrioridade *fila, inteiro tamanho)
{
    fila->tamanho = tamanho;
    fila->qtd = 0;
    fila->vetor = (No*) malloc(tamanho * sizeof(No));
}

void encerrar(FilaPrioridade *fila){
    free(fila->vetor);
}

void converterEmArvore(FilaPrioridade *fila){
    inteiro j = 0;
    while(fila->qtd > 1){
        No novoNo;
        boolean alocou = false;
        novoNo.frequencia = fila->vetor[0].frequencia + fila->vetor[1].frequencia;

        novoNo.esq = (No*) malloc(sizeof(No));
        novoNo.esq->caracter = fila->vetor[0].caracter;
        novoNo.esq->frequencia = fila->vetor[0].frequencia;
        novoNo.esq->esq = fila->vetor[0].esq;
        novoNo.esq->dir = fila->vetor[0].dir;

        novoNo.dir = (No*) malloc(sizeof(No));
        novoNo.dir->caracter = fila->vetor[1].caracter;
        novoNo.dir->frequencia = fila->vetor[1].frequencia;
        novoNo.dir->esq = fila->vetor[1].esq;
        novoNo.dir->dir = fila->vetor[1].dir;

        for(j = 0; j < fila->qtd - 1; j++)
        {
            if(j + 3 > fila->qtd && alocou == false)
            {
                fila->vetor[j] = novoNo;
                alocou =true;
            }
            else
            if(fila->vetor[j+2].frequencia > novoNo.frequencia && alocou == false)
            {
                fila->vetor[j] = novoNo;
                alocou = true;
            }
            else if(alocou == true)
                fila->vetor[j] = fila->vetor[j+1];
            else
                fila->vetor[j] = fila->vetor[j+2];
        }
        fila->qtd--;
    }
}

char get(FilaPrioridade *fila, inteiro i)
{
    return fila->vetor[i].caracter;
}

No getRaiz(FilaPrioridade *fila)
{
    return fila->vetor[0];
}
