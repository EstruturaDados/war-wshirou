#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

typedef struct {
    char nome[40];
    char cor[20];
    int tropas;
} Territorio;

typedef enum {
    MISSAO_DESTRUIR_VERDE = 1,
    MISSAO_CONQUISTAR_3 = 2
} Missao;

// ---- PROTÓTIPOS ----
void inicializarTerritorios(Territorio *t);
void exibirMapa(const Territorio *t);
int escolherTerritorio(const char *msg);
void simularAtaque(Territorio *at, Territorio *def);
Missao sortearMissao();
void exibirMissao(Missao m);
int verificarMissao(Missao m, const Territorio *t);

// ----------------------

void inicializarTerritorios(Territorio *t) {
    strcpy(t[0].nome, "Norte");
    strcpy(t[0].cor, "Vermelho");
    t[0].tropas = 3;

    strcpy(t[1].nome, "Sul");
    strcpy(t[1].cor, "Verde");
    t[1].tropas = 3;

    strcpy(t[2].nome, "Leste");
    strcpy(t[2].cor, "Azul");
    t[2].tropas = 3;

    strcpy(t[3].nome, "Oeste");
    strcpy(t[3].cor, "Amarelo");
    t[3].tropas = 3;

    strcpy(t[4].nome, "Centro");
    strcpy(t[4].cor, "Verde");
    t[4].tropas = 3;
}

void exibirMapa(const Territorio *t) {
    printf("\n===== ESTADO DO MAPA =====\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%d) %-10s | Cor: %-8s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
    printf("===========================\n");
}

int escolherTerritorio(const char *msg) {
    int x;
    printf("%s (1-%d): ", msg, TOTAL_TERRITORIOS);
    scanf("%d", &x);
    getchar();
    return x - 1; // índice
}

void simularAtaque(Territorio *at, Territorio *def) {
    printf("\nATAQUE: %s (%s) ➝ %s (%s)\n",
           at->nome, at->cor, def->nome, def->cor);

    int dAtq = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;

    printf("🎲 Dados: Atacante = %d | Defensor = %d\n", dAtq, dDef);

    if (dAtq >= dDef) {
        printf("➡️ Atacante venceu o confronto!\n");
        def->tropas--;

        if (def->tropas <= 0) {
            printf("🏴 Território %s foi conquistado!\n", def->nome);
            strcpy(def->cor, at->cor);
            def->tropas = 1;
        }
    } else {
        printf("🛡️ Defensor resistiu!\n");
        at->tropas--;
    }
}

Missao sortearMissao() {
    return (rand() % 2) ? MISSAO_DESTRUIR_VERDE : MISSAO_CONQUISTAR_3;
}

void exibirMissao(Missao m) {
    printf("\n===== SUA MISSÃO =====\n");
    switch (m) {
        case MISSAO_DESTRUIR_VERDE:
            printf("✔ Destruir completamente o Exército VERDE.\n");
            break;
        case MISSAO_CONQUISTAR_3:
            printf("✔ Conquistar 3 territórios inimigos.\n");
            break;
    }
    printf("=======================\n");
}

int verificarMissao(Missao m, const Territorio *t) {
    if (m == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
            if (strcmp(t[i].cor, "Verde") == 0)
                return 0;
        }
        return 1; // venceu
    }

    if (m == MISSAO_CONQUISTAR_3) {
        int conquistas = 0;
        for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
            if (strcmp(t[i].cor, "Vermelho") == 0) // jogador é vermelho
                conquistas++;
        }
        return conquistas >= 3;
    }

    return 0;
}

int main() {
    srand(time(NULL));

    Territorio mapa[TOTAL_TERRITORIOS];
    inicializarTerritorios(mapa);

    Missao missao = sortearMissao();
    exibirMissao(missao);

    int opc = 1;

    while (opc != 0) {
        exibirMapa(mapa);

        printf("\nMENU:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opc);
        getchar();

        if (opc == 1) {
            int at = escolherTerritorio("Escolha o ATACANTE");
            int def = escolherTerritorio("Escolha o DEFENSOR");

            if (at < 0 || at >= TOTAL_TERRITORIOS ||
                def < 0 || def >= TOTAL_TERRITORIOS ||
                at == def) {
                printf("❌ Escolha inválida!\n");
                continue;
            }

            simularAtaque(&mapa[at], &mapa[def]);
        }

        else if (opc == 2) {
            if (verificarMissao(missao, mapa)) {
                printf("\n🎉 PARABÉNS! MISSÃO CONCLUÍDA! 🎉\n");
                break;
            } else {
                printf("\nAinda não concluiu sua missão.\n");
            }
        }
    }

    printf("\nJogo encerrado.\n");
    return 0;
}
