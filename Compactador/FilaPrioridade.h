#include "structs.h"

typedef struct {
    int qtd, tamanho;
    No  *vetor;
}FilaPrioridade;

extern void inicieFila(FilaPrioridade *fila, int tamanho);
extern void inserir(FilaPrioridade *fila, char caracter);
extern int existe(FilaPrioridade *fila, char caracter);
extern void aumentarFrequencia(FilaPrioridade *fila, int posicao);
extern void encerrar();
extern void ordenar(FilaPrioridade *fila);
extern char get(FilaPrioridade *fila, int posicao);
