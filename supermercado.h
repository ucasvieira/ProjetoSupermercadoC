// supermercado.h
#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30
#define MAX_ITENS 5
#define MAX_PRODUTOS 10

typedef struct {
    char nome[100];
    char prontuario[15];
} Usuario;

typedef struct {
    char nome[100];
    char descricao[200];
    float peso;
    float preco;
} Produto;

typedef struct {
    Produto itens[MAX_ITENS];
    int topo;
} Pilha;

typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int frente;
    int tras;
} Fila;

// Funções principais
int login();
void cadastrar_usuario();

// Operações das gôndolas
extern Pilha gondolas[MAX_PRODUTOS];
void inicializar_gondolas();
void abastecer_gondola();

// Operações do PDV
extern Fila fila_pdv;
extern Pilha carrinho;
void inicializar_pdv();
void adicionar_ao_carrinho();
void processar_pdv();

// Funções auxiliares
int pilha_cheia(Pilha *p);
int pilha_vazia(Pilha *p);
void inserir_produto(Pilha *p, Produto prod);
Produto retirar_produto(Pilha *p);
int fila_cheia(Fila *f);
int fila_vazia(Fila *f);
void adicionar_na_fila(Fila *f, Produto prod);
Produto remover_da_fila(Fila *f);
void gerar_cupom_fiscal(Fila *f);

#endif