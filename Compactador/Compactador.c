#include "Compactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicieCompactador(Compactador *compactador, No *inicio){
    compactador->raiz = *inicio;
    compactador->qtd = 0;
    compactador->codigo = (Codigo*) malloc(quantasFolhas(inicio) * sizeof(Codigo));
}

void percorrer(Compactador *compactador, No *atual){
    if(atual != NULL){
         percorrer(compactador, atual->esq);
         if(atual->esq == NULL && atual->dir == NULL){
             //compactador->codigo[compactador->qtd].codigo = //o codigo que a gente não sabe;
             compactador->codigo[compactador->qtd].qtd = atual->frequencia; //o codigo que a gente não sabe;
             compactador->codigo[compactador->qtd].qual = atual->caracter;//o codigo que a gente não sabe;
             compactador->qtd++;
         }

         percorrer(compactador, atual->dir);
    }
}

void percorrerInOrdem(Compactador *compactador){
    percorrer(&compactador, &compactador->raiz);
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

