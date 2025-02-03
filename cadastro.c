// cadastro.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"

void cadastrar_usuario() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb+");
    if (!arquivo) arquivo = fopen("USUARIOS.DAT", "wb+");

    // Carregar usuários existentes
    fseek(arquivo, 0, SEEK_END);
    int num_usuarios = ftell(arquivo)/sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(num_usuarios * sizeof(Usuario));
    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);

    // Cadastrar novo usuário
    Usuario novo;
    printf("\nNovo nome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Prontuario: ");
    fgets(novo.prontuario, 15, stdin);
    novo.prontuario[strcspn(novo.prontuario, "\n")] = '\0';

    // Inserir na posição correta
    int i = num_usuarios - 1;
    while (i >= 0 && strcmp(novo.nome, usuarios[i].nome) < 0) {
        usuarios[i+1] = usuarios[i];
        i--;
    }
    usuarios[i+1] = novo;
    num_usuarios++;

    // Reescrever arquivo
    freopen("USUARIOS.DAT", "wb", arquivo);
    fwrite(usuarios, sizeof(Usuario), num_usuarios, arquivo);

    free(usuarios);
    fclose(arquivo);
}
