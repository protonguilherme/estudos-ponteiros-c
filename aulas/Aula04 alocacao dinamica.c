/*
 * AULA 04 - Alocação Dinâmica de Memória
 * 
 * Objetivos:
 * - Entender diferença entre stack e heap
 * - Usar malloc, calloc, realloc, free
 * - Alocar arrays dinamicamente
 * - Evitar memory leaks
 * - Trabalhar com memória dinâmica de forma segura
 */

#include <stdio.h>
#include <stdlib.h>  // necessário para malloc, calloc, realloc, free
#include <string.h>

// ============================================
// FUNÇÕES AUXILIARES
// ============================================

// Cria array dinâmico preenchido
int* criar_array(int tamanho, int valor_inicial) {
    int *arr = (int*) malloc(tamanho * sizeof(int));
    
    if(arr == NULL) {
        printf("Erro: falha ao alocar memória!\n");
        return NULL;
    }
    
    for(int i = 0; i < tamanho; i++) {
        arr[i] = valor_inicial;
    }
    
    return arr;
}

// Imprime array
void imprimir_array(int *arr, int tamanho) {
    printf("[ ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Cria cópia de array
int* copiar_array(int *original, int tamanho) {
    int *copia = (int*) malloc(tamanho * sizeof(int));
    
    if(copia == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < tamanho; i++) {
        copia[i] = original[i];
    }
    
    return copia;
}

// Redimensiona array
int* redimensionar_array(int *arr_antigo, int tamanho_antigo, int tamanho_novo) {
    int *arr_novo = (int*) realloc(arr_antigo, tamanho_novo * sizeof(int));
    
    if(arr_novo == NULL) {
        printf("Erro ao redimensionar!\n");
        return arr_antigo;  // mantém o antigo
    }
    
    // Inicializa novos elementos (se aumentou)
    for(int i = tamanho_antigo; i < tamanho_novo; i++) {
        arr_novo[i] = 0;
    }
    
    return arr_novo;
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("=== AULA 04: ALOCAÇÃO DINÂMICA ===\n\n");
    
    // ============================================
    // PARTE 1: STACK vs HEAP
    // ============================================
    printf("--- PARTE 1: Stack vs Heap ---\n");
    
    // Stack: tamanho fixo, gerenciada automaticamente
    int arr_stack[5] = {1, 2, 3, 4, 5};
    printf("Array na stack: ");
    for(int i = 0; i < 5; i++) printf("%d ", arr_stack[i]);
    printf("\n");
    
    // Heap: tamanho dinâmico, gerenciada manualmente
    int *arr_heap = (int*) malloc(5 * sizeof(int));
    if(arr_heap != NULL) {
        for(int i = 0; i < 5; i++) {
            arr_heap[i] = i + 1;
        }
        printf("Array no heap: ");
        for(int i = 0; i < 5; i++) printf("%d ", arr_heap[i]);
        printf("\n");
        free(arr_heap);  // SEMPRE libere!
    }
    printf("\n");
    
    // ============================================
    // PARTE 2: MALLOC - Alocação Básica
    // ============================================
    printf("--- PARTE 2: malloc() ---\n");
    
    int tamanho = 10;
    int *numeros = (int*) malloc(tamanho * sizeof(int));
    
    // SEMPRE verifique se malloc funcionou!
    if(numeros == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("Memória alocada com sucesso!\n");
    printf("Endereço: %p\n", (void*)numeros);
    printf("Tamanho: %d bytes (%d ints)\n", 
           tamanho * (int)sizeof(int), tamanho);
    
    // Preenche com valores
    for(int i = 0; i < tamanho; i++) {
        numeros[i] = i * 10;
    }
    
    printf("Array: ");
    imprimir_array(numeros, tamanho);
    
    // SEMPRE libere quando terminar!
    free(numeros);
    numeros = NULL;  // boa prática
    printf("\n");
    
    // ============================================
    // PARTE 3: CALLOC - Alocação Inicializada
    // ============================================
    printf("--- PARTE 3: calloc() ---\n");
    
    // calloc inicializa tudo com 0
    int *zeros = (int*) calloc(5, sizeof(int));
    
    if(zeros != NULL) {
        printf("Array com calloc (inicializado com 0): ");
        imprimir_array(zeros, 5);
        
        free(zeros);
    }
    printf("\n");
    
    // ============================================
    // PARTE 4: REALLOC - Redimensionamento
    // ============================================
    printf("--- PARTE 4: realloc() ---\n");
    
    int *dinamico = (int*) malloc(3 * sizeof(int));
    
    if(dinamico != NULL) {
        dinamico[0] = 10;
        dinamico[1] = 20;
        dinamico[2] = 30;
        
        printf("Array inicial (3 elementos): ");
        imprimir_array(dinamico, 3);
        
        // Aumenta para 6 elementos
        dinamico = (int*) realloc(dinamico, 6 * sizeof(int));
        
        if(dinamico != NULL) {
            dinamico[3] = 40;
            dinamico[4] = 50;
            dinamico[5] = 60;
            
            printf("Array redimensionado (6 elementos): ");
            imprimir_array(dinamico, 6);
            
            free(dinamico);
        }
    }
    printf("\n");
    
    // ============================================
    // PARTE 5: STRINGS DINÂMICAS
    // ============================================
    printf("--- PARTE 5: Strings Dinâmicas ---\n");
    
    char *nome = (char*) malloc(50 * sizeof(char));
    
    if(nome != NULL) {
        strcpy(nome, "João Silva");
        printf("Nome: %s\n", nome);
        printf("Tamanho alocado: 50 bytes\n");
        printf("Tamanho usado: %zu bytes\n", strlen(nome) + 1);
        
        free(nome);
    }
    printf("\n");
    
    // ============================================
    // PARTE 6: ARRAY DE PONTEIROS (MATRIZ DINÂMICA)
    // ============================================
    printf("--- PARTE 6: Matriz Dinâmica ---\n");
    
    int linhas = 3, colunas = 4;
    
    // Aloca array de ponteiros
    int **matriz = (int**) malloc(linhas * sizeof(int*));
    
    if(matriz != NULL) {
        // Aloca cada linha
        for(int i = 0; i < linhas; i++) {
            matriz[i] = (int*) malloc(colunas * sizeof(int));
            if(matriz[i] == NULL) {
                printf("Erro ao alocar linha %d\n", i);
                // Libera o que já foi alocado
                for(int j = 0; j < i; j++) {
                    free(matriz[j]);
                }
                free(matriz);
                return 1;
            }
        }
        
        // Preenche matriz
        int valor = 1;
        for(int i = 0; i < linhas; i++) {
            for(int j = 0; j < colunas; j++) {
                matriz[i][j] = valor++;
            }
        }
        
        // Imprime matriz
        printf("Matriz %dx%d:\n", linhas, colunas);
        for(int i = 0; i < linhas; i++) {
            for(int j = 0; j < colunas; j++) {
                printf("%3d ", matriz[i][j]);
            }
            printf("\n");
        }
        
        // Libera memória (ordem reversa!)
        for(int i = 0; i < linhas; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }
    printf("\n");
    
    // ============================================
    // PARTE 7: EXEMPLO PRÁTICO
    // ============================================
    printf("--- PARTE 7: Exemplo Prático ---\n");
    
    int *meu_array = criar_array(5, 100);
    
    if(meu_array != NULL) {
        printf("Array criado: ");
        imprimir_array(meu_array, 5);
        
        int *copia = copiar_array(meu_array, 5);
        if(copia != NULL) {
            printf("Cópia: ");
            imprimir_array(copia, 5);
            
            copia[2] = 999;
            printf("Cópia modificada: ");
            imprimir_array(copia, 5);
            printf("Original (inalterado): ");
            imprimir_array(meu_array, 5);
            
            free(copia);
        }
        
        free(meu_array);
    }
    printf("\n");
    
    // ============================================
    // PARTE 8: ERROS COMUNS
    // ============================================
    printf("--- PARTE 8: Erros Comuns ---\n");
    
    printf("❌ Memory Leak: alocar sem liberar\n");
    printf("❌ Dangling Pointer: usar após free\n");
    printf("❌ Double Free: liberar duas vezes\n");
    printf("❌ Buffer Overflow: escrever além do alocado\n");
    printf("❌ Não verificar se malloc retornou NULL\n");
    printf("\n");
    
    printf("✅ BOM: sempre verificar malloc\n");
    printf("✅ BOM: sempre dar free\n");
    printf("✅ BOM: p = NULL após free\n");
    printf("✅ BOM: liberar na ordem reversa\n");
    printf("\n");
    
    // ============================================
    // PARTE 9: EXEMPLO DE USO CORRETO
    // ============================================
    printf("--- PARTE 9: Uso Correto ---\n");
    
    int *correto = (int*) malloc(5 * sizeof(int));
    
    if(correto == NULL) {
        printf("Erro ao alocar!\n");
        return 1;
    }
    
    // Usa o ponteiro
    for(int i = 0; i < 5; i++) {
        correto[i] = i;
    }
    
    printf("Array: ");
    imprimir_array(correto, 5);
    
    // Libera e anula
    free(correto);
    correto = NULL;
    
    // Verifica antes de usar
    if(correto != NULL) {
        printf("Ponteiro válido\n");
    } else {
        printf("Ponteiro já foi liberado ✅\n");
    }
    printf("\n");
    
    // ============================================
    // EXERCÍCIOS PARA PRATICAR
    // ============================================
    printf("--- EXERCÍCIOS ---\n");
    printf("1. Crie função que aloca e preenche array com números ímpares\n");
    printf("2. Crie função que concatena duas strings dinâmicas\n");
    printf("3. Crie função que remove duplicatas de array dinâmico\n");
    printf("4. Crie calculadora que aloca memória para histórico de operações\n\n");
    
    printf("=== FIM DA AULA 04 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * 1. malloc(size) - aloca size bytes (não inicializa)
 * 2. calloc(n, size) - aloca n*size bytes (inicializa com 0)
 * 3. realloc(ptr, new_size) - redimensiona bloco
 * 4. free(ptr) - libera memória alocada
 * 
 * REGRAS DE OURO:
 * - SEMPRE verificar se malloc retornou NULL
 * - SEMPRE dar free() no que você alocou
 * - NUNCA usar ponteiro após free()
 * - NUNCA dar free() duas vezes no mesmo ponteiro
 * - Fazer ptr = NULL após free() é boa prática
 * 
 * PRÓXIMA AULA: Structs e Ponteiros
 */