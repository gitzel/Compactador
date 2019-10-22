typedef struct No
{
    char      caracter;  // 1byte
    int       frequencia; //4bytes
    struct No *esq, *dir;
} No;

typedef struct {
    int qtd, tamanho;
    No  *vetor;
}FilaPrioridade;

extern void inicie(FilaPrioridade *fila, int tamanho);
extern void inserir(FilaPrioridade *fila, char caracter);
extern int existe(FilaPrioridade *fila, char caracter);
extern void aumentarFrequencia(FilaPrioridade *fila, int posicao);
extern void encerrar();
extern void ordenar(FilaPrioridade *fila);
extern char get(FilaPrioridade *fila, int posicao);
