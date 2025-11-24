#include <stdio.h>
#include <string.h>

#define MAX 5

struct Territorio {
    char nome[50];
    char cor[30];
    int tropas;
};

int main() {
    struct Territorio mapa[MAX];

    for (int i = 0; i < MAX; i++) {
        printf("=== Cadastro do Território %d ===\n", i + 1);

        // Leitura do nome
        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';  // remove '\n'

        // Leitura da cor
        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        // Leitura do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);

        getchar(); // limpar buffer após scanf
        printf("\n");
    }

    // Impressão do estado atual do mapa
    printf("===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < MAX; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}
