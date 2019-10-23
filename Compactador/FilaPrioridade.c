#include "FilaPrioridade.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum{
	false, true
}boolean;

void inserir (FilaPrioridade *fila, char caracter)
{
   int posicao = existe(fila, caracter);

   if(posicao == -1)
   {
       No novoNo;
       novoNo.caracter = caracter;
       novoNo.frequencia = 1;
       fila->vetor[fila->qtd] = novoNo;
       fila->qtd++;
   }else
      aumentarFrequencia(fila, posicao);
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

void inicie(FilaPrioridade *fila, int tamanho)
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
        novoNo.esq = &fila->vetor[0];
        novoNo.dir = &fila->vetor[1];

        for(j = 0; j < fila->qtd - 1; j++)
        {
            if(j + 3 > fila->qtd && alocou == false)
            {
                fila->vetor[j] = novoNo;
                alocou =true;
            }

            else
            if(fila->vetor[j+2].frequencia > novoNo.frequencia && alocou == false){
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
