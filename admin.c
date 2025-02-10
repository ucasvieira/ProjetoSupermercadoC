#include <ctype.h>
#include "supermercado.h"

void gerenciar_usuarios() {
    int opcao;
    do {
        printf("\n=== GERENCIAR USUÁRIOS ===\n");
        printf("1. Listar usuarios\n");
        printf("2. Adicionar usuario\n");
        printf("3. Remover usuario\n");
        printf("4. Editar usuario\n");
        printf("5. Verificar arquivo RAW\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                listar_usuarios();
                break;
            case 2:
                adicionar_usuario_admin();
                break;
            case 3:
                remover_usuario();
                break;
            case 4:
                editar_usuario();
                break;
            case 5:
                verificar_arquivo_usuarios();
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void listar_usuarios() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de usuarios!\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    int num_usuarios = file_size / sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(file_size);
    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);

    qsort(usuarios, num_usuarios, sizeof(Usuario), compara_usuarios);

    printf("\n=== LISTA DE USUÁRIOS (ORDENADA) ===\n");
    for(int i = 0; i < num_usuarios; i++) {
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Prontuario: %s\n", usuarios[i].prontuario);
        printf("Tipo: %s\n", usuarios[i].tipo == ADMIN ? "Admin" : "Usuario");
        printf("----------------------------\n");
    }

    free(usuarios);
}

void adicionar_usuario_admin() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb+");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de usuarios!\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    int num_usuarios = file_size / sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(file_size + sizeof(Usuario));
    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);

    Usuario novo;
    printf("\nNome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Prontuario: ");
    fgets(novo.prontuario, 15, stdin);
    novo.prontuario[strcspn(novo.prontuario, "\n")] = '\0';

    printf("Tipo (0-Usuario, 1-Admin): ");
    scanf("%d", (int*)&novo.tipo);
    getchar();

    usuarios[num_usuarios] = novo;
    num_usuarios++;

    qsort(usuarios, num_usuarios, sizeof(Usuario), compara_usuarios);

    arquivo = fopen("USUARIOS.DAT", "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        free(usuarios);
        return;
    }
    fwrite(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);
    free(usuarios);

    printf("Usuario cadastrado com sucesso!\n");
}

void remover_usuario() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    if (!arquivo) {
        printf("Arquivo de usuarios nao encontrado!\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    int num_usuarios = file_size / sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(file_size);
    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);

    char prontuario[15];
    printf("Prontuario do usuario a remover: ");
    fgets(prontuario, 15, stdin);
    prontuario[strcspn(prontuario, "\n")] = '\0';

    int index = -1;
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].prontuario, prontuario) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario nao encontrado!\n");
        free(usuarios);
        return;
    }

    for (int i = index; i < num_usuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    num_usuarios--;

    arquivo = fopen("USUARIOS.DAT", "wb");
    fwrite(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);
    free(usuarios);
    printf("Usuario removido com sucesso!\n");
}

int compara_usuarios(const void *a, const void *b) {
    const Usuario *ua = (const Usuario *)a;
    const Usuario *ub = (const Usuario *)b;

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

void editar_usuario() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb+");
    if (!arquivo) {
        printf("Arquivo de usuarios nao encontrado!\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    int num_usuarios = file_size / sizeof(Usuario);
    rewind(arquivo);

    Usuario *usuarios = malloc(file_size);
    if (!usuarios) {
        printf("Erro de alocação de memória!\n");
        fclose(arquivo);
        return;
    }

    fread(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);

    char prontuario[15];
    printf("Prontuario do usuario a editar: ");
    fgets(prontuario, 15, stdin);
    prontuario[strcspn(prontuario, "\n")] = '\0';

    int index = -1;
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].prontuario, prontuario) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario nao encontrado!\n");
        free(usuarios);
        return;
    }

    Usuario *user = &usuarios[index];
    printf("Novo nome [atual: %s]: ", user->nome);
    char novo_nome[100];
    fgets(novo_nome, 100, stdin);
    novo_nome[strcspn(novo_nome, "\n")] = '\0';
    if (strlen(novo_nome) > 0) strcpy(user->nome, novo_nome);

    printf("Novo prontuario [atual: %s]: ", user->prontuario);
    char novo_pront[15];
    fgets(novo_pront, 15, stdin);
    novo_pront[strcspn(novo_pront, "\n")] = '\0';
    if (strlen(novo_pront) > 0) strcpy(user->prontuario, novo_pront);

    printf("Novo tipo [atual: %d] (0-Usuario, 1-Admin): ", user->tipo);
    char tipo[2];
    fgets(tipo, 2, stdin);
    if (strlen(tipo) > 0) user->tipo = atoi(tipo) ? ADMIN : USUARIO;

    qsort(usuarios, num_usuarios, sizeof(Usuario), compara_usuarios);

    arquivo = fopen("USUARIOS.DAT", "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        free(usuarios);
        return;
    }

    fwrite(usuarios, sizeof(Usuario), num_usuarios, arquivo);
    fclose(arquivo);
    free(usuarios);

    printf("Usuario atualizado com sucesso!\n");
}

void verificar_arquivo_usuarios() {
    FILE *arquivo = fopen("USUARIOS.DAT", "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para verificacao!\n");
        return;
    }

    printf("\n=== CONTEUDO CRU DO ARQUIVO ===\n");

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    rewind(arquivo);

    int num_usuarios = file_size / sizeof(Usuario);
    printf("Tamanho do arquivo: %ld bytes\n", file_size);
    printf("Numero de usuarios: %d\n", num_usuarios);

    for (int i = 0; i < num_usuarios; i++) {
        Usuario u;
        fread(&u, sizeof(Usuario), 1, arquivo);
        printf("\n[Registro %d - Offset: %ld]\n", i+1, ftell(arquivo) - sizeof(Usuario));
        printf("Nome: %s\n", u.nome);
        printf("Prontuario: %s\n", u.prontuario);
        printf("Tipo: %s\n", u.tipo == ADMIN ? "Admin" : "Usuario");
    }

    fclose(arquivo);
}