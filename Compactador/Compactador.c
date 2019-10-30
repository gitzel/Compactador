//
// Created by u18194 on 25/10/2019.
//

#include "Compactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicieCompactador(Compactador *compactador, No *inicio){
    tamanhoCodigo =quantasFolhas(inicio);
    compactador->raiz = inicio;
    compactador->qtd = 0;
    compactador->codigo = (Codigo*) malloc(tamanhoCodigo * sizeof(Codigo));

}

void percorrer(Compactador *compactador, No *atual,  char codigo[], int qtd){
    if(atual != NULL){
        if(atual->esq != NULL) {
            codigo[qtd] = '0';
            percorrer(compactador, atual->esq, codigo,  qtd + 1);
        }
        if(atual->esq == NULL && atual->dir == NULL){
            compactador->codigo[compactador->qtd].freq = atual->frequencia; //o codigo que a gente não sabe;
            compactador->codigo[compactador->qtd].qual = atual->caracter;//o codigo que a gente não sabe;
            compactador->codigo[compactador->qtd].quantosBits = qtd;
            compactador->codigo[compactador->qtd].codigo = codigo;
            compactador->qtd++;
            printf("char = %c freq = %d codigo = %s\n",atual->caracter,atual->frequencia, codigo);
        }
        if(atual->dir != NULL) {
            codigo[qtd] = '1';
            percorrer(compactador, atual->dir, codigo, qtd + 1);
        }
    }
}

void percorrerInOrdem(Compactador *compactador){
    char codigo[8];
    percorrer(compactador, compactador->raiz, codigo, 0);
}

int quantasFolhas(No *noAtual){
    if (noAtual == NULL)
        return 0;

    if (noAtual->esq == NULL && noAtual->dir == NULL)
        return 1;

    return quantasFolhas(noAtual->esq) + quantasFolhas(noAtual->dir);
}

int qtdFolhas(Compactador *compactador) {
    return(quantasFolhas(&compactador->raiz));
}


void compactarArquivo(Compactador *compactador, FILE *arq)
{
    int i;
    int qtd = compactador->qtd;
    int quantosBits = 0;
    char byte;

    fwrite(&qtd, sizeof(int), 1, arq);
    fwrite(&qtd, sizeof(int), 1, arq);

   for(i = 0; i < qtd; i++)
    {
        Codigo codigo = compactador->codigo[i];
        fwrite(&codigo.qual, sizeof(char), 1, arq);
        fwrite(&codigo.freq, sizeof(int), 1, arq);
    }

    for(i = 0; i < qtd; i++)
    {
        Codigo codigo = compactador->codigo[i];
        int bits = codigo.quantosBits;

        int j;
        int difPra8 = 0;

        if(bits + quantosBits > 8)
            difPra8 = bits - 8;


        for(j = 0; j < bits - difPra8; j++)
            byte[j + quantosBits] = codigo.codigo[j];

        quantosBits += bits;

        if(quantosBits >= 8) {
            fwrite(byte, sizeof(char), 8, arq);
            fflush(arq);
            if (quantosBits == 8)
                quantosBits = 0;
            else
            {
                for(j = 0; j < difPra8; j++)
                    byte[j] = codigo.codigo[7 + j];
                quantosBits = difPra8;
            }
        }
    }

    int quantosLixos = 0;
    if(quantosBits != 0) {
        quantosBits = 8 - quantosBits;
        fwrite(byte, sizeof(char), 8, arq);
        fflush(arq);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(&quantosLixos, sizeof(int), 1, arq);
    fflush(arq);

}

void descompactarArquivo(Compactador *compactador, FILE *entrada,FILE *arq) {
    No *anterior = NULL;
    No *atual = compactador->raiz;
    while(!feof(entrada))
    {
        char byte;
        fread(&byte, sizeof(char), 1, entrada);
        int i;
        for(i = 0; i < 8; i++)
        {
            if(atual->esq == NULL && atual->dir == NULL)
            {
                //achou char
            }
            else
            if(byte & (1 << (7 - i)))
            {
                if(atual->esq != NULL)
                {
                    anterior = atual;
                    atual = atual->esq;
                }
                else
                {
                    atual = anterior;
                }
            }
            else
            {
                // é 0
            }

        }
        // para cada bit, ver se é 0(esq) ou 1(dir); é folha? achou o char e escreve freq vezes
    }
}