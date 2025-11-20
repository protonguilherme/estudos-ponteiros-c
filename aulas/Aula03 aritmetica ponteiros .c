/*
 * AULA 03 - Aritmética de Ponteiros
 * 
 * Objetivos:
 * - Entender como funciona aritmética de ponteiros
 * - Percorrer arrays usando ponteiros
 * - Entender a relação entre ponteiros e arrays
 * - Fazer operações com ponteiros
 */

#include <stdio.h>

// ============================================
// FUNÇÕES AUXILIARES
// ============================================

// Soma array usando notação de array
int soma_array_v1(int arr[], int tamanho) {
    int soma = 0;
    for(int i = 0; i < tamanho; i++) {
        soma += arr[i];  // notação de array
    }
    return soma;
}

// Soma array usando aritmética de ponteiros
int soma_array_v2(int *arr, int tamanho) {
    int soma = 0;
    for(int i = 0; i < tamanho; i++) {
        soma += *(arr + i);  // aritmética de ponteiros
    }
    return soma;
}

// Soma array usando incremento de ponteiro
int soma_array_v3(int *arr, int tamanho) {
    int soma = 0;
    int *ptr = arr;  // ponteiro para o início
    
    for(int i = 0; i < tamanho; i++) {
        soma += *ptr;  // valor atual
        ptr++;         // avança para próximo elemento
    }
    return soma;
}

// Imprime array com ponteiro
void imprimir_array(int *arr, int tamanho) {
    int *ptr = arr;
    printf("[ ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("]\n");
}

// Inverte array usando dois ponteiros
void inverter_array(int *arr, int tamanho) {
    int *inicio = arr;
    int *fim = arr + tamanho - 1;
    
    while(inicio < fim) {
        // Troca valores
        int temp = *inicio;
        *inicio = *fim;
        *fim = temp;
        
        // Move ponteiros
        inicio++;
        fim--;
    }
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("=== AULA 03: ARITMÉTICA DE PONTEIROS ===\n\n");
    
    // ============================================
    // PARTE 1: PONTEIROS E ARRAYS
    // ============================================
    printf("--- PARTE 1: Relação entre Ponteiros e Arrays ---\n");
    
    int numeros[5] = {10, 20, 30, 40, 50};
    int *ptr = numeros;  // nome do array é um ponteiro!
    
    printf("numeros[0] = %d\n", numeros[0]);
    printf("*ptr = %d (mesma coisa!)\n", *ptr);
    printf("numeros[2] = %d\n", numeros[2]);
    printf("*(ptr + 2) = %d (mesma coisa!)\n\n", *(ptr + 2));
    
    // ============================================
    // PARTE 2: ARITMÉTICA DE PONTEIROS
    // ============================================
    printf("--- PARTE 2: Aritmética de Ponteiros ---\n");
    
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = arr;
    
    printf("Endereço de p: %p\n", (void*)p);
    printf("Valor de *p: %d\n", *p);
    printf("\n");
    
    p++;  // avança sizeof(int) bytes
    printf("Após p++:\n");
    printf("Endereço de p: %p\n", (void*)p);
    printf("Valor de *p: %d\n", *p);
    printf("\n");
    
    p += 2;  // avança 2 * sizeof(int) bytes
    printf("Após p += 2:\n");
    printf("Endereço de p: %p\n", (void*)p);
    printf("Valor de *p: %d\n\n", *p);
    
    // ============================================
    // PARTE 3: PERCORRENDO ARRAYS
    // ============================================
    printf("--- PARTE 3: Três Formas de Percorrer Arrays ---\n");
    
    int valores[] = {5, 10, 15, 20, 25};
    int tamanho = 5;
    
    printf("Forma 1 (índice): ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");
    
    printf("Forma 2 (aritmética): ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", *(valores + i));
    }
    printf("\n");
    
    printf("Forma 3 (incremento): ");
    int *ponteiro = valores;
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", *ponteiro);
        ponteiro++;
    }
    printf("\n\n");
    
    // ============================================
    // PARTE 4: DIFERENÇA ENTRE PONTEIROS
    // ============================================
    printf("--- PARTE 4: Diferença entre Ponteiros ---\n");
    
    int lista[] = {100, 200, 300, 400, 500};
    int *inicio = lista;
    int *fim = &lista[4];
    
    printf("Endereço inicio: %p\n", (void*)inicio);
    printf("Endereço fim: %p\n", (void*)fim);
    printf("Diferença: %ld elementos\n", fim - inicio);
    printf("Diferença em bytes: %ld bytes\n\n", 
           (char*)fim - (char*)inicio);
    
    // ============================================
    // PARTE 5: COMPARAÇÃO DE PONTEIROS
    // ============================================
    printf("--- PARTE 5: Comparação de Ponteiros ---\n");
    
    int dados[] = {1, 2, 3, 4, 5};
    int *p1 = dados;
    int *p2 = dados + 3;
    
    printf("p1 aponta para: %d\n", *p1);
    printf("p2 aponta para: %d\n", *p2);
    
    if(p1 < p2) {
        printf("p1 vem antes de p2 na memória\n");
    }
    
    if(p2 > p1) {
        printf("p2 vem depois de p1 na memória\n");
    }
    printf("\n");
    
    // ============================================
    // PARTE 6: EXEMPLO PRÁTICO - SOMA
    // ============================================
    printf("--- PARTE 6: Exemplo Prático ---\n");
    
    int nums[] = {10, 20, 30, 40, 50};
    int tam = 5;
    
    int s1 = soma_array_v1(nums, tam);
    int s2 = soma_array_v2(nums, tam);
    int s3 = soma_array_v3(nums, tam);
    
    printf("Array: ");
    imprimir_array(nums, tam);
    printf("Soma (v1): %d\n", s1);
    printf("Soma (v2): %d\n", s2);
    printf("Soma (v3): %d\n\n", s3);
    
    // ============================================
    // PARTE 7: INVERTER ARRAY
    // ============================================
    printf("--- PARTE 7: Inverter Array ---\n");
    
    int original[] = {1, 2, 3, 4, 5, 6};
    int n = 6;
    
    printf("ANTES: ");
    imprimir_array(original, n);
    
    inverter_array(original, n);
    
    printf("DEPOIS: ");
    imprimir_array(original, n);
    printf("\n");
    
    // ============================================
    // PARTE 8: ACESSANDO ELEMENTOS
    // ============================================
    printf("--- PARTE 8: Formas Equivalentes de Acessar ---\n");
    
    int test[] = {10, 20, 30, 40};
    int *pt = test;
    
    printf("arr[2] = %d\n", test[2]);
    printf("*(arr + 2) = %d\n", *(test + 2));
    printf("pt[2] = %d\n", pt[2]);
    printf("*(pt + 2) = %d\n", *(pt + 2));
    printf("2[arr] = %d (funciona mas não use!)\n\n", 2[test]);
    
    // ============================================
    // PARTE 9: CUIDADOS COM PONTEIROS
    // ============================================
    printf("--- PARTE 9: Cuidados Importantes ---\n");
    
    int seguro[] = {1, 2, 3};
    int *ps = seguro;
    
    printf("✅ Seguro: *ps = %d\n", *ps);
    printf("✅ Seguro: *(ps + 2) = %d\n", *(ps + 2));
    // printf("❌ PERIGO: *(ps + 100) = %d\n", *(ps + 100)); // NÃO FAÇA!
    printf("⚠️  Acessar fora dos limites causa crash!\n\n");
    
    // ============================================
    // EXERCÍCIOS PARA PRATICAR
    // ============================================
    printf("--- EXERCÍCIOS ---\n");
    printf("1. Crie função que encontra o maior elemento usando ponteiros\n");
    printf("2. Crie função que copia um array usando ponteiros\n");
    printf("3. Crie função que conta elementos pares usando ponteiros\n\n");
    
    printf("=== FIM DA AULA 03 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * 1. arr[i] é equivalente a *(arr + i)
 * 2. ptr++ avança sizeof(tipo) bytes automaticamente
 * 3. ptr + n avança n * sizeof(tipo) bytes
 * 4. ptr1 - ptr2 retorna número de elementos entre eles
 * 5. Podemos comparar ponteiros (<, >, ==, !=)
 * 6. Nome do array é um ponteiro constante para o primeiro elemento
 * 7. CUIDADO: não acesse fora dos limites do array!
 * 
 * PRÓXIMA AULA: Alocação Dinâmica (malloc, free)
 */