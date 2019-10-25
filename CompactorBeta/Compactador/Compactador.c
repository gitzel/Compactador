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

void percorrer(Compactador *compactador, No *atual,  char *codigo, int qtd){
    if(atual != NULL){
        if(atual->esq != NULL) {
            int aux = qtd;
            codigo[aux] = '0';
            aux++;
            percorrer(compactador, atual->esq, codigo,  aux);
        }
        if(atual->esq == NULL && atual->dir == NULL){
            compactador->codigo[compactador->qtd].qtd = atual->frequencia; //o codigo que a gente não sabe;
            compactador->codigo[compactador->qtd].qual = atual->caracter;//o codigo que a gente não sabe;
            compactador->qtd++;
            compactador->codigo[compactador->qtd].codigo = codigo;
            printf("char = %c freq = %d codigo =",atual->caracter,atual->frequencia);
        }
        if(atual->dir != NULL) {
            int aux = qtd;
            codigo[aux] = '1';
            aux++;
            percorrer(compactador, atual->dir, codigo, aux);
        }
    }
}

void percorrerInOrdem(Compactador *compactador){
    char *codigo;
    codigo = (char*) malloc(sizeof(char) * tamanhoCodigo);
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

