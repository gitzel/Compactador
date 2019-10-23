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

extern void inicie(Compactador *compactador, No inicio);
extern void percorrerInOrdem(Compactador *compactador);
void percorrerInOrdem(Compactador *compactador, No atual);
extern int qtdFolhas(Compactador *compactador);
int qtdFolhas(No atual);
