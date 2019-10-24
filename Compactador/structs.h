#ifndef structs
#define structs
typedef struct No
{
    char      caracter;  // 1byte
    int       frequencia; //4bytes
    struct No *esq, *dir;
} No;

#endif // structs
