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

// --- Estrutura de Dados ---
// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20]; 
    int quantidade;
} Item;

// Estrutura da lista estática (vetor fixo de até 10 itens)
typedef struct {
    Item itens[MAX_ITENS];
    int quantidade;
} ListaEstatica;


// ==== FUNÇÕES LISTA ESTÁTICA ====

void inicializarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0;
}

// Inserir item
void inserirItem(ListaEstatica *lista, Item novo) {
    if (lista->quantidade == MAX_ITENS) {
        printf("Erro: A mochila está cheia!\n");
        return;
    }
    lista->itens[lista->quantidade] = novo;
    lista->quantidade++;
    printf("Item '%s' inserido com sucesso.\n", novo.nome);
}

// Remover item por nome
void removerItem(ListaEstatica *lista, const char* nome) {
    int i, pos = -1;

    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: Item '%s' não encontrado na mochila.\n", nome);
        return;
    }

    for (i = pos; i < lista->quantidade - 1; i++) {
        lista->itens[i] = lista->itens[i + 1];
    }

    lista->quantidade--;
    printf("Item '%s' removido com sucesso.\n", nome);
}

// Listar todos os itens
void listarItens(const ListaEstatica *lista) {
    int i;
    if (lista->quantidade == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\n=== Itens na mochila ===\n");
    for (i = 0; i < lista->quantidade; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               lista->itens[i].nome,
               lista->itens[i].tipo,
               lista->itens[i].quantidade);
    }
    printf("========================\n");
}

// Buscar item por nome
void buscarItem(const ListaEstatica *lista, const char* nome) {
    int i;
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->itens[i].nome, nome) == 0) {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   lista->itens[i].nome,
                   lista->itens[i].tipo,
                   lista->itens[i].quantidade);
            return;
        }
    }
    printf("Item '%s' não encontrado na mochila.\n", nome);
}

// ==== MENU ====
void menuListaEstatica() {
    ListaEstatica mochila;
    inicializarListaEstatica(&mochila);

    int opcao;
    do {
        printf("\n--- MOCHILA DO JOGADOR (Lista Estática) ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // consumir \n

        if (opcao == 1) {
            Item novo;
            printf("Digite o nome do item: ");
            fgets(novo.nome, sizeof(novo.nome), stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Digite o tipo do item: ");
            fgets(novo.tipo, sizeof(novo.tipo), stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

            printf("Digite a quantidade: ");
            scanf("%d", &novo.quantidade);
            getchar();

            inserirItem(&mochila, novo);

        } else if (opcao == 2) {
            char nome[30];
            printf("Digite o nome do item a remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            removerItem(&mochila, nome);

        } else if (opcao == 3) {
            listarItens(&mochila);

        } else if (opcao == 4) {
            char nome[30];
            printf("Digite o nome do item a buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            buscarItem(&mochila, nome);

        } else if (opcao == 0) {
            printf("Voltando ao menu principal...\n");
        } else {
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

int main() {
    int opcao;
    do {
        printf("\n--- INVENTÁRIO DO JOGADOR ---\n");
        printf("1. Lista Estática (mochila)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            menuListaEstatica();
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
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
