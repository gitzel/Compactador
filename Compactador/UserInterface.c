/*
 Implementação da biblioteca UserInterface criada para compactar e descompactar arquivos dependendo da opção solicitada pelo
 Usuário, os arquivos que serão compactados terão extensão .ig e os descompactados terão extensão igual a que eram originalmente.
 Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/
#include "UserInterface.h"
#include "FilaPrioridade.h"
#include "Descompactador.h"
#include "Compactador.h"
#include "String.h"
#include <stdlib.h>
#include "stdio.h"

extern void Compactar(){
    inteiro i, j;
    FILE *entrada, *saida;
    Compactador compactador;
    FilaPrioridade fila;
    unsigned char c, arqEntrada[100],aux[100], *arqSaida, *extensao;

    printf("Digite o caminho do arquivo: ");
    scanf("%s", arqEntrada);

    entrada = fopen(arqEntrada, "rb");

    extensao = getExtensao(arqEntrada);
    strcpy(aux, arqEntrada);
    arqSaida = strcat(strtok(aux, "."), ".ig");

    if(!entrada)
        printf("Arquivo nao encontrado!\n");
    else {
        inicieFila(&fila, 256);

        while (fread(&c, sizeof(unsigned char), 1, entrada) && c != EOF)
            inserir(&fila, c);

        saida = fopen(arqSaida, "wb");

        ordenar(&fila);
        fwrite(&fila.qtd, sizeof(inteiro), 1, saida);
        fwrite(&fila.qtd, sizeof(inteiro), 1, saida);
        inteiro tam = strlen(extensao);
        fwrite(&tam, sizeof(inteiro), 1, saida);
        fwrite(extensao, sizeof(unsigned char) * tam, 1, saida);

        printarFila(&fila, saida);

        converterEmArvore(&fila);
        No raiz = getRaiz(&fila);
        inicieCompactador(&compactador, &raiz);
        rewind(entrada);
        compactarArquivo(&compactador, saida, entrada);
        fclose(saida);
        fclose(entrada);
        encerrar(&fila);
        printf("Arquivo compactado com sucesso!\n");

    }
}

extern void  Descompactar(){
    inteiro i, qtd, j;

    FilaPrioridade fila;
    Descompactador descompactador;

    unsigned char caminho[100], *extensao, arqSaida[100];

    FILE *saida, *entrada;

    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);

    entrada = fopen(caminho, "rb");

    if(!entrada)
        printf("Arquivo nao encontrado!\n");
    else
    {
        inicieFila(&fila, 255);

        setLixo(&descompactador, entrada);

        fread(&qtd, sizeof(inteiro), 1, entrada);
        inteiro tamExtensao;
        fread(&tamExtensao, sizeof(inteiro), 1, entrada);
        extensao = (char*) malloc(sizeof(char) * tamExtensao);
        fread(extensao, sizeof(unsigned char) * tamExtensao, 1, entrada);

        for (i = 0; i < qtd; i++) {
            unsigned char c;
            inteiro freq;
            fread(&c, sizeof(unsigned char), 1, entrada);
            fread(&freq, sizeof(inteiro), 1, entrada);
            inserirCompactado(&fila, c, freq);
        }

        for(i = 0; i < strlen(caminho); i++)
        {
            if(caminho[i] == '.')
                break;

            arqSaida[i] = caminho[i];
        }
        int j;
        arqSaida[i++] = '.';
        for(j = 0; j < tamExtensao; j++, i++) {
            arqSaida[i] = extensao[j];
        }
        arqSaida[i] = '\0';



        saida = fopen(arqSaida, "wb");

        converterEmArvore(&fila);
        No raiz = getRaiz(&fila);
        inicieDescompactador(&descompactador, &raiz);
        descompactarArquivo(&descompactador, entrada, saida);
        fclose(entrada);
        fclose(saida);
        printf("Arquivo descompactado com sucesso!\n");
    }
}

char* getExtensao(char* arquivo){
    char *dot = strrchr(arquivo, '.');
    if (!dot || dot == arquivo)
        return "";
    return dot + 1;
}

