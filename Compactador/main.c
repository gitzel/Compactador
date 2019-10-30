#include <stdio.h>
#include <stdlib.h>

#include "FilaPrioridade.h"
#include "Compactador.h"

void Descompactar() {

    FilaPrioridade fila;
    inicieFila(&fila, 255);

    FILE *saida = fopen("C:/temp/descompactado.txt", "wb");

    FILE *entrada;
    entrada = fopen("C:/temp/teste.txt", "rb");
    char c;

    inteiro quantosLixos;
    fread(&quantosLixos, sizeof(inteiro), 1, entrada);

    inteiro qtd;
    fread(&qtd, sizeof(inteiro), 1, entrada);


    inteiro i;
    for(i = 0; i < qtd; i++){
        inteiro freq;
        inteiro quantosBits;
        fread(&c, sizeof(char), 1, entrada);
        fread(&freq, sizeof(inteiro), 1, entrada);
        inserirCompactado(&fila, c, freq);

    }

    ordenar(&fila);
    converterEmArvore(&fila);
    Compactador descompactador;
    inicieCompactador(&descompactador, &fila.vetor[0]);
    descompactarArquivo(&descompactador, entrada,saida);
    fclose(entrada);
    fclose(saida);
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
    inicieCompactador(&comp, &getRaiz(&fila));
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

