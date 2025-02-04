#include "supermercado.h"

Pilha gondolas[MAX_PRODUTOS]; // 10 gondolas
Pilha carrinho; // Carrinho de compras

void menu_gondolas() {
    int opcao;
    do {
        printf("\n=== MENU GONDOLAS ===\n");
        printf("1. Visualizar gondolas\n");
        printf("2. Adicionar produto\n");
        printf("3. debug pilha\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                visualizar_gondolas();
            break;
            case 2:
                abastecer_gondola();
            break;
            case 3:
                reinicializar_gondolas();
            break;
            case 0:
                printf("Retornando...\n");
            break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

// Implementação básica da pilha
void inicializar_pilha(Pilha *p) {
    // Garantir que a pilha comece vazia
    p->topo = -1;
    // Opcional: limpar dados antigos
    memset(p->itens, 0, sizeof(p->itens));
}

void inicializar_gondolas() {
    for(int i = 0; i < MAX_PRODUTOS; i++) {
        inicializar_pilha(&gondolas[i]);
    }
    printf("\nDiagnostico inicializacao:\n");
    for(int i = 0; i < MAX_PRODUTOS; i++) {
        printf("Gondola %d: topo=%d\n", i, gondolas[i].topo);
    }
}

// Função para administradores abastecerem
void abastecer_gondola() {
    if(usuario_logado.tipo != ADMIN) {
        printf("\nAcesso negado! Somente repositor.\n");
        return;
    }

    int num_gondola;
    printf("\n=== ABASTECIMENTO ===\n");
    printf("Numero da gondola (0-9): ");
    scanf("%d", &num_gondola);
    getchar();

    if(num_gondola < 0 || num_gondola >= MAX_PRODUTOS) {
        printf("Gondola invalida!\n");
        return;
    }

    if(pilha_cheia(&gondolas[num_gondola])) {
        printf("Erro: Gondola %d cheia!\n", num_gondola);
        return;
    }

    Produto novo;
    printf("Nome do produto: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Descricao: ");
    fgets(novo.descricao, 200, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    printf("Peso (kg): ");
    scanf("%f", &novo.peso);

    printf("Preco: R$");
    scanf("%f", &novo.preco);
    getchar(); // Limpar buffer

    inserir_produto(&gondolas[num_gondola], novo);
    printf("Produto adicionado a gondola %d!\n", num_gondola);
}

// Função para visualização das gondolas
void visualizar_gondolas() {
    printf("\n=== VISUALIZACAO DE GONDOLAS ===\n");
    for(int i = 0; i < MAX_PRODUTOS; i++) {
        int quantidade = gondolas[i].topo + 1;

        printf("\nGondola %d (%d/%d itens):\n", i, quantidade, MAX_ITENS);

        if(quantidade == 0) {
            printf(" [Gondola Vazia!]\n");
            continue;
        }

        // Mostrar apenas itens válidos
        for(int j = 0; j < quantidade; j++) {
            // Verificar se é um item válido
            if(strlen(gondolas[i].itens[j].nome) == 0) {
                continue; // Ignorar itens inválidos
            }

            printf("%d. %s\n   Desc: %s\n   Peso: %.2fkg\n   Preco: R$%.2f\n",
                   j+1,
                   gondolas[i].itens[j].nome,
                   gondolas[i].itens[j].descricao,
                   gondolas[i].itens[j].peso,
                   gondolas[i].itens[j].preco);
        }
    }
}


// Funções auxiliares da pilha
int pilha_cheia(Pilha *p) {
    return p->topo == MAX_ITENS - 1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void inserir_produto(Pilha *p, Produto prod) {
    if(pilha_cheia(p)) {
        printf("Erro: Capacidade maxima atingida!\n");
        return;
    }
    p->itens[++p->topo] = prod;
}

Produto retirar_produto(Pilha *p) {
    if(pilha_vazia(p)) {
        printf("Erro: Nao ha produtos disponiveis!\n");
        Produto vazio = {"", "", 0, 0};
        return vazio;
    }
    return p->itens[p->topo--];
}
void reinicializar_gondolas() {
    for(int i = 0; i < MAX_PRODUTOS; i++) {
        inicializar_pilha(&gondolas[i]);
        // Limpeza explícita dos dados
        memset(&gondolas[i], 0, sizeof(Pilha));
        gondolas[i].topo = -1; // Garantir que comece vazia
    }
    printf("Gondolas reinicializadas com sucesso!\n");
}