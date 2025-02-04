#include "supermercado.h"

void adicionar_ao_carrinho() {
    if(usuario_logado.tipo == ADMIN) {
        printf("Acesso negado! Clientes apenas.\n");
        return;
    }

    int num_gondola;
    printf("Numero da gondola (0-9): ");
    scanf("%d", &num_gondola);
    getchar();

    if(num_gondola < 0 || num_gondola >= MAX_PRODUTOS) {
        printf("Gondola invalida!\n");
        return;
    }

    Produto p = retirar_produto(&gondolas[num_gondola]);
    if(strlen(p.nome) > 0) {
        inserir_produto(&carrinho, p);
        printf("Produto adicionado ao carrinho!\n");
    }
}

void mostrar_carrinho() {
    printf("\n=== CARRINHO DE COMPRAS ===\n");
    if(pilha_vazia(&carrinho)) {
        printf("Carrinho vazio!\n");
        return;
    }

    for(int i = carrinho.topo; i >= 0; i--) {
        printf("%d. %s - R$%.2f\n",
              carrinho.topo - i + 1,
              carrinho.itens[i].nome,
              carrinho.itens[i].preco);
    }
}