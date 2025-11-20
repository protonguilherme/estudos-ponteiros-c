/*
 * AULA 02 - Ponteiros e Funções
 * 
 * Objetivos:
 * - Entender passagem por valor vs passagem por referência
 * - Usar ponteiros como parâmetros de funções
 * - Modificar variáveis através de ponteiros em funções
 * - Retornar múltiplos valores de uma função
 */

#include <stdio.h>

// ============================================
// FUNÇÕES AUXILIARES
// ============================================

// Passagem por VALOR (não modifica original)
void incrementa_valor(int n) {
    n++;  // modifica apenas a cópia local
    printf("Dentro da função (valor): n = %d\n", n);
}

// Passagem por REFERÊNCIA (modifica original)
void incrementa_referencia(int *n) {
    (*n)++;  // modifica o valor original
    printf("Dentro da função (referência): *n = %d\n", *n);
}

// Troca dois valores usando ponteiros
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Retorna múltiplos valores através de ponteiros
void dividir(int dividendo, int divisor, int *quociente, int *resto) {
    if(divisor != 0) {
        *quociente = dividendo / divisor;
        *resto = dividendo % divisor;
    }
}

// Encontra maior e menor em um array
void encontrar_max_min(int *arr, int tamanho, int *max, int *min) {
    if(tamanho == 0) return;
    
    *max = arr[0];
    *min = arr[0];
    
    for(int i = 1; i < tamanho; i++) {
        if(arr[i] > *max) *max = arr[i];
        if(arr[i] < *min) *min = arr[i];
    }
}

// Dobra todos os elementos de um array
void dobrar_array(int *arr, int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        arr[i] *= 2;
    }
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("=== AULA 02: PONTEIROS E FUNÇÕES ===\n\n");
    
    // ============================================
    // PARTE 1: PASSAGEM POR VALOR vs REFERÊNCIA
    // ============================================
    printf("--- PARTE 1: Passagem por Valor vs Referência ---\n");
    
    int numero = 10;
    
    printf("ANTES: numero = %d\n\n", numero);
    
    printf("Chamando incrementa_valor(numero):\n");
    incrementa_valor(numero);
    printf("DEPOIS: numero = %d (não mudou!)\n\n", numero);
    
    printf("Chamando incrementa_referencia(&numero):\n");
    incrementa_referencia(&numero);
    printf("DEPOIS: numero = %d (mudou!)\n\n", numero);
    
    // ============================================
    // PARTE 2: TROCAR VALORES
    // ============================================
    printf("--- PARTE 2: Trocar Valores ---\n");
    
    int x = 5, y = 10;
    
    printf("ANTES: x = %d, y = %d\n", x, y);
    trocar(&x, &y);
    printf("DEPOIS: x = %d, y = %d\n\n", x, y);
    
    // ============================================
    // PARTE 3: RETORNAR MÚLTIPLOS VALORES
    // ============================================
    printf("--- PARTE 3: Retornar Múltiplos Valores ---\n");
    
    int quociente, resto;
    
    dividir(17, 5, &quociente, &resto);
    
    printf("17 / 5 = %d (resto %d)\n\n", quociente, resto);
    
    // ============================================
    // PARTE 4: PONTEIROS E ARRAYS
    // ============================================
    printf("--- PARTE 4: Modificando Arrays ---\n");
    
    int numeros[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    
    printf("Array ANTES: ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");
    
    dobrar_array(numeros, tamanho);
    
    printf("Array DEPOIS: ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n\n");
    
    // ============================================
    // PARTE 5: ENCONTRAR MÁXIMO E MÍNIMO
    // ============================================
    printf("--- PARTE 5: Retornando Máximo e Mínimo ---\n");
    
    int valores[] = {45, 12, 89, 3, 67, 23, 56};
    int n = 7;
    int maximo, minimo;
    
    encontrar_max_min(valores, n, &maximo, &minimo);
    
    printf("Array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");
    printf("Máximo: %d\n", maximo);
    printf("Mínimo: %d\n\n", minimo);
    
    // ============================================
    // PARTE 6: EXEMPLO COMPLETO - CALCULADORA
    // ============================================
    printf("--- PARTE 6: Exemplo Completo ---\n");
    
    int a = 20, b = 5;
    int soma, sub, mult, div_result;
    
    // Simula uma calculadora que retorna 4 resultados
    soma = a + b;
    sub = a - b;
    mult = a * b;
    dividir(a, b, &div_result, &resto);
    
    printf("Calculadora com %d e %d:\n", a, b);
    printf("Soma: %d\n", soma);
    printf("Subtração: %d\n", sub);
    printf("Multiplicação: %d\n", mult);
    printf("Divisão: %d (resto %d)\n\n", div_result, resto);
    
    // ============================================
    // EXERCÍCIOS PARA PRATICAR
    // ============================================
    printf("--- EXERCÍCIOS ---\n");
    printf("1. Crie uma função que recebe 3 números e retorna a média e a soma\n");
    printf("2. Crie uma função que inverte dois caracteres\n");
    printf("3. Crie uma função que calcula área e perímetro de um retângulo\n\n");
    
    printf("=== FIM DA AULA 02 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * 1. Passagem por VALOR: função recebe cópia (não modifica original)
 * 2. Passagem por REFERÊNCIA: função recebe ponteiro (modifica original)
 * 3. Use ponteiros para retornar múltiplos valores
 * 4. Arrays são automaticamente passados por referência
 * 5. Sintaxe: void funcao(int *p) { *p = valor; }
 * 6. Chamada: funcao(&variavel);
 * 
 * PRÓXIMA AULA: Aritmética de Ponteiros
 */