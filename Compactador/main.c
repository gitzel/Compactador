#include <stdio.h>
#include <stdlib.h>

#include "FilaPrioridade.h"
#include "Compactador.h"

void Descompactar() {

    FilaPrioridade fila;
    inicieFila(&fila, 255);

    FILE *arq;
    arq = fopen("C:/temp/teste.txt", "rb");
    char c;

    int quantosLixos;
    fread(&quantosLixos, sizeof(int), 1, arq);
    fflush(arq);
    printf("%d\n", quantosLixos);
    int qtd;
    fread(&qtd, sizeof(int), 1, arq);
    fflush(arq);
    printf("%d", qtd);
/*
    int i;
    for(i = 0; i < qtd; i++){
        int freq;
        int quantosBits;
        fread(&c, sizeof(char), 1, arq);
        fread(&freq, sizeof(int), 1, arq);
        fread(&quantosBits, sizeof(int), 1, arq);
        inserirCompactado(&fila, c, freq);
    }

    for(i = 0; i < qtd; i++){

    }
    ordenar(&fila);*/

    fclose(arq);
}


void Compactar()
{
    Compactador comp;
    FilaPrioridade fila;
    char c;
    char caminho[100];

    printf("Digite o caminho do arquivo: ");

    scanf("%s", caminho);

    FILE *arq;
    arq = fopen(caminho, "r");

    inicieFila(&fila, 255);

    while((c = fgetc(arq)) != EOF)
        inserir(&fila, c);

    ordenar(&fila);

    converterEmArvore(&fila);
    inicieCompactador(&comp, &fila.vetor[0]);
    percorrerInOrdem(&comp);
    printf("aaaaaa");
    fclose(arq);
    arq = fopen("C:/temp/teste.txt", "wb");
    compactarArquivo(&comp, arq);
    fclose(arq);
    encerrar(&fila);
}


int main()
{
    inteiro resposta;
    printf("--> Tratador de Arquivos <--\n\n");
    printf("1 - Compactar\n");
    printf("2 - Descompactar\n");

    scanf("%d", &resposta);

    switch(resposta)
    {
        case 1: Compactar();break;
        case 2: Descompactar();break;
    }

    return 0;
}

