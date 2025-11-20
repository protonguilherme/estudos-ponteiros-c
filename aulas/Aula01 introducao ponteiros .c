/*
 * AULA 01 - Introdução a Ponteiros
 * 
 * Objetivos:
 * - Entender o que são ponteiros
 * - Declarar e inicializar ponteiros
 * - Usar operadores & e *
 * - Ver endereços de memória
 */

#include <stdio.h>

int main() {
    printf("=== AULA 01: INTRODUÇÃO A PONTEIROS ===\n\n");
    
    // ============================================
    // PARTE 1: O QUE SÃO PONTEIROS?
    // ============================================
    printf("--- PARTE 1: Variáveis Normais vs Ponteiros ---\n");
    
    int numero = 42;  // variável normal (guarda um valor)
    
    printf("Valor de numero: %d\n", numero);
    printf("Endereço de numero: %p\n", (void*)&numero);
    printf("Tamanho de numero: %zu bytes\n\n", sizeof(numero));
    
    // ============================================
    // PARTE 2: DECLARANDO PONTEIROS
    // ============================================
    printf("--- PARTE 2: Declarando Ponteiros ---\n");
    
    int *ptr;  // declara um ponteiro para int
    ptr = &numero;  // ptr agora guarda o endereço de numero
    
    printf("Valor de ptr (endereço): %p\n", (void*)ptr);
    printf("Valor apontado por ptr: %d\n", *ptr);
    printf("Tamanho de ptr: %zu bytes\n\n", sizeof(ptr));
    
    // ============================================
    // PARTE 3: OPERADORES & e *
    // ============================================
    printf("--- PARTE 3: Operadores & (address-of) e * (dereference) ---\n");
    
    int x = 10;
    int *p = &x;  // & pega o endereço
    
    printf("x = %d\n", x);
    printf("&x = %p (endereço de x)\n", (void*)&x);
    printf("p = %p (ponteiro guarda endereço)\n", (void*)p);
    printf("*p = %d (dereferencia - acessa o valor)\n\n", *p);
    
    // ============================================
    // PARTE 4: MODIFICANDO ATRAVÉS DE PONTEIROS
    // ============================================
    printf("--- PARTE 4: Modificando Valores ---\n");
    
    int valor = 100;
    int *ponteiro = &valor;
    
    printf("ANTES: valor = %d\n", valor);
    
    *ponteiro = 200;  // modifica valor através do ponteiro
    
    printf("DEPOIS: valor = %d\n", valor);
    printf("Modificamos 'valor' usando o ponteiro!\n\n");
    
    // ============================================
    // PARTE 5: MÚLTIPLOS PONTEIROS PARA MESMA VARIÁVEL
    // ============================================
    printf("--- PARTE 5: Múltiplos Ponteiros ---\n");
    
    int num = 50;
    int *p1 = &num;
    int *p2 = &num;
    
    printf("num = %d\n", num);
    printf("*p1 = %d\n", *p1);
    printf("*p2 = %d\n", *p2);
    
    *p1 = 75;  // modifica através de p1
    printf("\nApós *p1 = 75:\n");
    printf("num = %d\n", num);
    printf("*p2 = %d (p2 também vê a mudança!)\n\n", *p2);
    
    // ============================================
    // PARTE 6: PONTEIRO NULO
    // ============================================
    printf("--- PARTE 6: Ponteiro Nulo (NULL) ---\n");
    
    int *ptr_nulo = NULL;  // ponteiro que não aponta para nada
    
    printf("ptr_nulo = %p\n", (void*)ptr_nulo);
    
    // NUNCA faça isso: *ptr_nulo = 10; (vai crashar!)
    
    // Sempre verifique antes de usar:
    if(ptr_nulo != NULL) {
        printf("Ponteiro válido: %d\n", *ptr_nulo);
    } else {
        printf("Ponteiro é NULL - não pode usar!\n\n");
    }
    
    // ============================================
    // PARTE 7: DIFERENTES TIPOS DE PONTEIROS
    // ============================================
    printf("--- PARTE 7: Tipos de Ponteiros ---\n");
    
    int a = 10;
    float b = 3.14;
    char c = 'A';
    
    int *ptr_int = &a;
    float *ptr_float = &b;
    char *ptr_char = &c;
    
    printf("int: %d (tamanho do ponteiro: %zu)\n", *ptr_int, sizeof(ptr_int));
    printf("float: %.2f (tamanho do ponteiro: %zu)\n", *ptr_float, sizeof(ptr_float));
    printf("char: %c (tamanho do ponteiro: %zu)\n\n", *ptr_char, sizeof(ptr_char));
    
    // Nota: Todos os ponteiros têm o mesmo tamanho (geralmente 8 bytes em 64-bit)
    
    // ============================================
    // EXERCÍCIOS PARA PRATICAR
    // ============================================
    printf("--- EXERCÍCIOS PARA VOCÊ ---\n");
    printf("1. Crie uma variável e um ponteiro para ela\n");
    printf("2. Imprima o valor e o endereço\n");
    printf("3. Modifique o valor através do ponteiro\n");
    printf("4. Imprima novamente\n\n");
    
    // Seu código aqui:
    // int minha_var = ...
    // int *meu_ptr = ...
    
    printf("=== FIM DA AULA 01 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * 1. Ponteiro = variável que guarda ENDEREÇO de outra variável
 * 2. & (address-of) = pega o endereço
 * 3. * (dereference) = acessa o valor no endereço
 * 4. int *p; = declara ponteiro para int
 * 5. p = &x; = p aponta para x
 * 6. *p = valor apontado
 * 7. Sempre inicialize ponteiros (NULL ou &variavel)
 * 
 * PRÓXIMA AULA: Ponteiros e Funções
 */