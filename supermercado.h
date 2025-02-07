// supermercado.h
#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30
#define MAX_ITENS 5
#define MAX_GONDOLAS 10      // Quantidade de gôndolas
#define MAX_ITENS_GONDOLA 5
#define MAX_ITENS_CARRINHO 20// Capacidade de cada gôndola
#define MAX_PRODUTOS 100


typedef enum {USUARIO, ADMIN} TipoUsuario;


typedef struct {
    char nome[100];
    char prontuario[15];
    TipoUsuario tipo;
} Usuario;

extern Usuario usuario_logado;

typedef struct {
    char nome[100];
    char descricao[200];
    float peso;
    float preco;
    int num_gondola;
} Produto;

typedef struct {
    Produto itens[MAX_ITENS];
    int topo;  // Deve ser inicializado com -1
} Gondola;

typedef struct {
    Produto itens[MAX_ITENS_CARRINHO];
    int topo;  // Deve ser inicializado com -1
} Carrinho;

typedef struct {
    Produto *produtos;  // Vetor dinâmico
    int capacidade;
    int frente;
    int tras;
} Fila;

// Funções principais
int login(char nome[100], char prontuario[15]);
void cadastrar_usuario();

// Operações das gôndolas
extern Gondola gondolas[MAX_GONDOLAS];
extern Carrinho carrinho;
void menu_gondolas();
void abastecer_gondola();
void visualizar_gondolas();
void reinicializar_gondolas();
void salvar_gondolas();
void carregar_gondolas();
void editar_gondola();
void reinicalizar_gondolas();
void limpar_gondola();


// Operações do PDV
extern Fila fila_pdv;
void menu_pdv();
void menu_carrinho();
void remover_do_carrinho();
void finalizar_compra();
void inicializar_pdv();
void adicionar_ao_carrinho();
void processar_pdv();
void inserir_produto_carrinho(Carrinho *p, Produto prod);
// Funções da fila
void inicializar_fila(Fila *f);
int fila_cheia(Fila *f);
int fila_vazia(Fila *f);
void adicionar_na_fila(Fila *f, Produto prod);
Produto remover_da_fila(Fila *f);

// Funções do carrinho
void mostrar_carrinho();
void remover_do_carrinho();
int carrinho_vazio(Carrinho *p);
int carrinho_cheio(Carrinho *p);

// Funções auxiliares
int pilha_cheia(Gondola *p);
int pilha_vazia(Gondola *p);
void inserir_produto(Gondola *p, Produto prod);
Produto retirar_produto(Gondola *p);
int fila_cheia(Fila *f);
int fila_vazia(Fila *f);
void adicionar_na_fila(Fila *f, Produto prod);
Produto remover_da_fila(Fila *f);
void gerar_cupom_fiscal(Fila *f);
void inicializar_pilha(Gondola *p);


// Funções de administração
void gerenciar_usuarios();
void listar_usuarios();
void adicionar_usuario_admin();
void remover_usuario();
int compara_usuarios(const void *a, const void *b);
void editar_usuario();

// Função de checar arquivo
void verificar_arquivo_usuarios();
#endif