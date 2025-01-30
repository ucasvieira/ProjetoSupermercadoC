// supermercado.h
#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30
#define MAX_ITENS 5
#define MAX_PRODUTOS 10

// Estrutura para o cadastro do usuário
typedef struct {
    char nome[100];
    char prontuario[15];
} Usuario;

// Estrutura para os produtos nas gôndolas
typedef struct {
    char nome[100];
    char descricao[200];
    float peso;
    float preco;
} Produto;

// Estrutura para as pilhas de gôndolas
typedef struct {
    Produto itens[MAX_ITENS];
    int topo;
} Pilha;

// Estrutura para a fila do PDV
typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int frente;
    int tras;
} Fila;

void abastecer_gondola();
void pdv();

// Funções para manipulação dos usuários
void cadastrar_usuario(FILE *arquivo);
int buscar_usuario(FILE *arquivo, char *nome, char *prontuario);
void ordenar_usuarios(FILE *arquivo);
int compara_usuarios(const void *a, const void *b);

// Funções para manipulação da pilha
void inicializar_pilha(Pilha *p);
int pilha_cheia(Pilha *p);
int pilha_vazia(Pilha *p);
void inserir_produto(Pilha *p, Produto prod);
Produto retirar_produto(Pilha *p);

// Funções para manipulação da fila
void inicializar_fila(Fila *f);
int fila_cheia(Fila *f);
int fila_vazia(Fila *f);
void adicionar_na_fila(Fila *f, Produto prod);
Produto remover_da_fila(Fila *f);

// Função para gerar o cupom fiscal
void gerar_cupom_fiscal(Fila *f);

int login();

#endif
