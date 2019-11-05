#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FilaPrioridade.h"
#include "Compactador.h"
#include "Descompactador.h"


void Percorrer(No *atual){
    if(atual != NULL){
        Percorrer(atual->esq);
        printf("%c\n", atual->caracter);
        Percorrer(atual->dir);
    }
}

void Descompactar() {
    inteiro i, qtd, j;

    FilaPrioridade fila;
    Descompactador descompactador;

    char caminho[100], extensao[5], novoArquivo[100];

    FILE *saida, *entrada;

    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);

    entrada = fopen(caminho, "rb");

    inicieFila(&fila, 255);

    setLixo(&descompactador, entrada);

    fread(&qtd, sizeof(inteiro), 1, entrada);

    fread(&extensao, sizeof(char), 5, entrada);

    for(i = 0; i < qtd; i++) {
        char c;
        inteiro freq;
        fread(&c, sizeof(char), 1, entrada);
        fread(&freq, sizeof(inteiro), 1, entrada);
        inserirCompactado(&fila, c, freq);
    }

    for(i =0; i < strlen(caminho); i++){
        novoArquivo[i] = caminho[i];
        if(caminho[i] == '.')
        {
            for(i = i+1, j = 0; i<strlen(caminho); i++)
                novoArquivo[i] = extensao[j];
        }
    }

    saida = fopen(novoArquivo, "wb");

    converterEmArvore(&fila);
    No raiz = getRaiz(&fila);
    inicieDescompactador(&descompactador, &raiz);
    descompactarArquivo(&descompactador, entrada,saida);
    fclose(entrada);
    fclose(saida);
}


void Compactar(){
    inteiro i, j;
    FILE *arq;
    Compactador compactador;
    FilaPrioridade fila;
    char c, caminho[100], extensao[5], novoArquivo[100];

    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);

    for(i =0; i < strlen(caminho); i++){
        novoArquivo[i] = caminho[i];
        if(caminho[i] == '.')
        {
            novoArquivo[i] = '.';
            novoArquivo[i+1] = 'i';
            novoArquivo[i+2] = 'g';
            for(j = 0; i<strlen(caminho); i++)
                extensao[j] = caminho[i];
        }
    }

    arq = fopen(caminho, "rb");

    inicieFila(&fila, 255);

    while((c = fgetc(arq)) != EOF)
        inserir(&fila, c);

    fclose(arq);

    arq = fopen(novoArquivo, "wb");

    ordenar(&fila);
    fwrite(&fila.qtd, sizeof(inteiro), 1, arq);
    fwrite(&fila.qtd, sizeof(inteiro), 1, arq);
    fwrite(&extensao, sizeof(char), 5, arq);

    printarFila(&fila, arq);

    converterEmArvore(&fila);
    No raiz = getRaiz(&fila);
    inicieCompactador(&compactador, &raiz);
    compactarArquivo(&compactador, arq, fopen(caminho, "rb"));
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

