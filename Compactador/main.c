#include <stdio.h>
#include <stdlib.h>

#include "FilaPrioridade.h"

#define  inteiro int    // 4bits

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

    char caminho[100];
    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);
    printf("%s", caminho);

    FILE *arq;
    arq = fopen(caminho, "r");

    while(!feof(arq))
    {
        No *novoNo;
        novoNo->caracter = getc(arq);
        novoNo->frequencia =
    }

}
