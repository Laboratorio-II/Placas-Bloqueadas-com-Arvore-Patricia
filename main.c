#include <stdio.h>
#include "patricia.h"

int main() {
    int n, q;
    char placa[TAM_PLACA];
    No* raiz = NULL;

    // Placas bloqueadas
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%7s", placa);
        raiz = inserir(raiz, placa);
    }

    // Carros que passam pelo pedágio
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%7s", placa);
        if (buscar(raiz, placa)) {
            printf("%s: BLOQUEADA\n", placa);
        } else {
            printf("%s: LIBERADA\n", placa);
        }
    }

    liberar(raiz);
    return 0;
}
