
#include "structs.h"

typedef struct {
    int  qtd;
    char qual;
    char *codigo;
}Codigo;

typedef struct {
    No  raiz;
    Codigo *codigo;
    int qtd;
}Compactador;

extern void inicieCompactador(Compactador *compactador, No *inicio);
extern void percorrerInOrdem(Compactador *compactador);
extern int qtdFolhas(Compactador *compactador);
int quantasFolhas(No *atual);
void percorrer(Compactador *compactador, No *atual);

