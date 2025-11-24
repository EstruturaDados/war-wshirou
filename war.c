#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[50];
    char cor[30];
    int tropas;
};

/* ------------------------------------------------------ */
/* Função de batalha entre dois territórios               */
/* ------------------------------------------------------ */
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("O território atacante não tem tropas suficientes para atacar!\n");
        return;
    }

    printf("\n🔥 BATALHA ENTRE %s (ATACANTE) e %s (DEFENSOR)!\n",
           atacante->nome, defensor->nome);

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("🎲 Dado do atacante: %d\n", dadoAtk);
    printf("🛡️ Dado do defensor: %d\n", dadoDef);

    if (dadoAtk >= dadoDef) {  // empates favorecem o atacante
        defensor->tropas--;

        printf("⚔️ Atacante venceu! %s perdeu 1 tropa.\n", defensor->nome);

        if (defensor->tropas <= 0) {
            printf("🏴 %s foi conquistado por %s!\n",
                   defensor->nome, atacante->nome);

            defensor->tropas = 1;
            atacante->tropas--;
        }
    } else {
        atacante->tropas--;
        printf("🛡️ Defensor resistiu! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

/* ------------------------------------------------------ */
/* Função para mostrar o mapa                             */
/* ------------------------------------------------------ */
void mostrarMapa(struct Territorio *mapa, int n) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=================================\n");
}

int main() {
    srand(time(NULL)); // inicializa rand()

    int n = 5;
    struct Territorio *mapa = calloc(n, sizeof(struct Territorio));

    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== Cadastro dos Territórios ===\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar buffer
    }

    int opcao, atk, def;

    while (1) {
        mostrarMapa(mapa, n);

        printf("\n=== Fase de Ataque ===\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;
        if (opcao != 1) continue;

        printf("Escolha o território atacante (1 a %d): ", n);
        scanf("%d", &atk);

        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &def);
        getchar();

        if (atk < 1 || atk > n || def < 1 || def > n || atk == def) {
            printf("⚠️ Seleção inválida!\n");
            continue;
        }

        atacar(&mapa[atk - 1], &mapa[def - 1]);
    }

    free(mapa);
    printf("\nJogo encerrado. Até a próxima batalha!\n");

    return 0;
}