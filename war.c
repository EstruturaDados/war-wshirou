#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

void exibirMapa(Territorio *t, int n) {
    printf("\n===== ESTADO DO MAPA =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
    printf("===========================\n");
}

void simularAtaque(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n🎲 Dados sorteados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtq);
    printf("Defensor  (%s): %d\n", defensor->nome, dadoDef);

    if (dadoAtq >= dadoDef) {
        printf("➡️ Atacante venceu o confronto!\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("🏳️ O defensor perdeu todas as tropas!\n");
            printf("🏴 Território %s foi conquistado por %s!\n",
                   defensor->nome, atacante->nome);
            defensor->tropas = 1; // ganha uma tropa mínima
            strcpy(defensor->cor, atacante->cor);
        }

    } else {
        printf("🛡️ Defensor resistiu ao ataque!\n");
        atacante->tropas--;
    }
}

int main() {
    srand(time(NULL));

    int n = 5;
    Territorio *mapa = (Territorio*) calloc(n, sizeof(Territorio));

    if (!mapa) {
        printf("Erro de alocação!\n");
        return 1;
    }

    printf("=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    int at, def, opcao = 1;

    while (opcao == 1) {
        exibirMapa(mapa, n);

        printf("\nEscolha o território ATACANTE (1-5): ");
        scanf("%d", &at);
        printf("Escolha o território DEFENSOR (1-5): ");
        scanf("%d", &def);
        getchar();

        if (at < 1 || at > 5 || def < 1 || def > 5 || at == def) {
            printf("❌ Escolha inválida!\n");
            continue;
        }

        simularAtaque(&mapa[at - 1], &mapa[def - 1]);

        printf("\nDeseja realizar outro ataque? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);
        getchar();
    }

    printf("\nJogo encerrado! Estado final do mapa:\n");
    exibirMapa(mapa, n);

    free(mapa);
    return 0;
}