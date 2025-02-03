// pdv.c
#include "supermercado.h"

Fila fila_pdv;
Pilha carrinho;

void inicializar_pdv() {
    inicializar_fila(&fila_pdv);
    inicializar_pilha(&carrinho);
}

void adicionar_ao_carrinho() {
    int num_gondola;
    printf("Numero da gondola (0-9): ");
    scanf("%d", &num_gondola);
    getchar();

    Produto p = retirar_produto(&gondolas[num_gondola]);
    if (strlen(p.nome) == 0) return;

    inserir_produto(&carrinho, p);
    printf("Produto adicionado ao carrinho!\n");
}

void processar_pdv() {
    while (!pilha_vazia(&carrinho)) {
        Produto p = retirar_produto(&carrinho);
        adicionar_na_fila(&fila_pdv, p);
    }
    gerar_cupom_fiscal(&fila_pdv);
}

// Implementações da fila
void inicializar_fila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
}

int fila_cheia(Fila *f) {
    return (f->tras + 1) % MAX_PRODUTOS == f->frente;
}

int fila_vazia(Fila *f) {
    return f->tras < f->frente;
}

void adicionar_na_fila(Fila *f, Produto prod) {
    if (fila_cheia(f)) {
        printf("Erro: Esteira cheia!\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX_PRODUTOS;
    f->produtos[f->tras] = prod;
}

Produto remover_da_fila(Fila *f) {
    if (fila_vazia(f)) {
        printf("Erro: Esteira vazia!\n");
        Produto vazio = {"", "", 0, 0};
        return vazio;
    }
    Produto p = f->produtos[f->frente];
    f->frente = (f->frente + 1) % MAX_PRODUTOS;
    return p;
}

void gerar_cupom_fiscal(Fila *f) {
    float total = 0;
    printf("\n=== CUPOM FISCAL ===\n");
    while (!fila_vazia(f)) {
        Produto p = remover_da_fila(f);
        printf("%s - %s\n", p.nome, p.descricao);
        printf("Peso: %.2fkg | Preco: R$%.2f\n\n", p.peso, p.preco);
        total += p.preco;
    }
    printf("Total a pagar: R$%.2f\n", total);
}