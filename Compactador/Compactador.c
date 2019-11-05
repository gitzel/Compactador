//
// Created by u18194 on 25/10/2019.
//

#include "Compactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicieCompactador(Compactador *compactador, No *inicio){
    compactador->raiz = inicio;
    compactador->qtd = 0;
    compactador->codigo = (Codigo*) malloc(255 * sizeof(Codigo));
}

void percorrer(Compactador *compactador, No *atual,  char *codigo, int qtd, FILE *arq){
    if(atual != NULL){
        if(atual->esq != NULL) {
            codigo[qtd] = '0';
            percorrer(compactador, atual->esq, codigo, qtd + 1,arq);
        }
        if(atual->esq == NULL && atual->dir == NULL){
            compactador->codigo[atual->caracter].quantosBits = qtd;
            compactador->codigo[atual->caracter].byte = (char*) malloc(sizeof(char) * qtd);
            int i;
            for(i = 0; i < qtd; i++)
                compactador->codigo[atual->caracter].byte[i] = codigo[i];
            compactador->qtd++;
        }
        if(atual->dir != NULL) {
            codigo[qtd] = '1';
            percorrer(compactador, atual->dir, codigo, qtd + 1, arq);
        }
    }
}


inteiro quantasFolhas(No *noAtual){
    if (noAtual == NULL)
        return 0;

    if (ehFolha(noAtual) == true)
        return 1;

    return quantasFolhas(noAtual->esq) + quantasFolhas(noAtual->dir);
}

inteiro qtdFolhas(Compactador *compactador) {
    return(quantasFolhas(compactador->raiz));
}

boolean ehFolha(No* no){
     if(no->esq == NULL && no->dir == NULL)
        return true;

     return false;
}

void compactarArquivo(Compactador *compactador, FILE *arq, FILE *entrada)
{
    inteiro qtd;
    inteiro qtdAtual = 0;
    char *aux;
    char c;
    unsigned char saida = 0;
    aux = (char*) malloc(sizeof(char) * altura(compactador->raiz));

    percorrer(compactador, compactador->raiz, aux, 0, arq);
    free(aux);

    qtd = compactador->qtd;

    while((c = fgetc(entrada)) != EOF){
        Codigo codigo = compactador->codigo[c];
        int bits = codigo.quantosBits;

        int j;
        int difPra8 = 0;

        if(bits + qtdAtual > 8)
            difPra8 = qtdAtual + bits - 8;

        for(j = 0; j < (bits-difPra8>0?bits - difPra8:difPra8-bits); j++)
        {
            if(codigo.byte[j] == '1')
                saida|= (1u << (7 - (qtdAtual + j)));
        }

        qtdAtual += bits;

        if(qtdAtual >= 8) {
            fwrite(&saida, sizeof(char), 1, arq);
            fflush(arq);
             saida = 0;
            if (qtdAtual == 8)
                qtdAtual = 0;
            else{
                qtdAtual = 0;
                int inicioResto = codigo.quantosBits - difPra8;
                for(j = 0; j < difPra8; j++) {
                    if (codigo.byte[inicioResto + j] == '1')
                        saida |= (1u << (7 - (qtdAtual + j)));
                    if(j == 7)
                    {
                        fwrite(&saida, sizeof(char), 1, arq);
                        fflush(arq);
                        saida = 0;
                        difPra8 -= 8;
                        inicioResto = codigo.quantosBits - difPra8;
                        j = -1;
                    }
                }

                qtdAtual = difPra8;
            }
        }
    }

    inteiro quantosLixos = 0;
    if(qtdAtual != 0) {
        quantosLixos = 8 - qtdAtual;
        fwrite(&saida, sizeof(char), 1, arq);
        fflush(arq);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(&quantosLixos, sizeof(inteiro), 1, arq);
    fwrite(&qtd, sizeof(inteiro), 1, arq);
    fflush(arq);
}


void print(char bits)
{
    /*
    Sabendo que o parametro chamado "bits" tem 32 bits nesta ordem:
    31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    escreva na tela os 0s e 1s que formam o parametro
    */

    for(int c = 7; c >= 0; c--)
        printf("%d", ((((bits >> c) & 1u)? 1: 0)));

    printf("\n");
}

inteiro altura(No *noAtual)
{
    inteiro alturaEsquerda,
            alturaDireita;

    if (noAtual == NULL)
        return 0;

    alturaEsquerda = altura(noAtual->esq);
    alturaDireita  = altura(noAtual->dir);

    if (alturaEsquerda >= alturaDireita)
        return 1 + alturaEsquerda;

    return 1 + alturaDireita;
}