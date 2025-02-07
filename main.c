// main.c
#include <stdio.h>
#include "supermercado.h"


int main() {
    // Solicitar credenciais
    char nome[100], prontuario[15];
    printf("\n=== LOGIN ===\n");
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Prontuario: ");
    fgets(prontuario, sizeof(prontuario), stdin);
    prontuario[strcspn(prontuario, "\n")] = '\0';
    if (!login(nome, prontuario)) return 1;


    int opcao;
    do {
        inicializar_pdv();
        carregar_gondolas();
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Caixa/PDV\n");
        if (usuario_logado.tipo == ADMIN) {
            printf("2. Abastecer gondolas\n");
            printf("3. Gerenciar usuarios\n");
        }
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                menu_pdv();
            break;
            case 2:
                if (usuario_logado.tipo == ADMIN) {
                    menu_gondolas();
                } else {
                    printf("Opcao invalida!\n");
                }
            break;
            case 3:
                if (usuario_logado.tipo == ADMIN) {
                    gerenciar_usuarios();
                } else {
                    printf("Opcao invalida!\n");
                }
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