//
// Created by u18194 on 25/10/2019.
//


#include "FilaPrioridade.h"
#include <stdio.h>
#include <stdlib.h>


void inserir (FilaPrioridade *fila, char caracter)
{
    int posicao = existe(fila, caracter);

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

void inserirCompactado(FilaPrioridade *fila, char caracter, int frequencia)
{
    No novoNo;
    novoNo.caracter = caracter;
    novoNo.frequencia = frequencia;
    novoNo.esq = NULL;
    novoNo.dir = NULL;
    fila->vetor[fila->qtd] = novoNo;
    fila->qtd++;
}

void ordenar(FilaPrioridade *fila){
    int min, outer, inner;
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

int existe (FilaPrioridade *fila, char caracter)
{
    int i;
    for(i =0; i<fila->qtd; i++)
        if(fila->vetor[i].caracter == caracter)
            return i;

    return -1;
}

void aumentarFrequencia (FilaPrioridade *fila, int posicao)
{
    fila->vetor[posicao].frequencia++;
}

void inicieFila(FilaPrioridade *fila, int tamanho)
{
    fila->tamanho = tamanho;
    fila->qtd = 0;
    fila->vetor = (No*) malloc(tamanho * sizeof(No));
}

void encerrar(FilaPrioridade *fila){
    free(fila->vetor);
}

void converterEmArvore(FilaPrioridade *fila){
    int j = 0;
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

char get(FilaPrioridade *fila, int i)
{
    return fila->vetor[i].caracter;
}
