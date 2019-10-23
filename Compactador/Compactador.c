#include "Compactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicie(Compactador *compactador, No inicio){
    compactador->raiz = inicio;
    compactador->qtd = 0;
    compactador->codigo = (Codigo*) malloc(qtdFolhas(inicio) * sizeof(Codigo));
}

void percorrerInOrdem(Compactador *compactador, No atual, int n){
    if(atual){
         percorrerInOrdem(compactador, atual.esq, 0);
         if(atual.esq == NULL && atual.dir == NULL){
             //compactador->codigo[compactador->qtd].codigo = //o codigo que a gente não sabe;
             compactador->codigo[compactador->qtd].qtd = atual.frequencia; //o codigo que a gente não sabe;
             compactador->codigo[compactador->qtd].qual = atual.caracter;//o codigo que a gente não sabe;
             compactador->qtd++;
         }

         percorrerInOrdem(compactador, atual.dir, 1);
    }
}

void percorrerInOrdem(Compactador *compactador){
    percorrerInOrdem(compactador->raiz);
}

int qtdFolhas(No noAtual){
      if (noAtual == NULL)
        return 0;

      if (noAtual.esq == NULL && noAtual.dir == NULL)
        return 1;

      return qtdFolhas(noAtual.esq) +
             qtdFolhas(noAtual.dir);
}

int qtdFolhas(Compactador *compactador) {
        return(qtdFolhas(compactador->raiz));
}

