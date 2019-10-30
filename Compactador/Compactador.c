//
// Created by u18194 on 25/10/2019.
//

#include "Compactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicieCompactador(Compactador *compactador, No *inicio, FILE *saida){
    compactador->raiz = inicio;
    compactador->saida = saida;
}

void percorrer(Compactador *compactador, No *atual,  char *codigo, inteiro *qtd, inteiro *quantidadeDeUm){
    if(atual != NULL){
        if(*qtd == 8){
            fwrite(codigo, sizeof(char), 1, compactador->saida);
            fflush(compactador->saida);
            *qtd = 0;
            *codigo = 0;
        }

        if(atual->esq != NULL) {
            *qtd = *qtd + 1;
            percorrer(compactador, atual->esq, codigo, qtd, quantidadeDeUm);
        }

        if(atual->dir != NULL) {
            inteiro i;
            *qtd = *qtd + 1;
            *quantidadeDeUm = *quantidadeDeUm + 1;
            if(*quantidadeDeUm > 1)
                for(i = 0; i < *quantidadeDeUm;i++) {
                    *codigo |= (1u << (7 - *qtd - *quantidadeDeUm + i));
                    *qtd = *qtd + 1;
                }
            else
                *codigo |= (1u << (7 - *qtd));



            percorrer(compactador, atual->dir, codigo,  qtd, quantidadeDeUm);
            *quantidadeDeUm = *quantidadeDeUm - 1;

        }

    }
}

void printarArvore(Compactador *compactador, No *noAtual){
    if(noAtual != NULL)
    {
        printarArvore(compactador,noAtual->esq);
        fwrite(&noAtual->caracter,   sizeof(char), 1, compactador->saida);
        fwrite(&noAtual->frequencia, sizeof(inteiro), 1, compactador->saida);
        printarArvore(compactador, noAtual->dir);
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

void compactarArquivo(Compactador *compactador, FILE *arq)
{
    inteiro qtd = quantasFolhas(compactador->raiz);
    inteiro qtdLixo= 0;
    char codigo = 0;
    inteiro auxQtd = 0;

    fwrite(&qtd, sizeof(inteiro), 1, arq);
    fwrite(&qtd, sizeof(inteiro), 1, arq);

    printarArvore(compactador, compactador->raiz);

    inteiro  qtd1 = 0;
    percorrer(compactador, compactador->raiz, &codigo, &auxQtd, &qtd1);

    qtdLixo = 8 - auxQtd;

    if(auxQtd != 0) {
        fwrite(&codigo, sizeof(char), 1, arq);
        fflush(arq);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(&qtdLixo, sizeof(inteiro), 1, arq);
    fflush(arq);
}



void descompactarArquivo(Compactador *compactador, FILE *entrada,FILE *arq) {
    No *anterior = NULL;
    No *atual = compactador->raiz;
    while(!feof(entrada))
    {
        char byte;
        fread(&byte, sizeof(char), 1, entrada);
        inteiro i;
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
