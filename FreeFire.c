// ============================================================================
//         PROJETO FREE FIRE - DESAFIO DE CÓDIGO (Versão Final C99)
// ============================================================================
// 
// OBJETIVO:
// - Implementar um sistema de gerenciamento de componentes (itens) para a
//   missão final do jogo "Free Fire".
// - Permite cadastrar, listar, ordenar e buscar componentes de forma eficiente.
//
// RECURSOS PRINCIPAIS:
// - Estrutura de dados baseada em vetor de structs
// - Algoritmos de ordenação: Bubble Sort, Insertion Sort e Selection Sort
// - Busca Binária com contagem de comparações
// - Medição do tempo de execução
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// --- Constantes Globais ---
#define MAX_COMPONENTES 10
#define MAX_NOME 30
#define MAX_TIPO 20

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];   // Nome do componente
    char tipo[MAX_TIPO];   // Tipo do componente (Ex: arma, veículo, suprimento)
    int prioridade;        // Nível de importância (1-10)
} Componente;

// ==== FUNÇÕES AUXILIARES ====
// Exibe todos os componentes formatados
void mostrarComponentes(Componente v[], int n) {
    int i;
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (i = 0; i < n; i++) {
        printf("%2d) Nome: %-15s | Tipo: %-12s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("----------------------------\n");
}

// Troca dois elementos de posição no vetor
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ==== ALGORITMOS DE ORDENAÇÃO ====
// --- Bubble Sort (ordena por nome em ordem alfabética) ---
void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    int i, j;
    *comparacoes = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

// --- Insertion Sort (ordena por tipo) ---
void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    int i, j;
    Componente chave;
    *comparacoes = 0;

    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// --- Selection Sort (ordena por prioridade em ordem crescente) ---
void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    int i, j, min;
    *comparacoes = 0;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) trocar(&v[i], &v[min]);
    }
}

// ==== BUSCA BINÁRIA ====
// Realiza busca binária pelo nome 
int buscaBinariaPorNome(Componente v[], int n, const char *chave, int *comparacoes) {
    int esq = 0, dir = n - 1, meio, cmp;
    *comparacoes = 0;

    while (esq <= dir) {
        meio = (esq + dir) / 2;
        (*comparacoes)++;
        cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1;
}

int main(void) {
    Componente comps[MAX_COMPONENTES];
    int n = 0;
    int opcao, comparacoes, pos;
    char nomeBusca[MAX_NOME];
    clock_t inicio, fim;
    double tempo;

    do {
        printf("\n===== MENU TORRE DE FUGA =====\n");
        printf("1. Cadastrar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Busca binária por nome (requer ordenação por nome)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch (opcao) {
            case 1:
                if (n >= MAX_COMPONENTES) {
                    printf("Limite máximo de componentes atingido!\n");
                } else {
                    printf("Nome: ");
                    fgets(comps[n].nome, MAX_NOME, stdin);
                    comps[n].nome[strcspn(comps[n].nome, "\n")] = '\0';

                    printf("Tipo: ");
                    fgets(comps[n].tipo, MAX_TIPO, stdin);
                    comps[n].tipo[strcspn(comps[n].tipo, "\n")] = '\0';

                    printf("Prioridade (1-10): ");
                    scanf("%d", &comps[n].prioridade);
                    getchar();

                    n++;
                    printf("Componente cadastrado com sucesso!\n");
                }
                break;

            case 2:
                if (n == 0) printf("Nenhum componente cadastrado.\n");
                else mostrarComponentes(comps, n);
                break;

            case 3:
                inicio = clock();
                bubbleSortNome(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenação concluída (Bubble Sort - Nome)\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(comps, n);
                break;

            case 4:
                inicio = clock();
                insertionSortTipo(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenação concluída (Insertion Sort - Tipo)\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(comps, n);
                break;

            case 5:
                inicio = clock();
                selectionSortPrioridade(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenação concluída (Selection Sort - Prioridade)\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(comps, n);
                break;

            case 6:
                if (n == 0) {
                    printf("Nenhum componente disponível para busca.\n");
                } else {
                    printf("Digite o nome do componente a buscar: ");
                    fgets(nomeBusca, MAX_NOME, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    pos = buscaBinariaPorNome(comps, n, nomeBusca, &comparacoes);
                    if (pos != -1) {
                        printf("Componente '%s' encontrado na posição %d (%d comparações)\n",
                               comps[pos].nome, pos + 1, comparacoes);
                    } else {
                        printf("Componente '%s' não encontrado (%d comparações)\n",
                               nomeBusca, comparacoes);
                    }
                }
                break;

            case 0:
                printf("Encerrando o sistema. Missão concluída!\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}