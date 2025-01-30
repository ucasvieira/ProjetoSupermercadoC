// abastecimento.c
#include "supermercado.h"

void inicializar_pilha(Pilha *p) {
    p->topo = -1;
}

int pilha_cheia(Pilha *p) {
    return p->topo == MAX_ITENS - 1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void inserir_produto(Pilha *p, Produto prod) {
    if (pilha_cheia(p)) {
        printf("A prateleira esta cheia.\n");
        return;
    }
    p->itens[++(p->topo)] = prod;
}

Produto retirar_produto(Pilha *p) {
    if (pilha_vazia(p)) {
        printf("A prateleira esta vazia.\n");
        Produto prod = {"", "", 0.0, 0.0}; // Produto vazio
        return prod;
    }
    return p->itens[(p->topo)--];
}

void abastecer_gondola() {
    Pilha gondolas[10];
    for (int i = 0; i < 10; i++) {
        inicializar_pilha(&gondolas[i]);
    }

    Produto produto;
    printf("Digite o nome do produto: ");
    fgets(produto.nome, 100, stdin);
    printf("Digite a descricao: ");
    fgets(produto.descricao, 200, stdin);
    printf("Digite o peso: ");
    scanf("%f", &produto.peso);
    printf("Digite o preco: ");
    scanf("%f", &produto.preco);

    int escolha;
    printf("Escolha a gôndola (0 a 9): ");
    scanf("%d", &escolha);

    if (escolha >= 0 && escolha < 10) {
        inserir_produto(&gondolas[escolha], produto);
    } else {
        printf("Gôndola inválida.\n");
    }
}
