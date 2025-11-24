#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

typedef enum {
    MISSAO_DESTRUIR_VERDE = 1,
    MISSAO_CONQUISTAR_3 = 2
} Missao;

// ======= DECLARAÇÃO DAS FUNÇÕES =======
void inicializarTerritorios(Territorio *mapa);
void exibirMapa(const Territorio *mapa);
int menuPrincipal();
void realizarAtaque(Territorio *mapa);
void batalhar(Territorio *atacante, Territorio *defensor);
Missao sortearMissao();
void exibirMissao(Missao m);
int verificarMissao(const Territorio *mapa, Missao m);

// ======= PROGRAMA PRINCIPAL =======
int main() {
    srand(time(NULL));

    Territorio mapa[N_TERRITORIOS];
    inicializarTerritorios(mapa);

    Missao missaoJogador = sortearMissao();

    printf("=== MISSÃO SORTEADA ===\n");
    exibirMissao(missaoJogador);

    int opcao;

    while ((opcao = menuPrincipal()) != 0) {
        switch (opcao) {
            case 1:
                realizarAtaque(mapa);
                break;

            case 2:
                if (verificarMissao(mapa, missaoJogador)) {
                    printf("\n🎉 PARABÉNS! Você completou a missão!\n");
                    return 0;
                } else {
                    printf("\n📌 Missão ainda não concluída.\n");
                    exibirMissao(missaoJogador);
                }
                break;

            default:
                printf("\n❌ Opção inválida!\n");
        }
    }

    printf("\nJogo encerrado.\n");
    return 0;
}

// ======= FUNÇÕES =======

// Inicialização automática
void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};
    const int tropasIniciais[] = {5, 4, 6, 3, 4};

    for (int i = 0; i < N_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropasIniciais[i];
    }
}

void exibirMapa(const Territorio *mapa) {
    printf("\n==== MAPA ATUAL ====\n");
    for (int i = 0; i < N_TERRITORIOS; i++) {
        printf("%d) %-10s | Cor: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

int menuPrincipal() {
    printf("\n===== MENU =====\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("Escolha: ");

    int op;
    scanf("%d", &op);
    return op;
}

void realizarAtaque(Territorio *mapa) {
    exibirMapa(mapa);

    int a, d;
    printf("\nEscolha ATACANTE (1 a 5): ");
    scanf("%d", &a);
    printf("Escolha DEFENSOR (1 a 5): ");
    scanf("%d", &d);

    if (a < 1 || a > 5 || d < 1 || d > 5 || a == d) {
        printf("\n❌ Ataque inválido!\n");
        return;
    }

    batalhar(&mapa[a - 1], &mapa[d - 1]);
}

void batalhar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n🎲 Dados:\n");
    printf("Atacante (%s, %s): %d\n", atacante->nome, atacante->cor, dadoA);
    printf("Defensor  (%s, %s): %d\n", defensor->nome, defensor->cor, dadoD);

    if (dadoA >= dadoD) {
        printf("\n🔥 Ataque bem-sucedido!\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("🏴 Território %s foi conquistado!\n", defensor->nome);

            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
        }
    } else {
        printf("\n🛡 Defesa bem-sucedida! Atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

// Sorteia a missão do jogador
Missao sortearMissao() {
    int r = rand() % 2; // 0 ou 1
    return (r == 0) ? MISSAO_DESTRUIR_VERDE : MISSAO_CONQUISTAR_3;
}

// Exibe descrição da missão
void exibirMissao(Missao m) {
    printf("\n🎯 Sua missão: ");
    if (m == MISSAO_DESTRUIR_VERDE) {
        printf("Destruir completamente o exército Verde.\n");
    } else {
        printf("Conquistar 3 territórios inimigos.\n");
    }
}

// Verifica se a missão foi concluída
int verificarMissao(const Territorio *mapa, Missao m) {
    if (m == MISSAO_DESTRUIR_VERDE) {

        for (int i = 0; i < N_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                return 0; // ainda existe território verde vivo
            }
        }
        return 1; // todos verdes eliminados

    } else if (m == MISSAO_CONQUISTAR_3) {

        // contar quantos territórios têm a mesma cor do jogador inicial
        // o jogador é o dono da cor do território 1 (por exemplo)
        const char *corJogador = mapa[0].cor;
        int count = 0;

        for (int i = 0; i < N_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                count++;
            }
        }

        return count >= 3;
    }

    return 0;
}
