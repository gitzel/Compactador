/*
 * Arquivo principal para compactar e descompactar arquivos, os arquivos que serão compactados terão extensão .ig
 * Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
 */

#include <stdio.h>
#include <stdlib.h>

#include "UserInterface.h"
#include "Struct.h"

int main()
{
    inteiro resposta;
    printf("--> Tratador de Arquivos <--\n\n");
    printf("1 - Compactar\n");
    printf("2 - Descompactar\n");

    printf("\nDigite a opcao desejada: ");
    scanf("%d", &resposta);

    switch(resposta)
    {
        case 1: Compactar();break;
        case 2: Descompactar();break;
    }

    return 0;
}

