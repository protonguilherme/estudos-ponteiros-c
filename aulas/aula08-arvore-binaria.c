/*
 * AULA 08 - Árvore Binária de Busca (BST)
 * 
 * Objetivos:
 * - Entender estrutura de árvore binária
 * - Implementar inserção ordenada
 * - Buscar elementos (O(log n) no melhor caso)
 * - Percorrer: in-order, pre-order, post-order
 * - Calcular altura e contar nós
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// DEFINIÇÃO DO NÓ
// ============================================

typedef struct TreeNode {
    int data;
    struct TreeNode *esquerda;
    struct TreeNode *direita;
} TreeNode;

// ============================================
// FUNÇÕES DA ÁRVORE
// ============================================

// Cria novo nó
TreeNode* criar_node(int valor) {
    TreeNode *novo = (TreeNode*) malloc(sizeof(TreeNode));
    if(novo == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return NULL;
    }
    
    novo->data = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere ordenadamente (recursivo)
TreeNode* inserir(TreeNode *raiz, int valor) {
    // Caso base: encontrou posição vazia
    if(raiz == NULL) {
        printf("✅ Inserido: %d\n", valor);
        return criar_node(valor);
    }
    
    // Menor: vai para esquerda
    if(valor < raiz->data) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    // Maior: vai para direita
    else if(valor > raiz->data) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    // Igual: não insere duplicatas
    else {
        printf("⚠️  Valor %d já existe (não inserido)\n", valor);
    }
    
    return raiz;
}

// Busca valor (recursivo)
TreeNode* buscar(TreeNode *raiz, int valor) {
    // Caso base: não encontrou ou achou
    if(raiz == NULL) {
        printf("❌ Valor %d não encontrado\n", valor);
        return NULL;
    }
    
    if(raiz->data == valor) {
        printf("✅ Valor %d encontrado!\n", valor);
        return raiz;
    }
    
    // Busca na subárvore apropriada
    if(valor < raiz->data) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

// Encontra menor valor (nó mais à esquerda)
TreeNode* encontrar_minimo(TreeNode *raiz) {
    if(raiz == NULL) return NULL;
    
    TreeNode *atual = raiz;
    while(atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Encontra maior valor (nó mais à direita)
TreeNode* encontrar_maximo(TreeNode *raiz) {
    if(raiz == NULL) return NULL;
    
    TreeNode *atual = raiz;
    while(atual->direita != NULL) {
        atual = atual->direita;
    }
    return atual;
}

// Remove nó (recursivo - complexo!)
TreeNode* remover(TreeNode *raiz, int valor) {
    if(raiz == NULL) {
        printf("❌ Valor %d não encontrado para remover\n", valor);
        return NULL;
    }
    
    // Busca o nó
    if(valor < raiz->data) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if(valor > raiz->data) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Encontrou o nó a remover
        
        // Caso 1: Nó folha (sem filhos)
        if(raiz->esquerda == NULL && raiz->direita == NULL) {
            printf("✅ Removido %d (folha)\n", valor);
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho (direita)
        else if(raiz->esquerda == NULL) {
            TreeNode *temp = raiz->direita;
            printf("✅ Removido %d (1 filho direito)\n", valor);
            free(raiz);
            return temp;
        }
        // Caso 2: Nó com um filho (esquerda)
        else if(raiz->direita == NULL) {
            TreeNode *temp = raiz->esquerda;
            printf("✅ Removido %d (1 filho esquerdo)\n", valor);
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            // Encontra sucessor (menor da subárvore direita)
            TreeNode *sucessor = encontrar_minimo(raiz->direita);
            
            // Substitui valor
            raiz->data = sucessor->data;
            
            // Remove o sucessor
            raiz->direita = remover(raiz->direita, sucessor->data);
            printf("✅ Removido %d (2 filhos - substituído por %d)\n", 
                   valor, raiz->data);
        }
    }
    
    return raiz;
}

// Altura da árvore (recursivo)
int altura(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    int altura_esq = altura(raiz->esquerda);
    int altura_dir = altura(raiz->direita);
    
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

// Conta total de nós (recursivo)
int contar_nos(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    return 1 + contar_nos(raiz->esquerda) + contar_nos(raiz->direita);
}

// Conta nós folha
int contar_folhas(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    if(raiz->esquerda == NULL && raiz->direita == NULL) {
        return 1;  // é folha
    }
    
    return contar_folhas(raiz->esquerda) + contar_folhas(raiz->direita);
}

// ============================================
// PERCURSOS (TRAVERSALS)
// ============================================

// In-order: Esquerda → Raiz → Direita (ordem crescente!)
void in_order(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    in_order(raiz->esquerda);
    printf("%d ", raiz->data);
    in_order(raiz->direita);
}

// Pre-order: Raiz → Esquerda → Direita
void pre_order(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    printf("%d ", raiz->data);
    pre_order(raiz->esquerda);
    pre_order(raiz->direita);
}

// Post-order: Esquerda → Direita → Raiz
void post_order(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    post_order(raiz->esquerda);
    post_order(raiz->direita);
    printf("%d ", raiz->data);
}

// Libera toda árvore (post-order!)
void liberar_arvore(TreeNode **raiz) {
    if(*raiz == NULL) return;
    
    liberar_arvore(&(*raiz)->esquerda);
    liberar_arvore(&(*raiz)->direita);
    free(*raiz);
    *raiz = NULL;
}

// Imprime árvore visualmente (simplificado)
void imprimir_arvore(TreeNode *raiz, int nivel) {
    if(raiz == NULL) return;
    
    imprimir_arvore(raiz->direita, nivel + 1);
    
    for(int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%d\n", raiz->data);
    
    imprimir_arvore(raiz->esquerda, nivel + 1);
}

// ============================================
// MAIN - DEMONSTRAÇÃO
// ============================================

int main() {
    printf("=== AULA 08: ÁRVORE BINÁRIA DE BUSCA ===\n\n");
    
    TreeNode *raiz = NULL;
    
    // ==========================================
    // PARTE 1: INSERÇÃO
    // ==========================================
    printf("--- PARTE 1: Inserção Ordenada ---\n\n");
    
    printf("Inserindo: 50, 30, 70, 20, 40, 60, 80\n\n");
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);
    
    printf("\nTentando inserir duplicata:\n");
    raiz = inserir(raiz, 50);
    printf("\n");
    
    // ==========================================
    // PARTE 2: VISUALIZAÇÃO
    // ==========================================
    printf("--- PARTE 2: Visualização da Árvore ---\n\n");
    
    printf("Árvore (formato visual):\n");
    imprimir_arvore(raiz, 0);
    printf("\n");
    
    printf("Estrutura conceitual:\n");
    printf("        50\n");
    printf("       /  \\\n");
    printf("     30    70\n");
    printf("    / \\   / \\\n");
    printf("   20 40 60 80\n\n");
    
    // ==========================================
    // PARTE 3: PERCURSOS
    // ==========================================
    printf("--- PARTE 3: Percursos (Traversals) ---\n\n");
    
    printf("In-order (crescente):   ");
    in_order(raiz);
    printf("\n");
    
    printf("Pre-order (raiz primeiro): ");
    pre_order(raiz);
    printf("\n");
    
    printf("Post-order (raiz último):  ");
    post_order(raiz);
    printf("\n\n");
    
    // ==========================================
    // PARTE 4: BUSCA
    // ==========================================
    printf("--- PARTE 4: Busca ---\n\n");
    
    buscar(raiz, 40);
    buscar(raiz, 100);
    printf("\n");
    
    TreeNode *min = encontrar_minimo(raiz);
    TreeNode *max = encontrar_maximo(raiz);
    
    printf("Menor valor: %d\n", min ? min->data : -1);
    printf("Maior valor: %d\n\n", max ? max->data : -1);
    
    // ==========================================
    // PARTE 5: INFORMAÇÕES
    // ==========================================
    printf("--- PARTE 5: Informações da Árvore ---\n\n");
    
    printf("Altura: %d\n", altura(raiz));
    printf("Total de nós: %d\n", contar_nos(raiz));
    printf("Nós folha: %d\n\n", contar_folhas(raiz));
    
    // ==========================================
    // PARTE 6: REMOÇÃO
    // ==========================================
    printf("--- PARTE 6: Remoção ---\n\n");
    
    printf("Removendo 20 (folha):\n");
    raiz = remover(raiz, 20);
    printf("In-order: ");
    in_order(raiz);
    printf("\n\n");
    
    printf("Removendo 30 (1 filho):\n");
    raiz = remover(raiz, 30);
    printf("In-order: ");
    in_order(raiz);
    printf("\n\n");
    
    printf("Removendo 50 (2 filhos - raiz):\n");
    raiz = remover(raiz, 50);
    printf("In-order: ");
    in_order(raiz);
    printf("\n\n");
    
    printf("Árvore após remoções:\n");
    imprimir_arvore(raiz, 0);
    printf("\n");
    
    // ==========================================
    // PARTE 7: EXEMPLO PRÁTICO
    // ==========================================
    printf("--- PARTE 7: Exemplo Completo ---\n\n");
    
    TreeNode *numeros = NULL;
    
    printf("Criando árvore com: 15, 10, 20, 8, 12, 17, 25\n\n");
    int valores[] = {15, 10, 20, 8, 12, 17, 25};
    for(int i = 0; i < 7; i++) {
        numeros = inserir(numeros, valores[i]);
    }
    
    printf("\nÁrvore criada:\n");
    imprimir_arvore(numeros, 0);
    
    printf("\nOrdenado (in-order): ");
    in_order(numeros);
    printf("\n\n");
    
    printf("Altura: %d\n", altura(numeros));
    printf("Total de nós: %d\n", contar_nos(numeros));
    
    printf("\nLiberando memória...\n");
    liberar_arvore(&raiz);
    liberar_arvore(&numeros);
    printf("✅ Árvores liberadas\n\n");
    
    printf("=== FIM DA AULA 08 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * ESTRUTURA:
 * ==========
 * - Cada nó tem: valor, filho esquerdo, filho direito
 * - Esquerda < Raiz < Direita (propriedade BST)
 * - Folhas: nós sem filhos
 * 
 * OPERAÇÕES E COMPLEXIDADE:
 * ==========================
 * Árvore Balanceada:
 * - Busca: O(log n) ⚡
 * - Inserção: O(log n) ⚡
 * - Remoção: O(log n) ⚡
 * 
 * Árvore Degenerada (pior caso):
 * - Todas: O(n) 🐌 (vira lista)
 * 
 * PERCURSOS:
 * ==========
 * - In-order: esq → raiz → dir (ORDENADO!)
 * - Pre-order: raiz → esq → dir
 * - Post-order: esq → dir → raiz
 * 
 * VANTAGENS:
 * ==========
 * ✅ Busca rápida (log n)
 * ✅ Inserção/remoção rápida (log n)
 * ✅ Mantém ordenação
 * ✅ In-order retorna elementos ordenados
 * 
 * DESVANTAGENS:
 * =============
 * ❌ Pode degenerar (virar lista)
 * ❌ Mais complexa que lista
 * ❌ Usa mais memória (2 ponteiros por nó)
 * ❌ Precisa balanceamento (AVL, Red-Black)
 * 
 * QUANDO USAR:
 * ============
 * ✅ Busca frequente
 * ✅ Dados ordenados
 * ✅ Inserção/busca/remoção balanceadas
 * ❌ Não use se acesso é sempre sequencial
 * 
 * PRÓXIMOS ESTUDOS:
 * =================
 * - Árvore AVL (autobalanceada)
 * - Red-Black Tree
 * - Heap
 * - B-Tree
 */
