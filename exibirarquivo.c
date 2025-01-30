#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30

// Estrutura para armazenar os dados do usuário
typedef struct {
    char nome[100];
    char prontuario[20];
} Usuario;

void exibir_dados() {
    Usuario usuarios[MAX_USUARIOS];
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Lê os usuários do arquivo
    int num_usuarios = 0;
    while (fread(&usuarios[num_usuarios], sizeof(Usuario), 1, arquivo)) {
        num_usuarios++;
    }
    fclose(arquivo);

    // Exibe os dados dos usuários
    printf("Lista de Usuários Cadastrados:\n");
    for (int i = 0; i < num_usuarios; i++) {
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Prontuário: %s\n", usuarios[i].prontuario);
        printf("-----------------------------\n");
    }
}

int main() {
    // Chama a função para exibir os dados
    exibir_dados();

    return 0;
}
