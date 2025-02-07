#include "supermercado.h"


#define ARQUIVO_GONDOLAS "GONDOLAS.DAT"

Gondola gondolas[MAX_GONDOLAS]; // 10 gondolas
Carrinho carrinho; // Carrinho de compras

void menu_gondolas() {
    int opcao;
    do {
        printf("\n=== MENU GONDOLAS ===\n");
        printf("1. Visualizar gondolas\n");
        printf("2. Adicionar produto\n");
        printf("3. Limpar Gondola\n");
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
                limpar_gondola();
            case 0:
                printf("Retornando...\n");
            break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

// Implementação básica da pilha
void inicializar_pilha(Gondola *p) {
    p->topo = -1;
    memset(p->itens, 0, sizeof(p->itens));
}

// Função para administradores abastecerem
void abastecer_gondola() {
    if(usuario_logado.tipo != ADMIN) {
        printf("\nAcesso negado! Somente repositor.\n");
        return;
    }

    int num_gondola;
    printf("\n=== ABASTECIMENTO ===\n");
    printf("Numero da gondola (1-10): ");
    scanf("%d", &num_gondola);
    getchar();

    num_gondola-=1; // Ajustar para índice 0-based

    if(num_gondola < 0 || num_gondola >= MAX_GONDOLAS) {
        printf("Gondola invalida!\n");
        return;
    }

    if(pilha_cheia(&gondolas[num_gondola])) {
        printf("Erro: Gondola %d cheia!\n", num_gondola +1);
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
    salvar_gondolas(); // Salva alterações no arquivo
    printf("Produto adicionado a gondola %d!\n", num_gondola + 1);
}

// Função para visualização das gondolas
void visualizar_gondolas() {
    printf("\n=== VISUALIZACAO DE GONDOLAS ===\n");
    for(int i = 0; i < MAX_GONDOLAS; i++) {
        int quantidade = gondolas[i].topo +1;

        printf("\nGondola %d (%d/%d itens):", i+1, gondolas[i].topo + 1, MAX_ITENS_GONDOLA);
        if (gondolas[i].topo >= MAX_ITENS_GONDOLA - 1) {
            printf("   [Gondola Cheia!]\n");
        }else{
            printf("\n");
        }

        if(quantidade == 0) { // topo == -1
            printf(" [Gondola Vazia!]\n");
            continue;
        }

        // Mostrar apenas itens válidos
        for(int j = 0; j < quantidade; j++) {
            // Verificar se é um item válido

            printf("\n%d. %s\n   Desc: %s\n   Peso: %.2fkg\n   Preco: R$%.2f\n",
                   j + 1,
                   gondolas[i].itens[j].nome,
                   gondolas[i].itens[j].descricao,
                   gondolas[i].itens[j].peso,
                   gondolas[i].itens[j].preco);


        }
        if(gondolas[i].topo >= MAX_ITENS_GONDOLA - 1) {
            printf("\n [Gondola Cheia!]\n");
        }
    }
}


// Funções auxiliares da pilha
int pilha_cheia(Gondola *p) {
    return p->topo == MAX_ITENS_GONDOLA -1;
}

int pilha_vazia(Gondola *p) {
    return p->topo == -1;
}

void inserir_produto(Gondola *p, Produto prod) {
    if(pilha_cheia(p)) {
        printf("Erro: Capacidade maxima atingida!\n");
        return;
    }
    p->itens[++p->topo] = prod;
}

Produto retirar_produto(Gondola *p) {
    if(pilha_vazia(p)) {
        printf("Erro: Nao ha produtos disponiveis!\n");
        Produto vazio = {"", "", 0, 0, -1};
        return vazio;
    }
    int temp = p->topo;
    p->topo--;
    return p->itens[temp];

}

void salvar_gondolas() {
    FILE *arquivo = fopen(ARQUIVO_GONDOLAS, "wb");
    if(!arquivo) {
        printf("Erro ao salvar gondolas!\n");
        return;
    }

    // Salvar todas as gondolas de uma vez
    fwrite(gondolas, sizeof(Gondola), MAX_GONDOLAS, arquivo);
    fclose(arquivo);
}

void carregar_gondolas() {
    FILE *arquivo = fopen(ARQUIVO_GONDOLAS, "rb");
    if (!arquivo) {
        printf("Arquivo de gondolas nao encontrado. Iniciando com gondolas vazias.\n");
        reinicializar_gondolas(); // Inicializa explicitamente
        return;
    }

    // Verificar tamanho correto do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    if (tamanho != sizeof(Gondola) * MAX_GONDOLAS) {
        printf("Arquivo corrompido. Recriando gondolas...\n");
        fclose(arquivo);
        reinicializar_gondolas();
        return;
    }

    // Carregar dados válidos
    size_t lidos = fread(gondolas, sizeof(Gondola), MAX_GONDOLAS, arquivo);
    fclose(arquivo);

    if (lidos != MAX_GONDOLAS) {
        printf("Erro ao ler gondolas. Recriando...\n");
        reinicializar_gondolas();
    }
}

void reinicializar_gondolas() {
    for (int i = 0; i < MAX_GONDOLAS; i++) {
        inicializar_pilha(&gondolas[i]);
    }
    salvar_gondolas(); // Salva o estado vazio
}

void limpar_gondola() {

    int num_gondola;
    printf("\n=== LIMPAR GONDOLA ===\n");
    printf("Numero da gondola (1-10): ");
    scanf("%d", &num_gondola);
    getchar();

    num_gondola-=1; // Ajustar para índice 0-based

    if(num_gondola < 0 || num_gondola >= MAX_GONDOLAS) {
        printf("Gondola invalida!\n");
        return;
    }

    if(pilha_vazia(&gondolas[num_gondola])) {
        printf("Erro: Gondola %d cheia!\n", num_gondola +1);
        return;
    }

    inicializar_pilha(&gondolas[num_gondola]);
    salvar_gondolas();
    printf("Gondola %d limpa!\n", num_gondola + 1);
}