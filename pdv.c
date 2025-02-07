#include "supermercado.h"
#include <time.h>

Fila fila_pdv;

Produto retirar_produto_carrinho(Carrinho *p) {
    if(carrinho_vazio(p)) {
        printf("Erro: Nao ha produtos disponiveis!\n");
        Produto vazio = {"", "", 0, 0, -1};
        return vazio;
    }
    return p->itens[p->topo--];
}

void inicializar_carrinho(Carrinho *p) {
    p->topo = -1;
    memset(p->itens, 0, sizeof(p->itens));
}

void menu_pdv() {
    int opcao;
    do {
        printf("\n=== CAIXA/PDV ===\n");
        mostrar_carrinho();
        printf("\n1. Adicionar item ao carrinho\n");
        printf("2. Remover ultimo item do carrinho\n");
        printf("3. Finalizar compra\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                adicionar_ao_carrinho();
            break;
            case 2:
                remover_do_carrinho();
            break;
            case 3:
                finalizar_compra();
            break;
            case 0:
                printf("Retornando...\n");
            break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}


void remover_do_carrinho() {
    if(carrinho_vazio(&carrinho)) {
        printf("Carrinho vazio!\n");
        return;
    }

    Produto p = retirar_produto_carrinho(&carrinho);
    printf("Item removido: %s\n", p.nome);
    // Devolve o produto à gondola original
    if(!pilha_cheia(&gondolas[p.num_gondola])) {
        carrinho.topo--;
        inserir_produto(&gondolas[p.num_gondola], p);
        printf("Item devolvido a gondola %d\n", p.num_gondola + 1);
    } else {
        printf("Erro: Gondola %d cheia! Item nao pode ser devolvido.\n", p.num_gondola + 1);
    }
}

void finalizar_compra() {
    if(carrinho_vazio(&carrinho)) {
        printf("Carrinho vazio!\n");
        return;
    }

    // Verifica espaço na fila
    if(fila_cheia(&fila_pdv)) {
        printf("Erro: Fila do PDV cheia! Não é possível finalizar a compra.\n");
        return;
    }

    // Cria lista temporária para inverter a ordem
    Produto temp[MAX_ITENS_CARRINHO];
    int index = 0;

    // Transfere para lista temporária
    while(!carrinho_vazio(&carrinho)) {
        temp[index++] = retirar_produto_carrinho(&carrinho);
    }

    // Transfere para fila na ordem correta
    for(int i = index-1; i >= 0; i--) {
        adicionar_na_fila(&fila_pdv, temp[i]);
    }

    // Gera cupom e limpa carrinho
    gerar_cupom_fiscal(&fila_pdv);
    inicializar_carrinho(&carrinho);
    salvar_gondolas();
}

void gerar_cupom_fiscal(Fila *f) {
    printf("eae teste boga\n");
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char data_hora[50];
    strftime(data_hora, sizeof(data_hora), "%d/%m/%Y %H:%M:%S", t);
    printf("eae teste boga\n");
    float total = 0;

    printf("\n=== CUPOM FISCAL ===\n");
    printf("Supermercado XPTO\n");
    printf("Data: %s\n", data_hora);
    printf("Atendente: %s\n\n", usuario_logado.nome);
    printf("Itens:\n");

    int contador = 1;
    while(!fila_vazia(f)) {
        Produto p = remover_da_fila(f);
        printf("%d. %s\n", contador++, p.nome);
        printf("   Descricao: %s\n", p.descricao);
        printf("   Peso: %.2fkg\n", p.peso);
        printf("   Preco: R$%.2f\n\n", p.preco);
        total += p.preco;
    }

    printf("Total: R$%.2f\n", total);
    printf("====================\n");

    // Reinicializa a fila após gerar o cupom
    inicializar_fila(f);
}


void adicionar_ao_carrinho() {
    int num_gondola;
    printf("Numero da gondola (1-%d): ", MAX_GONDOLAS);
    scanf("%d", &num_gondola);
    num_gondola-=1  ;

    if(num_gondola < 0 || num_gondola >= MAX_GONDOLAS) {
        printf("Gondola inválida!\n");
        return;
    }

    if(pilha_vazia(&gondolas[num_gondola])) {
        printf("Gondola vazia!\n");
        return;
    }

    Produto p = retirar_produto(&gondolas[num_gondola]);
    p.num_gondola = num_gondola;

    // Ensure product name and description are null-terminated
    p.nome[sizeof(p.nome) - 1] = '\0';
    p.descricao[sizeof(p.descricao) - 1] = '\0';

    if(carrinho.topo == MAX_ITENS_CARRINHO - 1) {
        printf("Carrinho cheio! Finalize a compra primeiro.\n");
        inserir_produto(&gondolas[num_gondola], p); // Devolve o produto
        return;
    }

    inserir_produto_carrinho(&carrinho, p);
    printf("Produto adicionado: %s\n", p.nome);
}

void inicializar_pdv() {
    inicializar_fila(&fila_pdv);
    inicializar_carrinho(&carrinho);
}

void inicializar_fila(Fila *f) {
    f->capacidade = MAX_PRODUTOS;
    f->produtos = malloc(f->capacidade * sizeof(Produto));
    f->frente = 0;
    f->tras = -1;
}

int fila_cheia(Fila *f) {
    return (f->tras - f->frente + 1) == f->capacidade;
}

int fila_vazia(Fila *f) {
    return f->tras < f->frente;
}

void adicionar_na_fila(Fila *f, Produto prod) {
    if(fila_cheia(f)) {
        // Aumenta capacidade se necessário
        f->capacidade *= 2;
        f->produtos = realloc(f->produtos, f->capacidade * sizeof(Produto));
    }
    f->produtos[++f->tras] = prod;
}

Produto remover_da_fila(Fila *f) {
    if(fila_vazia(f)) {
        Produto vazio = {"", "", 0, 0, -1};
        return vazio;
    }
    return f->produtos[f->frente++];
}

void mostrar_carrinho() {
    printf("\n=== CARRINHO DE COMPRAS ===\n");
    if(carrinho_vazio(&carrinho)) {
        printf("Carrinho vazio!\n");
        return;
    }

    for(int i = carrinho.topo; i >= 0; i--) {
        printf("%d. %s (Gondola %d) - R$%.2f\n",
              carrinho.topo - i + 1,
              carrinho.itens[i].nome,
              carrinho.itens[i].num_gondola + 1, // Exibe a gondola de origem
              carrinho.itens[i].preco);
    }
}

void inserir_produto_carrinho(Carrinho *p, Produto prod) {
    if(p->topo == MAX_ITENS_CARRINHO - 1) {
        printf("Erro: Carrinho cheio! Finalize a compra primeiro.\n");
        return;
    }
    p->itens[++p->topo] = prod;
}

int carrinho_cheio(Carrinho *p) {
    return p->topo == MAX_ITENS_GONDOLA -1;
}

int carrinho_vazio(Carrinho *p) {
    return p->topo == -1;
}
