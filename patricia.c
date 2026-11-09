#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

// Retorna o bit i da placa, contando da esquerda para a direita a partir de 1.
// Os bits 1 a 8 são do primeiro caractere, os bits 9 a 16 do segundo, e assim por diante.
int bit(const char* placa, int i) {
    unsigned char c = (unsigned char)placa[(i - 1) / 8];
    return (c >> (7 - (i - 1) % 8)) & 1;
}

static No* criar_folha(const char* placa) {
    No* no = (No*)malloc(sizeof(No));
    no->folha = 1;
    no->bit = 0;
    strcpy(no->placa, placa);
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

static No* criar_interno(int b, No* esq, No* dir) {
    No* no = (No*)malloc(sizeof(No));
    no->folha = 0;
    no->bit = b;
    no->placa[0] = '\0';
    no->esq = esq;
    no->dir = dir;
    return no;
}

// Coloca na subárvore um nó interno que testa o bit b, com a nova placa de um lado
static No* inserir_no_bit(No* no, const char* placa, int b) {
    // O nó que testa o bit b fica acima de nós que testam bits maiores
    if (no->folha || b < no->bit) {
        No* nova = criar_folha(placa);
        if (bit(placa, b) == 0) {
            return criar_interno(b, nova, no);
        }
        return criar_interno(b, no, nova);
    }
    if (bit(placa, no->bit) == 0) {
        no->esq = inserir_no_bit(no->esq, placa, b);
    } else {
        no->dir = inserir_no_bit(no->dir, placa, b);
    }
    return no;
}

No* inserir(No* raiz, const char* placa) {
    if (raiz == NULL) {
        return criar_folha(placa);
    }

    // Desce até uma folha seguindo os bits da placa
    No* atual = raiz;
    while (!atual->folha) {
        if (bit(placa, atual->bit) == 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    // Primeiro bit em que a placa nova e a placa da folha são diferentes
    int b = 1;
    while (b <= NUM_BITS && bit(placa, b) == bit(atual->placa, b)) {
        b++;
    }
    if (b > NUM_BITS) {
        return raiz;   // a placa já está na árvore
    }
    return inserir_no_bit(raiz, placa, b);
}

// Retorna 1 se a placa está na árvore e 0 caso contrário
int buscar(No* raiz, const char* placa) {
    // Implemente aqui
    return 0;
}

void liberar(No* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}
