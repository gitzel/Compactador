cmake_minimum_required(VERSION 3.14)
project(Compactador C)

set(CMAKE_C_STANDARD 99)

add_executable(Compactador main.c Struct.h FilaPrioridade.h Compactador.h Compactador.c FilaPrioridade.c)