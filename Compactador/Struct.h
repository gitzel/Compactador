/*
 * Biblioteca que define os tipos inteiro(int), boolean e No.
 * Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/

#ifndef COMPACTADOR_STRUCT_H
#define COMPACTADOR_STRUCT_H

typedef int inteiro;   // 4bits

typedef enum{
    false, true
}boolean;

typedef struct No
{
    unsigned char  caracter;  // 1byte
    inteiro       frequencia; //4bytes
    struct No *esq, *dir;
} No;

#endif //COMPACTADOR_STRUCT_H
