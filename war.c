#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio *mapa, int n);
void exibirMapa(Territorio *mapa, int n);
void batalhar(Territorio *atacante, Territorio *defensor);

int main() {
    srand(time(NULL));

    int n = 5;
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int escolhaAtacante, escolhaDefensor;

    while (1) {
        exibirMapa(mapa, n);

        printf("\nEscolha o território ATACANTE (1 a 5, 0 para sair): ");
        scanf("%d", &escolhaAtacante);
        if (escolhaAtacante == 0) break;

        printf("Escolha o território DEFENSOR (1 a 5): ");
        scanf("%d", &escolhaDefensor);

        if (escolhaAtacante < 1 || escolhaAtacante > 5 ||
            escolhaDefensor < 1 || escolhaDefensor > 5 ||
            escolhaAtacante == escolhaDefensor) {
            printf("\n❌ Escolha inválida!\n");
            continue;
        }

        batalhar(&mapa[escolhaAtacante - 1], &mapa[escolhaDefensor - 1]);
    }

    free(mapa);
    return 0;
}

void cadastrarTerritorios(Territorio *mapa, int n) {
    printf("=== Cadastro dos Territorios ===\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        getchar(); // limpar buffer
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(Territorio *mapa, int n) {
    printf("\n==== MAPA ATUAL ====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %-12s | Exército: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void batalhar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n🎲 Dados rolados:");
    printf("\nAtacante (%s): %d", atacante->nome, dadoA);
    printf("\nDefensor  (%s): %d\n", defensor->nome, dadoD);

    if (dadoA >= dadoD) {
        printf("\n🔥 Ataque bem-sucedido!\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("🏴 Território %s foi conquistado!\n", defensor->nome);

            // O exército atacante ocupa o território
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;          // defensor reinicia com tropa mínima
            atacante->tropas -= 1;         // atacante desloca 1 tropa
        }

    } else {
        printf("\n🛡 Defesa bem-sucedida! O atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}
