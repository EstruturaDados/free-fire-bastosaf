// ============================================================================
//         PROJETO FREE FIRE - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Simular o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// - Introduzir ordenação com critérios e busca binária para otimizar a gestão dos recursos.
//
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Constantes Globais ---
#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// --- Estrutura de Dados ---
// Estrutura que representa um item da mochila
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Estrutura da lista sequencial (vetor)
typedef struct {
    Item itens[MAX_ITENS];
    int qtd;
} MochilaVetor;

// Estrutura da lista encadeada
typedef struct No {
    Item dados;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
} MochilaLista;


// ==== FUNÇÕES LISTA SEQUENCIAL ====
void inicializarVetor(MochilaVetor* m) {
    m->qtd = 0;
}

void inserirItemVetor(MochilaVetor* m, Item it) {
    if (m->qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    m->itens[m->qtd++] = it;
    printf("Item %s inserido no vetor.\n", it.nome);
}

void removerItemVetor(MochilaVetor* m, const char* nome) {
    int i, j, pos = -1;
    for (i = 0; i < m->qtd; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Item %s não encontrado no vetor.\n", nome);
        return;
    }
    for (j = pos; j < m->qtd - 1; j++) {
        m->itens[j] = m->itens[j+1];
    }
    m->qtd--;
    printf("Item %s removido do vetor.\n", nome);
}

void listarVetor(const MochilaVetor* m) {
    int i;
    printf("Mochila (vetor):\n");
    for (i = 0; i < m->qtd; i++) {
        printf("- %s | Tipo: %s | Qtd: %d\n", 
            m->itens[i].nome, m->itens[i].tipo, m->itens[i].quantidade);
    }
}

int buscarSequencialVetor(const MochilaVetor* m, const char* nome, int* comparacoes) {
    int i;
    *comparacoes = 0;
    for (i = 0; i < m->qtd; i++) {
        (*comparacoes)++;
        if (strcmp(m->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(MochilaVetor* m) {
    int i, j;
    for (i = 0; i < m->qtd - 1; i++) {
        for (j = 0; j < m->qtd - i - 1; j++) {
            if (strcmp(m->itens[j].nome, m->itens[j+1].nome) > 0) {
                Item tmp = m->itens[j];
                m->itens[j] = m->itens[j+1];
                m->itens[j+1] = tmp;
            }
        }
    }
}

int buscarBinariaVetor(const MochilaVetor* m, const char* nome, int* comparacoes) {
    int esq = 0, dir = m->qtd - 1, meio;
    *comparacoes = 0;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(m->itens[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

// ==== FUNÇÕES LISTA ENCADEADA ====
void inicializarLista(MochilaLista* m) {
    m->inicio = NULL;
}

void inserirItemLista(MochilaLista* m, Item it) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação!\n");
        return;
    }
    novo->dados = it;
    novo->prox = m->inicio;
    m->inicio = novo;
    printf("Item %s inserido na lista.\n", it.nome);
}

void removerItemLista(MochilaLista* m, const char* nome) {
    No* atual = m->inicio;
    No* anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Item %s não encontrado na lista.\n", nome);
        return;
    }
    if (anterior == NULL) m->inicio = atual->prox;
    else anterior->prox = atual->prox;
    free(atual);
    printf("Item %s removido da lista.\n", nome);
}

void listarLista(const MochilaLista* m) {
    No* atual = m->inicio;
    printf("Mochila (lista encadeada):\n");
    while (atual != NULL) {
        printf("- %s | Tipo: %s | Qtd: %d\n",
            atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->prox;
    }
}

No* buscarSequencialLista(const MochilaLista* m, const char* nome, int* comparacoes) {
    No* atual = m->inicio;
    *comparacoes = 0;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void liberarLista(MochilaLista* m) {
    No* atual = m->inicio;
    while (atual != NULL) {
        No* tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    m->inicio = NULL;
}

int main() {
    MochilaVetor mochilaV;
    MochilaLista mochilaL;
    int opcao, comparacoes, pos;
    char nomeBusca[MAX_NOME];

    inicializarVetor(&mochilaV);
    inicializarLista(&mochilaL);

    do {
        printf("\n===== MENU MOCHILA =====\n");
        printf("1. Inserir item no vetor\n");
        printf("2. Remover item do vetor\n");
        printf("3. Listar vetor\n");
        printf("4. Buscar item (sequencial - vetor)\n");
        printf("5. Ordenar vetor e buscar (binaria)\n");
        printf("6. Inserir item na lista\n");
        printf("7. Remover item da lista\n");
        printf("8. Listar lista\n");
        printf("9. Buscar item (sequencial - lista)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Item it;
            printf("Nome: "); scanf("%s", it.nome);
            printf("Tipo: "); scanf("%s", it.tipo);
            printf("Quantidade: "); scanf("%d", &it.quantidade);
            inserirItemVetor(&mochilaV, it);
        }
        else if (opcao == 2) {
            printf("Nome do item para remover: ");
            scanf("%s", nomeBusca);
            removerItemVetor(&mochilaV, nomeBusca);
        }
        else if (opcao == 3) {
            listarVetor(&mochilaV);
        }
        else if (opcao == 4) {
            printf("Nome do item para buscar: ");
            scanf("%s", nomeBusca);
            pos = buscarSequencialVetor(&mochilaV, nomeBusca, &comparacoes);
            if (pos != -1) {
                printf("Item encontrado no vetor em %d comparacoes.\n", comparacoes);
            } else {
                printf("Item não encontrado (%d comparacoes).\n", comparacoes);
            }
        }
        else if (opcao == 5) {
            printf("Nome do item para busca binária: ");
            scanf("%s", nomeBusca);
            ordenarVetor(&mochilaV);
            pos = buscarBinariaVetor(&mochilaV, nomeBusca, &comparacoes);
            if (pos != -1) {
                printf("Item encontrado no vetor em %d comparacoes.\n", comparacoes);
            } else {
                printf("Item não encontrado (%d comparacoes).\n", comparacoes);
            }
        }
        else if (opcao == 6) {
            Item it;
            printf("Nome: "); scanf("%s", it.nome);
            printf("Tipo: "); scanf("%s", it.tipo);
            printf("Quantidade: "); scanf("%d", &it.quantidade);
            inserirItemLista(&mochilaL, it);
        }
        else if (opcao == 7) {
            printf("Nome do item para remover: ");
            scanf("%s", nomeBusca);
            removerItemLista(&mochilaL, nomeBusca);
        }
        else if (opcao == 8) {
            listarLista(&mochilaL);
        }
        else if (opcao == 9) {
            No* resultado;
            printf("Nome do item para buscar: ");
            scanf("%s", nomeBusca);
            resultado = buscarSequencialLista(&mochilaL, nomeBusca, &comparacoes);
            if (resultado != NULL) {
                printf("Item encontrado na lista em %d comparacoes.\n", comparacoes);
            } else {
                printf("Item não encontrado na lista (%d comparacoes).\n", comparacoes);
            }
        }
    } while (opcao != 0);

    liberarLista(&mochilaL);
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
