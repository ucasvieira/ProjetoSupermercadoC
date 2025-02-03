// main.c
#include <stdio.h>
#include "supermercado.h"

int main() {
    if (!login()) return 1;

    inicializar_gondolas();
    inicializar_pdv();

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Abastecer gondolas\n");
        printf("2. Adicionar ao carrinho\n");
        printf("3. Processar compras\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                abastecer_gondola();
            break;
            case 2:
                adicionar_ao_carrinho();
            break;
            case 3:
                processar_pdv();
            break;
            case 0:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}