/*
 * AULA 07 - Pilha (Stack) e Fila (Queue)
 * 
 * Objetivos:
 * - Entender LIFO (Last In First Out) - Pilha
 * - Entender FIFO (First In First Out) - Fila
 * - Implementar pilha com lista encadeada
 * - Implementar fila com lista encadeada
 * - Aplicações práticas
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// PILHA (STACK) - LIFO
// ============================================

typedef struct NodeStack {
    int data;
    struct NodeStack *next;
} NodeStack;

typedef struct {
    NodeStack *topo;
    int tamanho;
} Pilha;

// Cria pilha vazia
Pilha* criar_pilha() {
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    if(pilha == NULL) return NULL;
    
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Verifica se está vazia
int pilha_vazia(Pilha *pilha) {
    return pilha == NULL || pilha->topo == NULL;
}

// Empilha (push) - adiciona no topo
void empilhar(Pilha *pilha, int valor) {
    if(pilha == NULL) return;
    
    NodeStack *novo = (NodeStack*) malloc(sizeof(NodeStack));
    if(novo == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return;
    }
    
    novo->data = valor;
    novo->next = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    
    printf("⬆️  PUSH: %d empilhado\n", valor);
}

// Desempilha (pop) - remove do topo
int desempilhar(Pilha *pilha, int *valor) {
    if(pilha_vazia(pilha)) {
        printf("❌ Pilha vazia! Não pode desempilhar.\n");
        return 0;
    }
    
    NodeStack *temp = pilha->topo;
    *valor = temp->data;
    
    pilha->topo = pilha->topo->next;
    pilha->tamanho--;
    
    free(temp);
    printf("⬇️  POP: %d desempilhado\n", *valor);
    return 1;
}

// Consulta topo (peek) - vê sem remover
int topo(Pilha *pilha, int *valor) {
    if(pilha_vazia(pilha)) {
        printf("❌ Pilha vazia!\n");
        return 0;
    }
    
    *valor = pilha->topo->data;
    return 1;
}

// Tamanho da pilha
int tamanho_pilha(Pilha *pilha) {
    return pilha == NULL ? 0 : pilha->tamanho;
}

// Imprime pilha
void imprimir_pilha(Pilha *pilha) {
    if(pilha_vazia(pilha)) {
        printf("Pilha: [] (vazia)\n");
        return;
    }
    
    printf("Pilha (topo → base): [ ");
    NodeStack *atual = pilha->topo;
    while(atual != NULL) {
        printf("%d ", atual->data);
        atual = atual->next;
    }
    printf("]\n");
}

// Destroi pilha
void destruir_pilha(Pilha **pilha) {
    if(pilha == NULL || *pilha == NULL) return;
    
    int valor;
    while(!pilha_vazia(*pilha)) {
        desempilhar(*pilha, &valor);
    }
    
    free(*pilha);
    *pilha = NULL;
    printf("✅ Pilha destruída\n");
}

// ============================================
// FILA (QUEUE) - FIFO
// ============================================

typedef struct NodeQueue {
    int data;
    struct NodeQueue *next;
} NodeQueue;

typedef struct {
    NodeQueue *inicio;  // frente da fila
    NodeQueue *fim;     // final da fila
    int tamanho;
} Fila;

// Cria fila vazia
Fila* criar_fila() {
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    if(fila == NULL) return NULL;
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

// Verifica se está vazia
int fila_vazia(Fila *fila) {
    return fila == NULL || fila->inicio == NULL;
}

// Enfileira (enqueue) - adiciona no fim
void enfileirar(Fila *fila, int valor) {
    if(fila == NULL) return;
    
    NodeQueue *novo = (NodeQueue*) malloc(sizeof(NodeQueue));
    if(novo == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return;
    }
    
    novo->data = valor;
    novo->next = NULL;
    
    if(fila_vazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->next = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
    printf("➡️  ENQUEUE: %d entrou na fila\n", valor);
}

// Desenfileira (dequeue) - remove do início
int desenfileirar(Fila *fila, int *valor) {
    if(fila_vazia(fila)) {
        printf("❌ Fila vazia! Não pode desenfileirar.\n");
        return 0;
    }
    
    NodeQueue *temp = fila->inicio;
    *valor = temp->data;
    
    fila->inicio = fila->inicio->next;
    
    if(fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    fila->tamanho--;
    free(temp);
    printf("⬅️  DEQUEUE: %d saiu da fila\n", *valor);
    return 1;
}

// Consulta primeiro (peek)
int primeiro(Fila *fila, int *valor) {
    if(fila_vazia(fila)) {
        printf("❌ Fila vazia!\n");
        return 0;
    }
    
    *valor = fila->inicio->data;
    return 1;
}

// Tamanho da fila
int tamanho_fila(Fila *fila) {
    return fila == NULL ? 0 : fila->tamanho;
}

// Imprime fila
void imprimir_fila(Fila *fila) {
    if(fila_vazia(fila)) {
        printf("Fila: [] (vazia)\n");
        return;
    }
    
    printf("Fila (início → fim): [ ");
    NodeQueue *atual = fila->inicio;
    while(atual != NULL) {
        printf("%d ", atual->data);
        atual = atual->next;
    }
    printf("]\n");
}

// Destroi fila
void destruir_fila(Fila **fila) {
    if(fila == NULL || *fila == NULL) return;
    
    int valor;
    while(!fila_vazia(*fila)) {
        desenfileirar(*fila, &valor);
    }
    
    free(*fila);
    *fila = NULL;
    printf("✅ Fila destruída\n");
}

// ============================================
// MAIN - DEMONSTRAÇÃO
// ============================================

int main() {
    printf("=== AULA 07: PILHA E FILA ===\n\n");
    
    // ==========================================
    // PARTE 1: PILHA (LIFO)
    // ==========================================
    printf("╔════════════════════════════════╗\n");
    printf("║    PILHA (STACK) - LIFO        ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    Pilha *pilha = criar_pilha();
    
    printf("--- Empilhando elementos ---\n");
    empilhar(pilha, 10);
    empilhar(pilha, 20);
    empilhar(pilha, 30);
    empilhar(pilha, 40);
    
    printf("\n");
    imprimir_pilha(pilha);
    printf("Tamanho: %d elementos\n\n", tamanho_pilha(pilha));
    
    printf("--- Consultando topo ---\n");
    int valor_topo;
    if(topo(pilha, &valor_topo)) {
        printf("👀 Topo: %d (sem remover)\n\n", valor_topo);
    }
    
    printf("--- Desempilhando (LIFO: último a entrar, primeiro a sair) ---\n");
    int valor;
    while(!pilha_vazia(pilha)) {
        desempilhar(pilha, &valor);
    }
    
    printf("\n");
    imprimir_pilha(pilha);
    printf("\n");
    
    // Tentando desempilhar de pilha vazia
    printf("--- Tentando desempilhar de pilha vazia ---\n");
    desempilhar(pilha, &valor);
    printf("\n");
    
    destruir_pilha(&pilha);
    printf("\n");
    
    // ==========================================
    // PARTE 2: FILA (FIFO)
    // ==========================================
    printf("╔════════════════════════════════╗\n");
    printf("║     FILA (QUEUE) - FIFO        ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    Fila *fila = criar_fila();
    
    printf("--- Enfileirando elementos ---\n");
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);
    enfileirar(fila, 40);
    
    printf("\n");
    imprimir_fila(fila);
    printf("Tamanho: %d elementos\n\n", tamanho_fila(fila));
    
    printf("--- Consultando primeiro ---\n");
    int primeiro_valor;
    if(primeiro(fila, &primeiro_valor)) {
        printf("👀 Primeiro: %d (sem remover)\n\n", primeiro_valor);
    }
    
    printf("--- Desenfileirando (FIFO: primeiro a entrar, primeiro a sair) ---\n");
    while(!fila_vazia(fila)) {
        desenfileirar(fila, &valor);
    }
    
    printf("\n");
    imprimir_fila(fila);
    printf("\n");
    
    // Tentando desenfileirar de fila vazia
    printf("--- Tentando desenfileirar de fila vazia ---\n");
    desenfileirar(fila, &valor);
    printf("\n");
    
    destruir_fila(&fila);
    printf("\n");
    
    // ==========================================
    // PARTE 3: COMPARAÇÃO VISUAL
    // ==========================================
    printf("╔════════════════════════════════╗\n");
    printf("║      COMPARAÇÃO VISUAL         ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    printf("PILHA (LIFO):\n");
    printf("  ┌───┐\n");
    printf("  │ 3 │ ← TOPO (último a entrar, primeiro a sair)\n");
    printf("  ├───┤\n");
    printf("  │ 2 │\n");
    printf("  ├───┤\n");
    printf("  │ 1 │\n");
    printf("  └───┘\n\n");
    
    printf("FILA (FIFO):\n");
    printf("  INÍCIO → [1] [2] [3] ← FIM\n");
    printf("           ↑           ↑\n");
    printf("        sai aqui   entra aqui\n");
    printf("  (primeiro a entrar, primeiro a sair)\n\n");
    
    // ==========================================
    // PARTE 4: APLICAÇÕES PRÁTICAS
    // ==========================================
    printf("╔════════════════════════════════╗\n");
    printf("║      APLICAÇÕES PRÁTICAS       ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    printf("📚 PILHA (LIFO) é usada em:\n");
    printf("  • Desfazer/Refazer (Ctrl+Z)\n");
    printf("  • Navegação de páginas (botão voltar)\n");
    printf("  • Chamadas de funções (call stack)\n");
    printf("  • Expressões matemáticas (pós-fixa)\n");
    printf("  • Validação de parênteses\n\n");
    
    printf("🎫 FILA (FIFO) é usada em:\n");
    printf("  • Fila de impressão\n");
    printf("  • Buffer de teclado\n");
    printf("  • Atendimento (primeiro que chega, primeiro atendido)\n");
    printf("  • Processamento de tarefas (job queue)\n");
    printf("  • Breadth-First Search (BFS)\n\n");
    
    printf("=== FIM DA AULA 07 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * PILHA (STACK) - LIFO:
 * =====================
 * - Último a entrar, primeiro a sair
 * - Operações principais: push, pop, peek
 * - Todas operações: O(1)
 * - Analogia: pilha de pratos
 * 
 * FILA (QUEUE) - FIFO:
 * ====================
 * - Primeiro a entrar, primeiro a sair
 * - Operações principais: enqueue, dequeue, peek
 * - Todas operações: O(1)
 * - Analogia: fila de banco
 * 
 * DIFERENÇAS:
 * ===========
 * | Operação    | Pilha    | Fila       |
 * |-------------|----------|------------|
 * | Adicionar   | push     | enqueue    |
 * | Remover     | pop      | dequeue    |
 * | Consultar   | peek/top | front/peek |
 * | Ordem       | LIFO     | FIFO       |
 * 
 * IMPLEMENTAÇÃO:
 * ==============
 * - Ambas podem usar lista encadeada
 * - Ambas podem usar array (circular para fila)
 * - Lista encadeada: tamanho dinâmico
 * - Array: tamanho fixo mas acesso mais rápido
 * 
 * PRÓXIMA AULA: Árvore Binária de Busca
 */
