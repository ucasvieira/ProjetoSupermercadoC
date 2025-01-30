#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30

// Estrutura para armazenar os dados do usuário
typedef struct {
    char nome[100];
    char prontuario[20];
} Usuario;

// Função para realizar o login
int realizar_login() {
    char nome[100];
    char prontuario[20];
    Usuario usuario;
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return 0;
    }

    // Solicitar nome e prontuário ao usuário
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';  // Remove a quebra de linha no final da string

    printf("Digite seu prontuário: ");
    fgets(prontuario, sizeof(prontuario), stdin);
    prontuario[strcspn(prontuario, "\n")] = '\0';  // Remove a quebra de linha no final da string

    // Verifica se os dados correspondem a algum usuário no arquivo
    while (fread(&usuario, sizeof(Usuario), 1, arquivo)) {
        if (strcmp(nome, usuario.nome) == 0 && strcmp(prontuario, usuario.prontuario) == 0) {
            fclose(arquivo);
            printf("Login realizado com sucesso!\n");
            return 1;  // Login bem-sucedido
        }
    }

    fclose(arquivo);
    printf("Nome ou prontuário inválidos.\n");
    return 0;  // Falha no login
}

int main() {
    int resultado = realizar_login();
    
    if (resultado) {
        // Aqui você pode adicionar código para prosseguir com a aplicação, após o login bem-sucedido
        printf("Bem-vindo ao sistema.\n");
    } else {
        printf("Tentativa de login falhou. Tente novamente.\n");
    }
    
    return 0;
}
