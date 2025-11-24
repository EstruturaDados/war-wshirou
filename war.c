#include <stdio.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 50
#define TAM_COR 30

struct Territorio {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int tropas;
};

int main() {
    struct Territorio mapa[MAX];

    printf("=== Cadastro Inicial dos Territorios ===\n\n");

    for (int i = 0; i < MAX; i++) {
        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do Exercito: ");
        fgets(mapa[i].corExercito, TAM_COR, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar Enter do buffer

        printf("\n");
    }

    // Exibição do estado do mapa
    printf("\n=== Estado Atual do Mapa ===\n\n");

    for (int i = 0; i < MAX; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exercito: %s\n", mapa[i].corExercito);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}