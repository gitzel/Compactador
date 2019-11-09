/*
 Cabeçalho da biblioteca UserInterface criada para compactar e descompactar arquivos dependendo da opção solicitada pelo Usuário,
 os arquivos que serão compactados terão extensão .ig e os descompactados terão extensão igual a que eram originalmente.
 Autores: Isabela Paulino de Souza e Gustavo Ferreira Gitzel
*/

#ifndef COMPACTADOR_USERINTERFACE_H
#define COMPACTADOR_USERINTERFACE_H

extern void Compactar();
extern void Descompactar();
char* getExtensao(char *arquivo);

#endif //COMPACTADOR_USERINTERFACE_H
