/*
 * AULA 06 - Lista Encadeada
 * 
 * Objetivos:
 * - Entender o conceito de lista encadeada
 * - Implementar operações básicas (CRUD)
 * - Inserir no início, fim e posição
 * - Remover elementos
 * - Buscar e percorrer
 * - Inverter lista
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// DEFINIÇÃO DO NÓ
// ============================================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// ============================================
// FUNÇÕES DA LISTA
// ============================================

// Cria novo nó
Node* criar_node(int valor) {
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return NULL;
    }
    
    novo->data = valor;
    novo->next = NULL;
    return novo;
}

// Insere no início (O(1) - muito eficiente!)
void inserir_inicio(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    novo->next = *head;
    *head = novo;
    
    printf("✅ Inserido %d no início\n", valor);
}

// Insere no fim (O(n) - precisa percorrer)
void inserir_fim(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    // Se lista vazia
    if(*head == NULL) {
        *head = novo;
        printf("✅ Inserido %d (lista estava vazia)\n", valor);
        return;
    }
    
    // Percorre até o último nó
    Node *atual = *head;
    while(atual->next != NULL) {
        atual = atual->next;
    }
    
    atual->next = novo;
    printf("✅ Inserido %d no fim\n", valor);
}

// Insere em posição específica
void inserir_posicao(Node **head, int valor, int pos) {
    if(pos == 0) {
        inserir_inicio(head, valor);
        return;
    }
    
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    Node *atual = *head;
    for(int i = 0; i < pos - 1 && atual != NULL; i++) {
        atual = atual->next;
    }
    
    if(atual == NULL) {
        printf("❌ Posição %d inválida!\n", pos);
        free(novo);
        return;
    }
    
    novo->next = atual->next;
    atual->next = novo;
    printf("✅ Inserido %d na posição %d\n", valor, pos);
}

// Remove primeiro nó com valor específico
int remover_valor(Node **head, int valor) {
    if(*head == NULL) {
        printf("❌ Lista vazia!\n");
        return 0;
    }
    
    Node *temp;
    
    // Se é o primeiro nó
    if((*head)->data == valor) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("✅ Removido %d (era o primeiro)\n", valor);
        return 1;
    }
    
    // Procura o nó
    Node *atual = *head;
    while(atual->next != NULL && atual->next->data != valor) {
        atual = atual->next;
    }
    
    if(atual->next == NULL) {
        printf("❌ Valor %d não encontrado\n", valor);
        return 0;
    }
    
    temp = atual->next;
    atual->next = temp->next;
    free(temp);
    printf("✅ Removido %d\n", valor);
    return 1;
}

// Remove nó na posição específica
int remover_posicao(Node **head, int pos) {
    if(*head == NULL) {
        printf("❌ Lista vazia!\n");
        return 0;
    }
    
    Node *temp;
    
    // Remove primeiro (posição 0)
    if(pos == 0) {
        temp = *head;
        *head = (*head)->next;
        int valor = temp->data;
        free(temp);
        printf("✅ Removido %d da posição 0\n", valor);
        return 1;
    }
    
    // Encontra nó anterior à posição
    Node *atual = *head;
    for(int i = 0; i < pos - 1 && atual->next != NULL; i++) {
        atual = atual->next;
    }
    
    if(atual->next == NULL) {
        printf("❌ Posição %d inválida!\n", pos);
        return 0;
    }
    
    temp = atual->next;
    atual->next = temp->next;
    int valor = temp->data;
    free(temp);
    printf("✅ Removido %d da posição %d\n", valor, pos);
    return 1;
}

// Busca valor
Node* buscar(Node *head, int valor) {
    Node *atual = head;
    int pos = 0;
    
    while(atual != NULL) {
        if(atual->data == valor) {
            printf("✅ Encontrado %d na posição %d\n", valor, pos);
            return atual;
        }
        atual = atual->next;
        pos++;
    }
    
    printf("❌ Valor %d não encontrado\n", valor);
    return NULL;
}

// Conta nós
int contar(Node *head) {
    int count = 0;
    Node *atual = head;
    
    while(atual != NULL) {
        count++;
        atual = atual->next;
    }
    
    return count;
}

// Imprime lista
void imprimir(Node *head) {
    if(head == NULL) {
        printf("Lista vazia: NULL\n");
        return;
    }
    
    printf("Lista: ");
    Node *atual = head;
    while(atual != NULL) {
        printf("%d", atual->data);
        if(atual->next != NULL) printf(" -> ");
        atual = atual->next;
    }
    printf(" -> NULL\n");
}

// Inverte lista
void inverter(Node **head) {
    Node *anterior = NULL;
    Node *atual = *head;
    Node *proximo = NULL;
    
    while(atual != NULL) {
        proximo = atual->next;  // salva próximo
        atual->next = anterior;  // inverte link
        anterior = atual;        // avança anterior
        atual = proximo;         // avança atual
    }
    
    *head = anterior;
    printf("✅ Lista invertida\n");
}

// Limpa lista (libera toda memória)
void liberar(Node **head) {
    Node *atual = *head;
    Node *temp;
    int count = 0;
    
    while(atual != NULL) {
        temp = atual;
        atual = atual->next;
        free(temp);
        count++;
    }
    
    *head = NULL;
    printf("✅ %d nós liberados da memória\n", count);
}

// ============================================
// MAIN - DEMONSTRAÇÃO COMPLETA
// ============================================

int main() {
    printf("=== AULA 06: LISTA ENCADEADA ===\n\n");
    
    Node *lista = NULL;
    
    // ==========================================
    // PARTE 1: INSERÇÃO
    // ==========================================
    printf("--- PARTE 1: Inserção ---\n");
    
    printf("\nInserindo no início:\n");
    inserir_inicio(&lista, 10);
    inserir_inicio(&lista, 20);
    inserir_inicio(&lista, 30);
    imprimir(lista);
    
    printf("\nInserindo no fim:\n");
    inserir_fim(&lista, 5);
    inserir_fim(&lista, 1);
    imprimir(lista);
    
    printf("\nInserindo na posição 2:\n");
    inserir_posicao(&lista, 15, 2);
    imprimir(lista);
    printf("\n");
    
    // ==========================================
    // PARTE 2: BUSCA E CONTAGEM
    // ==========================================
    printf("--- PARTE 2: Busca e Contagem ---\n");
    
    buscar(lista, 15);
    buscar(lista, 100);
    
    int total = contar(lista);
    printf("Total de elementos: %d\n\n", total);
    
    // ==========================================
    // PARTE 3: REMOÇÃO
    // ==========================================
    printf("--- PARTE 3: Remoção ---\n");
    
    printf("\nLista atual:\n");
    imprimir(lista);
    
    printf("\nRemovendo valor 15:\n");
    remover_valor(&lista, 15);
    imprimir(lista);
    
    printf("\nRemovendo posição 0 (primeiro):\n");
    remover_posicao(&lista, 0);
    imprimir(lista);
    
    printf("\nTentando remover valor inexistente:\n");
    remover_valor(&lista, 999);
    printf("\n");
    
    // ==========================================
    // PARTE 4: INVERSÃO
    // ==========================================
    printf("--- PARTE 4: Inversão ---\n");
    
    printf("\nANTES da inversão:\n");
    imprimir(lista);
    
    inverter(&lista);
    
    printf("DEPOIS da inversão:\n");
    imprimir(lista);
    printf("\n");
    
    // ==========================================
    // PARTE 5: LIMPEZA
    // ==========================================
    printf("--- PARTE 5: Liberando Memória ---\n\n");
    
    liberar(&lista);
    imprimir(lista);
    printf("\n");
    
    // ==========================================
    // PARTE 6: EXEMPLO COMPLETO
    // ==========================================
    printf("--- PARTE 6: Exemplo Completo ---\n");
    
    Node *numeros = NULL;
    
    printf("\n🔹 Criando lista: 1, 2, 3, 4, 5\n");
    for(int i = 1; i <= 5; i++) {
        inserir_fim(&numeros, i);
    }
    imprimir(numeros);
    
    printf("\n🔹 Inserindo 0 no início:\n");
    inserir_inicio(&numeros, 0);
    imprimir(numeros);
    
    printf("\n🔹 Inserindo 6 no fim:\n");
    inserir_fim(&numeros, 6);
    imprimir(numeros);
    
    printf("\n🔹 Removendo 3:\n");
    remover_valor(&numeros, 3);
    imprimir(numeros);
    
    printf("\n🔹 Invertendo:\n");
    inverter(&numeros);
    imprimir(numeros);
    
    printf("\n🔹 Informações:\n");
    printf("Quantidade de elementos: %d\n", contar(numeros));
    
    printf("\n🔹 Liberando memória:\n");
    liberar(&numeros);
    
    printf("\n=== FIM DA AULA 06 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * ESTRUTURA:
 * - Node contém: data (valor) e next (ponteiro)
 * - Head aponta para primeiro nó
 * - Último nó aponta para NULL
 * 
 * OPERAÇÕES E COMPLEXIDADE:
 * - Inserir início: O(1) ⚡ super rápido
 * - Inserir fim: O(n) 🐌 precisa percorrer
 * - Remover: O(n) 🐌 precisa buscar
 * - Buscar: O(n) 🐌 linear
 * - Inverter: O(n) 🔄 percorre uma vez
 * 
 * VANTAGENS:
 * ✅ Tamanho dinâmico (cresce/diminui)
 * ✅ Inserção/remoção no início: O(1)
 * ✅ Não precisa memória contígua
 * ✅ Fácil inserir/remover no meio
 * 
 * DESVANTAGENS:
 * ❌ Acesso não é O(1) (precisa percorrer)
 * ❌ Usa mais memória (ponteiro extra por nó)
 * ❌ Busca sempre linear O(n)
 * ❌ Cache miss (nós espalhados na memória)
 * 
 * QUANDO USAR:
 * ✅ Muitas inserções/remoções
 * ✅ Tamanho variável desconhecido
 * ✅ Acesso sequencial (não aleatório)
 * ❌ Não use se precisa acesso rápido por índice
 * 
 * PRÓXIMA AULA: Pilha e Fila
 */
