// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"

Usuario usuario_logado;

int login(char nome[100], char prontuario[15]) {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    if (!arquivo) {
        printf("\nErro: Arquivo USUARIOS.DAT nao encontrado!\n");
        exit(1);
    }

    // Obter tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    rewind(arquivo);

    int num_usuarios = file_size / sizeof(Usuario);
    Usuario *usuarios = (Usuario*)malloc(file_size);

    if (!usuarios) {
        printf("\nErro de alocacao de memoria!\n");
        fclose(arquivo);
        exit(1);
    }

    // Ler todos os usuários
    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);

    // Busca binária corrigida
    int encontrado = 0;
    int left = 0, right = num_usuarios - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcasecmp(nome, usuarios[mid].nome);

        if (cmp == 0) {
            // Encontrou nome, verificar prontuário
            if (strcmp(prontuario, usuarios[mid].prontuario) == 0) {
                encontrado = 1;
                usuario_logado = usuarios[mid];  // Armazena o usuário logado
                break;
            }
            // Procurar por possíveis colisões de nome
            int temp = mid;
            while (temp >= left && strcmp(nome, usuarios[temp].nome) == 0) {
                if (strcmp(prontuario, usuarios[temp].prontuario) == 0) {
                    encontrado = 1;
                    break;
                }
                temp--;
            }
            if (!encontrado) {
                temp = mid + 1;
                while (temp <= right && strcmp(nome, usuarios[temp].nome) == 0) {
                    if (strcmp(prontuario, usuarios[temp].prontuario) == 0) {
                        encontrado = 1;
                        break;
                    }
                    temp++;
                }
            }
            break;
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    free(usuarios);

    if (!encontrado) {
        printf("\nUSUÁRIO E/OU PRONTUÁRIO INVÁLIDO!\n");
        exit(1);
    }

    printf("\nLogin realizado com sucesso!\n");
    return 1;
}