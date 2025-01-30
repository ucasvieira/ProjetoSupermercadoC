// pdv.c
#include "supermercado.h"

void inicializar_fila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
}

int fila_cheia(Fila *f) {
    return (f->tras + 1) % MAX_PRODUTOS == f->frente;
}

int fila_vazia(Fila *f) {
    return f->frente == f->tras;
}

void adicionar_na_fila(Fila *f, Produto prod) {
    if (fila_cheia(f)) {
        printf("Fila cheia!\n");
        return;
    }
    f->produtos[f->tras] = prod;
    f->tras = (f->tras + 1) % MAX_PRODUTOS;
}

Produto remover_da_fila(Fila *f) {
    if (fila_vazia(f)) {
        printf("Fila vazia!\n");
        Produto prod = {"", "", 0.0, 0.0}; // Produto vazio
        return prod;
    }
    Produto produto = f->produtos[f->frente];
    f->frente = (f->frente + 1) % MAX_PRODUTOS;
    return produto;
}

void gerar_cupom_fiscal(Fila *f) {
    float total = 0;
    printf("Cupom Fiscal:\n");
    while (!fila_vazia(f)) {
        Produto prod = remover_da_fila(f);
        printf("%s - %s - %.2f Kg - R$ %.2f\n", prod.nome, prod.descricao, prod.peso, prod.preco);
        total += prod.preco;
    }
    printf("Total a pagar: R$ %.2f\n", total);
}

void pdv() {
    Fila fila_pdv;
    inicializar_fila(&fila_pdv);

    Produto produto1 = {"Produto 1", "Descricao 1", 1.0, 10.0};
    Produto produto2 = {"Produto 2", "Descricao 2", 2.0, 20.0};

    // Adicionar produtos à fila do PDV
    adicionar_na_fila(&fila_pdv, produto1);
    adicionar_na_fila(&fila_pdv, produto2);

    // Gerar cupom fiscal
    gerar_cupom_fiscal(&fila_pdv);
}
