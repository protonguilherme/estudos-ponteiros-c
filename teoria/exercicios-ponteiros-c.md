# Exercícios Práticos - Ponteiros em C

## Índice por Nível
- [[#Nível 1 - Básico]]
- [[#Nível 2 - Intermediário]]
- [[#Nível 3 - Avançado]]
- [[#Projetos Completos]]
- [[#Soluções]]

---

## Nível 1 - Básico

### Exercício 1.1: Primeiros Passos com Ponteiros
**Objetivo:** Entender declaração, inicialização e dereferência.

```c
// Complete o código abaixo:
#include <stdio.h>

int main() {
    int x = 42;
    int *p;  // TODO: faça p apontar para x
    
    // TODO: imprima o valor de x usando o ponteiro p
    // TODO: modifique x para 100 usando o ponteiro p
    // TODO: imprima x novamente
    
    return 0;
}
```

**Saída esperada:**
```
Valor através do ponteiro: 42
Novo valor: 100
```

---

### Exercício 1.2: Troca de Valores
**Objetivo:** Criar função que troca valores de duas variáveis usando ponteiros.

```c
#include <stdio.h>

// TODO: Implemente esta função
void trocar(int *a, int *b) {
    // Seu código aqui
}

int main() {
    int x = 10, y = 20;
    
    printf("Antes: x=%d, y=%d\n", x, y);
    trocar(&x, &y);
    printf("Depois: x=%d, y=%d\n", x, y);
    
    return 0;
}
```

**Saída esperada:**
```
Antes: x=10, y=20
Depois: x=20, y=10
```

---

### Exercício 1.3: Soma de Array
**Objetivo:** Usar ponteiros para percorrer e somar elementos de um array.

```c
#include <stdio.h>

// TODO: Implemente usando ponteiros (não use notação de array arr[i])
int soma_array(int *arr, int tamanho) {
    // Seu código aqui
}

int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int tamanho = 5;
    
    int resultado = soma_array(numeros, tamanho);
    printf("Soma: %d\n", resultado);  // Deve imprimir 150
    
    return 0;
}
```

---

### Exercício 1.4: Maior e Menor Valor
**Objetivo:** Retornar maior e menor valor de um array através de ponteiros.

```c
#include <stdio.h>

// TODO: Implemente esta função
// max e min devem receber os valores através dos ponteiros
void encontrar_max_min(int *arr, int tamanho, int *max, int *min) {
    // Seu código aqui
}

int main() {
    int numeros[] = {45, 12, 89, 3, 67, 23};
    int tamanho = 6;
    int maior, menor;
    
    encontrar_max_min(numeros, tamanho, &maior, &menor);
    
    printf("Maior: %d\n", maior);  // 89
    printf("Menor: %d\n", menor);  // 3
    
    return 0;
}
```

---

### Exercício 1.5: Inverter String
**Objetivo:** Inverter uma string usando ponteiros.

```c
#include <stdio.h>
#include <string.h>

// TODO: Implemente esta função usando ponteiros
void inverter_string(char *str) {
    // Dica: use dois ponteiros, um no início e outro no fim
    // Seu código aqui
}

int main() {
    char texto[] = "Ponteiros";
    
    printf("Antes: %s\n", texto);
    inverter_string(texto);
    printf("Depois: %s\n", texto);  // "sorietnoPa"
    
    return 0;
}
```

---

## Nível 2 - Intermediário

### Exercício 2.1: Alocação Dinâmica de Array
**Objetivo:** Criar array dinâmico e preenchê-lo.

```c
#include <stdio.h>
#include <stdlib.h>

// TODO: Implemente esta função
// Deve alocar array de 'tamanho' elementos e preencher com valores de 1 a tamanho
int* criar_array_sequencial(int tamanho) {
    // Seu código aqui
}

int main() {
    int tamanho = 10;
    int *arr = criar_array_sequencial(tamanho);
    
    if(arr == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    
    // Imprime: 1 2 3 4 5 6 7 8 9 10
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}
```

---

### Exercício 2.2: Matriz Dinâmica
**Objetivo:** Alocar e manipular matriz 2D dinâmica.

```c
#include <stdio.h>
#include <stdlib.h>

// TODO: Implemente estas funções

// Aloca matriz linhas x colunas
int** criar_matriz(int linhas, int colunas) {
    // Seu código aqui
}

// Preenche matriz com valor
void preencher_matriz(int **matriz, int linhas, int colunas, int valor) {
    // Seu código aqui
}

// Imprime matriz
void imprimir_matriz(int **matriz, int linhas, int colunas) {
    // Seu código aqui
}

// Libera memória da matriz
void liberar_matriz(int **matriz, int linhas) {
    // Seu código aqui
}

int main() {
    int linhas = 3, colunas = 4;
    
    int **matriz = criar_matriz(linhas, colunas);
    if(matriz == NULL) return 1;
    
    preencher_matriz(matriz, linhas, colunas, 7);
    imprimir_matriz(matriz, linhas, colunas);
    liberar_matriz(matriz, linhas);
    
    return 0;
}
```

---

### Exercício 2.3: Remover Duplicatas
**Objetivo:** Remover elementos duplicados de um array.

```c
#include <stdio.h>
#include <stdlib.h>

// TODO: Implemente esta função
// Deve retornar novo array sem duplicatas
// novo_tamanho deve receber o tamanho do novo array
int* remover_duplicatas(int *arr, int tamanho, int *novo_tamanho) {
    // Seu código aqui
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 1};
    int tamanho = 9;
    int novo_tamanho;
    
    int *arr_unico = remover_duplicatas(arr, tamanho, &novo_tamanho);
    
    printf("Array original: ");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Array sem duplicatas: ");
    for(int i = 0; i < novo_tamanho; i++) {
        printf("%d ", arr_unico[i]);
    }
    printf("\n");
    
    free(arr_unico);
    return 0;
}
```

---

### Exercício 2.4: Struct com Ponteiros
**Objetivo:** Criar e manipular struct com dados dinâmicos.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    int idade;
    float *notas;
    int num_notas;
} Aluno;

// TODO: Implemente estas funções

// Cria novo aluno alocando memória dinamicamente
Aluno* criar_aluno(const char *nome, int idade, int num_notas) {
    // Seu código aqui
}

// Adiciona nota ao aluno
void adicionar_nota(Aluno *aluno, int indice, float nota) {
    // Seu código aqui
}

// Calcula média das notas
float calcular_media(Aluno *aluno) {
    // Seu código aqui
}

// Libera toda memória do aluno
void destruir_aluno(Aluno **aluno) {
    // Seu código aqui
}

int main() {
    Aluno *aluno = criar_aluno("João Silva", 20, 4);
    
    adicionar_nota(aluno, 0, 8.5);
    adicionar_nota(aluno, 1, 9.0);
    adicionar_nota(aluno, 2, 7.5);
    adicionar_nota(aluno, 3, 8.0);
    
    printf("Aluno: %s\n", aluno->nome);
    printf("Média: %.2f\n", calcular_media(aluno));
    
    destruir_aluno(&aluno);
    
    return 0;
}
```

---

### Exercício 2.5: Função Callback
**Objetivo:** Usar ponteiros para funções como callbacks.

```c
#include <stdio.h>

// TODO: Implemente esta função
// Deve aplicar a função 'operacao' a cada elemento do array
void aplicar_operacao(int *arr, int tamanho, int (*operacao)(int)) {
    // Seu código aqui
}

// Funções auxiliares
int dobrar(int x) {
    return x * 2;
}

int quadrado(int x) {
    return x * x;
}

int incrementar(int x) {
    return x + 1;
}

int main() {
    int numeros[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    
    printf("Original: ");
    for(int i = 0; i < tamanho; i++) printf("%d ", numeros[i]);
    printf("\n");
    
    aplicar_operacao(numeros, tamanho, dobrar);
    printf("Dobrado: ");
    for(int i = 0; i < tamanho; i++) printf("%d ", numeros[i]);
    printf("\n");
    
    // Teste com outras funções também
    
    return 0;
}
```

---

## Nível 3 - Avançado

### Exercício 3.1: Lista Encadeada Completa
**Objetivo:** Implementar lista encadeada com todas as operações.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// TODO: Implemente TODAS estas funções

Node* criar_node(int valor);
void inserir_inicio(Node **head, int valor);
void inserir_fim(Node **head, int valor);
void inserir_ordenado(Node **head, int valor);  // mantém lista ordenada
int remover_valor(Node **head, int valor);
int remover_indice(Node **head, int indice);
Node* buscar(Node *head, int valor);
int contar(Node *head);
void inverter(Node **head);
void remover_duplicatas(Node **head);
void imprimir(Node *head);
void liberar(Node **head);

int main() {
    Node *lista = NULL;
    
    // Teste suas funções aqui
    inserir_inicio(&lista, 5);
    inserir_inicio(&lista, 10);
    inserir_fim(&lista, 3);
    inserir_ordenado(&lista, 7);
    
    imprimir(lista);
    
    printf("Quantidade: %d\n", contar(lista));
    
    inverter(&lista);
    imprimir(lista);
    
    liberar(&lista);
    
    return 0;
}
```

---

### Exercício 3.2: Lista Duplamente Encadeada
**Objetivo:** Implementar lista com ponteiros para anterior e próximo.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

// TODO: Implemente estas funções

DNode* criar_dnode(int valor);
void inserir_inicio(DNode **head, int valor);
void inserir_fim(DNode **head, int valor);
void remover_valor(DNode **head, int valor);
void imprimir_frente(DNode *head);
void imprimir_tras(DNode *head);  // do final para o início
void liberar(DNode **head);

int main() {
    DNode *lista = NULL;
    
    // Teste suas funções
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 20);
    inserir_fim(&lista, 30);
    
    printf("Da frente para trás: ");
    imprimir_frente(lista);
    
    printf("De trás para frente: ");
    imprimir_tras(lista);
    
    liberar(&lista);
    
    return 0;
}
```

---

### Exercício 3.3: Pilha (Stack)
**Objetivo:** Implementar estrutura de dados pilha usando ponteiros.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *topo;
    int tamanho;
} Pilha;

// TODO: Implemente estas funções

Pilha* criar_pilha();
int esta_vazia(Pilha *pilha);
void empilhar(Pilha *pilha, int valor);  // push
int desempilhar(Pilha *pilha, int *valor);  // pop (retorna 1 se sucesso)
int topo(Pilha *pilha, int *valor);  // peek (não remove)
int tamanho(Pilha *pilha);
void destruir_pilha(Pilha **pilha);

int main() {
    Pilha *pilha = criar_pilha();
    
    empilhar(pilha, 10);
    empilhar(pilha, 20);
    empilhar(pilha, 30);
    
    printf("Tamanho: %d\n", tamanho(pilha));
    
    int valor;
    if(topo(pilha, &valor)) {
        printf("Topo: %d\n", valor);
    }
    
    while(!esta_vazia(pilha)) {
        desempilhar(pilha, &valor);
        printf("Desempilhou: %d\n", valor);
    }
    
    destruir_pilha(&pilha);
    
    return 0;
}
```

---

### Exercício 3.4: Fila (Queue)
**Objetivo:** Implementar estrutura de dados fila usando ponteiros.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *inicio;
    Node *fim;
    int tamanho;
} Fila;

// TODO: Implemente estas funções

Fila* criar_fila();
int esta_vazia(Fila *fila);
void enfileirar(Fila *fila, int valor);  // enqueue
int desenfileirar(Fila *fila, int *valor);  // dequeue
int primeiro(Fila *fila, int *valor);  // peek
int tamanho(Fila *fila);
void destruir_fila(Fila **fila);

int main() {
    Fila *fila = criar_fila();
    
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);
    
    printf("Tamanho: %d\n", tamanho(fila));
    
    int valor;
    while(!esta_vazia(fila)) {
        desenfileirar(fila, &valor);
        printf("Desenfileirou: %d\n", valor);
    }
    
    destruir_fila(&fila);
    
    return 0;
}
```

---

### Exercício 3.5: Árvore Binária de Busca
**Objetivo:** Implementar árvore binária com inserção e busca.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *esquerda;
    struct TreeNode *direita;
} TreeNode;

// TODO: Implemente estas funções

TreeNode* criar_node(int valor);
TreeNode* inserir(TreeNode *raiz, int valor);
TreeNode* buscar(TreeNode *raiz, int valor);
int altura(TreeNode *raiz);
int contar_nos(TreeNode *raiz);
void imprimir_em_ordem(TreeNode *raiz);  // esquerda-raiz-direita
void imprimir_pre_ordem(TreeNode *raiz);  // raiz-esquerda-direita
void imprimir_pos_ordem(TreeNode *raiz);  // esquerda-direita-raiz
void liberar_arvore(TreeNode **raiz);

int main() {
    TreeNode *raiz = NULL;
    
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);
    
    printf("Em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");
    
    printf("Altura: %d\n", altura(raiz));
    printf("Nós: %d\n", contar_nos(raiz));
    
    int busca = 40;
    TreeNode *encontrado = buscar(raiz, busca);
    if(encontrado) {
        printf("Valor %d encontrado!\n", busca);
    }
    
    liberar_arvore(&raiz);
    
    return 0;
}
```

---

## Projetos Completos

### Projeto 1: Sistema de Gerenciamento de Estudantes

**Descrição:** Criar sistema completo com CRUD de estudantes usando structs e listas encadeadas.

**Requisitos:**
- Struct `Estudante` com: nome, matrícula, curso, notas (array dinâmico)
- Lista encadeada de estudantes
- Funções: adicionar, remover, buscar, listar todos, calcular média
- Menu interativo
- Salvar/carregar de arquivo (opcional)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    int matricula;
    char *curso;
    float *notas;
    int num_notas;
} Estudante;

typedef struct Node {
    Estudante *estudante;
    struct Node *next;
} Node;

// TODO: Implemente todas as funções necessárias

int main() {
    Node *lista = NULL;
    int opcao;
    
    do {
        printf("\n=== Sistema de Gerenciamento ===\n");
        printf("1. Adicionar estudante\n");
        printf("2. Remover estudante\n");
        printf("3. Buscar estudante\n");
        printf("4. Listar todos\n");
        printf("5. Calcular média geral\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        // TODO: Implemente o menu
        
    } while(opcao != 0);
    
    // TODO: Liberar memória
    
    return 0;
}
```

---

### Projeto 2: Agenda de Contatos

**Descrição:** Sistema de agenda com busca, ordenação e persistência.

**Requisitos:**
- Struct `Contato` com: nome, telefone, email, endereço
- Lista duplamente encadeada
- Busca por nome (parcial)
- Ordenação alfabética
- Exportar para arquivo CSV
- Importar de arquivo CSV

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    char *telefone;
    char *email;
    char *endereco;
} Contato;

typedef struct DNode {
    Contato *contato;
    struct DNode *prev;
    struct DNode *next;
} DNode;

// TODO: Implemente o projeto completo
```

---

### Projeto 3: Calculadora de Expressões

**Descrição:** Avaliar expressões matemáticas usando pilha.

**Requisitos:**
- Converter notação infixa para posfixa
- Avaliar expressão posfixa usando pilha
- Suportar: +, -, *, /, parênteses
- Validar expressão

**Exemplo:**
```
Entrada: "3 + 4 * 2 / ( 1 - 5 )"
Posfixa: "3 4 2 * 1 5 - / +"
Resultado: 1
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// TODO: Implemente o projeto
// Dica: Use uma pilha para operadores e outra para operandos
```

---

### Projeto 4: Editor de Texto Simples

**Descrição:** Editor com desfazer/refazer usando pilhas.

**Requisitos:**
- Lista encadeada de linhas de texto
- Pilha para desfazer (undo)
- Pilha para refazer (redo)
- Comandos: inserir linha, remover linha, editar, desfazer, refazer
- Salvar arquivo

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Linha {
    char *texto;
    struct Linha *next;
} Linha;

typedef struct Acao {
    enum { INSERIR, REMOVER, EDITAR } tipo;
    int linha_num;
    char *conteudo_anterior;
    char *conteudo_novo;
    struct Acao *next;
} Acao;

// TODO: Implemente o editor
```

---

## Desafios Extras

### Desafio 1: Merge de Listas Ordenadas
Mesclar duas listas encadeadas ordenadas em uma única lista ordenada.

```c
Node* merge_listas(Node *lista1, Node *lista2) {
    // TODO: Implemente
}
```

---

### Desafio 2: Detectar Ciclo em Lista
Verificar se uma lista encadeada possui ciclo (usa algoritmo Floyd - tartaruga e lebre).

```c
int tem_ciclo(Node *head) {
    // TODO: Implemente usando dois ponteiros
}
```

---

### Desafio 3: K-ésimo Elemento do Final
Encontrar o k-ésimo elemento a partir do final da lista em uma única passagem.

```c
Node* k_do_final(Node *head, int k) {
    // TODO: Implemente usando dois ponteiros
}
```

---

### Desafio 4: Inverter K Nós por Vez
Inverter lista em grupos de k nós.

**Exemplo:** 
```
Entrada: 1->2->3->4->5->6->7->8, k=3
Saída: 3->2->1->6->5->4->8->7
```

```c
Node* inverter_k_grupos(Node *head, int k) {
    // TODO: Implemente
}
```

---

### Desafio 5: LRU Cache
Implementar cache LRU (Least Recently Used) usando lista duplamente encadeada e hash table (simplificada).

```c
typedef struct {
    DNode *lista;
    int capacidade;
    int tamanho;
} LRUCache;

LRUCache* criar_cache(int capacidade);
int get(LRUCache *cache, int chave);
void put(LRUCache *cache, int chave, int valor);
```

---

## Dicas para Resolver os Exercícios

### 📝 Metodologia
1. **Leia atentamente** o enunciado e entenda o que é pedido
2. **Planeje** antes de programar (desenhe no papel se ajudar)
3. **Implemente** passo a passo, testando cada função
4. **Teste** com vários casos, incluindo casos extremos
5. **Debug** com prints ou debugger se necessário

### 🐛 Debug
```c
// Use prints para debug temporário
printf("DEBUG: ponteiro = %p, valor = %d\n", p, *p);

// Verifique ponteiros nulos
if(ptr == NULL) {
    printf("ERRO: ponteiro nulo!\n");
    return;
}

// Compile com flags de debug
// gcc -g -Wall -Wextra programa.c
```

### ✅ Verificação de Memória
```bash
# Sempre teste com valgrind
valgrind --leak-check=full ./programa

# Ou compile com AddressSanitizer
gcc -fsanitize=address -g programa.c
```

### 📚 Conceitos Importantes por Exercício

**Básicos (1.1-1.5):** Ponteiros simples, passagem por referência, aritmética básica

**Intermediários (2.1-2.5):** Alocação dinâmica, structs, ponteiros para funções

**Avançados (3.1-3.5):** Estruturas de dados complexas, recursão, algoritmos

---

## Links Relacionados

- [[Ponteiros em C - Guia Completo]]
- [[Soluções dos Exercícios]]
- [[Estruturas de Dados em C]]
- [[Debug e Testes]]

---

## Tags

#c #exercicios #ponteiros #pratica #estruturas-de-dados #algoritmos

---

**Última atualização:** 2025-01-20

**Nota:** As soluções completas estão em arquivo separado. Tente resolver primeiro por conta própria!
