#ifndef PATRICIA_H
#define PATRICIA_H

#define TAM_PLACA 8    // 7 caracteres da placa mais o '\0'
#define NUM_BITS 56    // número de bits de uma placa (7 caracteres de 8 bits)

typedef struct No {
    int folha;              // 1 se o nó é uma folha, 0 se é um nó interno
    int bit;                // nó interno: número do bit testado (de 1 a NUM_BITS)
    char placa[TAM_PLACA];  // folha: placa guardada
    struct No* esq;         // nó interno: caminho quando o bit vale 0
    struct No* dir;         // nó interno: caminho quando o bit vale 1
} No;

int bit(const char* placa, int i);
No* inserir(No* raiz, const char* placa);
int buscar(No* raiz, const char* placa);
void liberar(No* raiz);

#endif
