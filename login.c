#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 30

// Estrutura para armazenar os dados do usuário
typedef struct {
    char nome[100];
    char prontuario[20];
} Usuario;

// Função para realizar a busca binária no vetor de usuários
int busca_binaria(Usuario usuarios[], int n, const char* nome, const char* prontuario) {
    int esquerda = 0, direita = n - 1;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        
        // Compara o nome para achar a posição correta
        int cmp = strcmp(nome, usuarios[meio].nome);
        
        if (cmp == 0) {
            // Se os nomes são iguais, verifica o prontuário
            if (strcmp(prontuario, usuarios[meio].prontuario) == 0) {
                return meio; // Encontrou o usuário
            } else {
                return -1; // Prontuário não corresponde
            }
        } else if (cmp < 0) {
            direita = meio - 1; // Nome está antes
        } else {
            esquerda = meio + 1; // Nome está depois
        }
    }

    return -1; // Não encontrou o usuário
}

// Função para carregar os dados do arquivo binário
int carregar_usuarios(Usuario usuarios[]) {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return 0;
    }

    int num_usuarios = 0;
    while (fread(&usuarios[num_usuarios], sizeof(Usuario), 1, arquivo)) {
        num_usuarios++;
    }

    fclose(arquivo);
    return num_usuarios;
}

// Função para remover qualquer \n no final das strings
void remove_newline(char* str) {
    const size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função de login
int login() {
    char nome[100];
    char prontuario[20];
    Usuario usuario;
    FILE *arquivo = fopen("./USUARIOS.DAT", "rb");
    
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
    int log = login();
    if (log == 0) {
        exit(0);
    }else if (log == 1) {

    }

    return 0;
}
