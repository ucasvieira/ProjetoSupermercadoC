#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"

// Função de comparação para ordenação
int compara_usuarios(const void *a, const void *b) {
    const Usuario *ua = (const Usuario *)a;
    const Usuario *ub = (const Usuario *)b;

    // Comparação case-insensitive
    const char *nomeA = ua->nome;
    const char *nomeB = ub->nome;

    while (*nomeA && *nomeB) {
        int diff = tolower((unsigned char)*nomeA) - tolower((unsigned char)*nomeB);
        if (diff != 0) return diff;
        nomeA++;
        nomeB++;
    }
    return *nomeA - *nomeB;
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

    for(int i = 0; novo.nome[i]; i++) {
        novo.nome[i] = tolower(novo.nome[i]);
    }
    
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
        {"Eurides Balbino da Silva", "SP07102X", ADMIN},
        {"Domingos Bernardo Gomes Santos", "SP090888", ADMIN},
        {"Andre Evandro Lourenco", "SP100092", ADMIN},
        {"Miguel Angelo Tancredi Molina", "SP102763", ADMIN},
        {"Antonio Airton Palladino", "SP112197", ADMIN},
        {"Luis Fernando Aires Branco Menegueti", "SP145385", ADMIN},
        {"Antonio Ferreira Viana", "SP200827", ADMIN},
        {"Leonardo Bertholdo", "SP204973", ADMIN},
        {"Marcelo Tavares de Santana", "SP20500X", ADMIN},
        {"Wagner de Paula Gomes", "SP215016", ADMIN},
        {"Daniel Marques Gomes de Morais", "SP220097", ADMIN},
        {"Alexandre Beletti Ferreira", "SP226117", ADMIN},
        {"Vladimir Camelo Pinto", "SP240291", ADMIN},
        {"Leonardo Andrade Motta de Lima", "SP24031X", ADMIN},
        {"Aldo Marcelo Paim", "SP240497", ADMIN},
        {"Cesar Lopes Fernandes", "SP890534",USUARIO},
        {"lucas","12345",ADMIN}
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

int main() {
    printf("Selecione a opção desejada:\n1 - Cadastrar usuário\n2 - Cadastrar usuários padrão\n");
    int opcao;
    scanf("%i", &opcao);fflush(stdin);
    if (opcao == 1) {
        cadastrar_usuario();
    } else if (opcao == 2) {
        cadastrar_usuarios_padrao();
    } else {
        printf("Opção inválida!\n");
    }
    return 0;
}