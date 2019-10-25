//
// Created by u18194 on 25/10/2019.
//

#ifndef COMPACTADOR_STRUCT_H
#define COMPACTADOR_STRUCT_H
typedef struct No
{
    char      caracter;  // 1byte
    int       frequencia; //4bytes
    struct No *esq, *dir;
} No;

#endif //COMPACTADOR_STRUCT_H
