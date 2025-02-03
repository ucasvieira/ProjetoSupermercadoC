#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"

// Função de comparação para ordenação
int compara_usuarios(const void *a, const void *b) {
    return strcmp(((Usuario*)a)->nome, ((Usuario*)b)->nome);
}

void cadastrar_usuario() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb+");
    if (!arquivo) {
        arquivo = fopen("USUARIOS.DAT", "wb+");
        if (!arquivo) {
            printf("Erro na criação do arquivo!\n");
            exit(1);
        }
    }

    // Carregar usuários existentes
    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    int num_usuarios = file_size / sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(file_size + sizeof(Usuario));
    if (!usuarios) {
        printf("Erro de alocação de memória!\n");
        fclose(arquivo);
        exit(1);
    }

    if (num_usuarios > 0) {
        fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    }

    // Cadastrar novo usuário
    Usuario novo;
    printf("\n=== CADASTRO DE USUÁRIO ===\n");
    
    printf("Nome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    
    printf("Prontuário: ");
    fgets(novo.prontuario, 15, stdin);
    novo.prontuario[strcspn(novo.prontuario, "\n")] = '\0';

    // Encontrar posição de inserção
    int pos = num_usuarios;
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(novo.nome, usuarios[i].nome) < 0) {
            pos = i;
            break;
        }
    }

    // Deslocar usuários
    for (int i = num_usuarios; i > pos; i--) {
        usuarios[i] = usuarios[i-1];
    }

    // Inserir novo usuário
    usuarios[pos] = novo;
    num_usuarios++;

    // Reescrever arquivo ordenado
    freopen("USUARIOS.DAT", "wb", arquivo);
    fwrite(usuarios, sizeof(Usuario), num_usuarios, arquivo);

    free(usuarios);
    fclose(arquivo);
    printf("\nUsuário cadastrado com sucesso!\n");
}

void cadastrar_usuarios_padrao() {
    Usuario padroes[] = {
        {"Domingos Lucas Latorre de Oliveira", "CJ146456"},
        {"Leandro Pinto Santana", "CP220383"},
        // ... (inserir todos os outros usuários listados na questão)
        {"Cesar Lopes Fernandes", "SP890534"},
        {"Josceli Maria Tenorio", "SZ124382"}
    };

    FILE *arquivo = fopen("USUARIOS.DAT", "wb");
    if (!arquivo) {
        printf("Erro ao criar arquivo de usuários!\n");
        exit(1);
    }

    qsort(padroes, sizeof(padroes)/sizeof(Usuario), sizeof(Usuario), compara_usuarios);
    fwrite(padroes, sizeof(Usuario), sizeof(padroes)/sizeof(Usuario), arquivo);
    fclose(arquivo);
}

