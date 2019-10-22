#include <stdio.h>
#include <stdlib.h>

#include "FilaPrioridade.h"

typedef int inteiro;   // 4bits

typedef enum{
	false, true
}boolean;

int main()
{
    inteiro resposta;
    printf("--> Tratador de Arquivos <--\n\n");
    printf("1 - Compactar\n");
    printf("2 - Descompactar\n");

    resposta = scanf("%d", &resposta);

    switch(resposta)
    {
        case 1: Compactar();break;
    }

    return 0;
}

void Compactar()
{
    FilaPrioridade fila;
    char caminho[100];
    printf("Digite o caminho do arquivo: ");

    scanf("%s", caminho);

    FILE *arq;
    arq = fopen(caminho, "r");

    inicie(&fila, 255);

    while(!feof(arq))
        inserir(&fila, getc(arq));

    ordenar(&fila);

    fclose(arq);
    encerrar(&fila);
}
