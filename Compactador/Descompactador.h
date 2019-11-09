/*
  *Cabeçalho da biblioteca Descompactador que armazena uma arvore, onde existem nós para descompactar um arquivo.
  Possui métodos para pegar a quantidade de lixo armazenada no arquivo, e um método para percorrê-lo e descompactá-lo. Além
  de métodos auxiliares como verificar se um nó é folha.
  *Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/

#ifndef COMPACTADOR_DESCOMPACTADOR_H
#define COMPACTADOR_DESCOMPACTADOR_H

#include <stdio.h>
#include "Struct.h"

typedef struct {
    No  *raiz;
    inteiro  qtdLixo;
}Descompactador;

extern void  setLixo(Descompactador *descompactador, FILE *arq);
extern void inicieDescompactador(Descompactador *descompactador, No *inicio);
extern void descompactarArquivo(Descompactador *descompactador, FILE *entrada, FILE *saida);
boolean isFolha(No *no);

#endif //COMPACTADOR_DESCOMPACTADOR_H
