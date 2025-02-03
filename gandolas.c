// gondolas.c
#include "supermercado.h"

Pilha gondolas[MAX_PRODUTOS]; // 10 pilhas

void inicializar_pilha(Pilha *p) {
    p->topo = -1;
}

void inicializar_gondolas() {
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        inicializar_pilha(&gondolas[i]);
    }
}

void abastecer_gondola() {
    int num_gondola;
    printf("\nNumero da gondola (0-9): ");
    scanf("%d", &num_gondola);
    getchar(); // Limpar buffer

    if (num_gondola < 0 || num_gondola >= MAX_PRODUTOS) {
        printf("Gondola invalida!\n");
        return;
    }

    Produto p;
    printf("Nome: ");
    fgets(p.nome, 100, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Descricao: ");
    fgets(p.descricao, 200, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0';

    printf("Peso: ");
    scanf("%f", &p.peso);

    printf("Preco: ");
    scanf("%f", &p.preco);
    getchar();

    inserir_produto(&gondolas[num_gondola], p);
}

// Implementações das funções da pilha


int pilha_cheia(Pilha *p) {
    return p->topo == MAX_ITENS - 1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void inserir_produto(Pilha *p, Produto prod) {
    if (pilha_cheia(p)) {
        printf("Erro: Gondola cheia!\n");
        return;
    }
    p->itens[++p->topo] = prod;
}

Produto retirar_produto(Pilha *p) {
    if (pilha_vazia(p)) {
        printf("Erro: Gondola vazia!\n");
        Produto vazio = {"", "", 0, 0};
        return vazio;
    }
    return p->itens[p->topo--];
}