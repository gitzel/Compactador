/*
  *Implementação da biblioteca Descompactador que armazena uma arvore, onde existem nós para descompactar um arquivo.
  Possui métodos para pegar a quantidade de lixo armazenada no arquivo, e um método para percorrê-lo e descompactá-lo. Além
  de métodos auxiliares como verificar se um nó é folha.
  *Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/

#include "Descompactador.h"
#include <stdio.h>
#include <stdlib.h>


void inicieDescompactador(Descompactador *descompactador, No *inicio){
    descompactador->raiz = inicio;
}

void  setLixo(Descompactador *descompactador, FILE *arq){
    fread(&descompactador->qtdLixo , sizeof(inteiro), 1, arq);
}

boolean isFolha(No* no) {
    if (no->esq == NULL && no->dir == NULL)
        return true;

    return false;
}

void descompactarArquivo(Descompactador *descompactador, FILE *entrada,FILE *saida) {
    No *atual = descompactador->raiz;
    inteiro i;
    inteiro max = 8;
    unsigned char byte;

    long posOriginal = ftell(entrada);

    fseek(entrada,  -1, SEEK_END);      // file, distancia, origem

    long  posFinal = ftell(entrada);

    fseek(entrada, posOriginal - posFinal, SEEK_CUR);

    boolean acabou = false;

    while(!feof(entrada) && acabou == false)
    {
        if(ftell(entrada) == posFinal)
        {
            max = 8 - descompactador->qtdLixo;
            acabou = true;
        }

        fread(&byte, sizeof(unsigned char), 1, entrada);

        for(i = 0; i < max; i++)
        {
            if (byte & (1u << (7 - i)))
                atual = atual->dir;
            else
                atual = atual->esq;

            if(isFolha(atual))
            {
                fprintf(saida, "%c", atual->caracter);
                atual = descompactador->raiz;
            }
        }
    }
}
