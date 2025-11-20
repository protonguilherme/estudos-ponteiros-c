# Ponteiros em C - Guia Completo

## Índice
- [[#O que são ponteiros]]
- [[#1. Aritmética de Ponteiros]]
- [[#2. Ponteiros para Ponteiros]]
- [[#3. Ponteiros e Arrays Multidimensionais]]
- [[#4. Ponteiros para Funções]]
- [[#5. Array de Ponteiros para Funções]]
- [[#6. Ponteiros e Structs]]
- [[#7. Ponteiros Const]]
- [[#8. Ponteiros void]]
- [[#9. Ponteiros e Strings]]
- [[#10. Lista Encadeada]]
- [[#11. Problemas Comuns e Debugging]]

---

## O que são ponteiros?

Um ponteiro é uma variável que armazena o **endereço de memória** de outra variável. Em vez de guardar um valor direto (como 42), ele guarda "onde" esse valor está na memória.

### Declaração e operadores básicos

```c
int x = 10;      // variável normal
int *p;          // ponteiro para int (ainda não inicializado)
p = &x;          // p agora aponta para x (& = "endereço de")

printf("%d", x);   // imprime 10
printf("%d", *p);  // imprime 10 também (* = "valor apontado por")
```

**Operadores principais:**
- `&` (address-of): pega o endereço de uma variável
- `*` (dereference): acessa o valor no endereço apontado

### Exemplo prático

```c
#include <stdio.h>

int main() {
    int numero = 42;
    int *ponteiro = &numero;
    
    printf("Valor de numero: %d\n", numero);
    printf("Endereço de numero: %p\n", &numero);
    printf("Valor de ponteiro: %p\n", ponteiro);
    printf("Valor apontado por ponteiro: %d\n", *ponteiro);
    
    // Modificando através do ponteiro
    *ponteiro = 100;
    printf("Novo valor de numero: %d\n", numero);  // imprime 100
    
    return 0;
}
```

### Ponteiros e funções

```c
void incrementa(int *n) {
    (*n)++;  // incrementa o valor apontado
}

int main() {
    int x = 5;
    incrementa(&x);  // passa o endereço
    printf("%d\n", x);  // imprime 6
    return 0;
}
```

---

## 1. Aritmética de Ponteiros

### Conceito
Quando você faz operações matemáticas com ponteiros (soma, subtração), o compilador automaticamente multiplica o valor pelo tamanho do tipo. Se você tem `int *p` e faz `p++`, o ponteiro não avança 1 byte, mas sim `sizeof(int)` bytes (geralmente 4). Isso permite percorrer arrays naturalmente, pois cada incremento "pula" para o próximo elemento completo, não para o meio de um elemento.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

printf("Endereço de p: %p\n", p);           // ex: 0x1000
printf("%d\n", *p);                          // 10
p++;                                          
printf("Endereço após p++: %p\n", p);       // ex: 0x1004 (avançou 4 bytes)
printf("%d\n", *p);                          // 20

// Você pode fazer operações matemáticas
p += 2;                                      // avança 2 * sizeof(int) = 8 bytes
printf("%d\n", *p);                          // 40

// Subtração entre ponteiros retorna NÚMERO DE ELEMENTOS
int *inicio = arr;
int *fim = &arr[4];
printf("Distância: %ld elementos\n", fim - inicio);  // 4 (não 16 bytes!)

// Acesso via índice é na verdade aritmética
printf("%d\n", p[0]);      // equivalente a *(p + 0)
printf("%d\n", p[1]);      // equivalente a *(p + 1)
```

---

## 2. Ponteiros para Ponteiros (Múltiplos níveis)

### Conceito
Um ponteiro para ponteiro armazena o endereço de outro ponteiro. É como ter "camadas" de indireção. Isso é essencial quando você precisa modificar o próprio ponteiro (não apenas o valor apontado) dentro de uma função, ou quando trabalha com matrizes dinâmicas onde cada linha pode ter tamanho diferente. Cada `*` adicional é uma "camada" de indireção que você precisa atravessar para chegar ao valor final.

```c
int x = 100;
int *p = &x;        // p guarda o endereço de x
int **pp = &p;      // pp guarda o endereço de p
int ***ppp = &pp;   // ppp guarda o endereço de pp

printf("Valor de x: %d\n", x);           // 100
printf("Endereço de x: %p\n", &x);       // ex: 0x1000
printf("Valor de p (aponta para x): %p\n", p);     // 0x1000
printf("Através de p: %d\n", *p);        // 100

printf("Endereço de p: %p\n", &p);       // ex: 0x2000
printf("Valor de pp (aponta para p): %p\n", pp);   // 0x2000
printf("Através de pp: %d\n", **pp);     // 100 (precisa de 2 *)

// Modificando x através das camadas
***ppp = 200;
printf("x agora vale: %d\n", x);         // 200
```

### Uso prático: modificar ponteiro em função

```c
void aloca_array(int **ptr, int tamanho) {
    *ptr = (int*) malloc(tamanho * sizeof(int));
    // Sem **, não conseguiríamos modificar o ponteiro original
}

int *arr = NULL;
aloca_array(&arr, 10);  // agora arr aponta para memória alocada
free(arr);
```

### Matriz dinâmica

```c
// Cada linha pode ter tamanho diferente
int **matriz = (int**) malloc(3 * sizeof(int*));
matriz[0] = (int*) malloc(4 * sizeof(int));  // linha 0: 4 elementos
matriz[1] = (int*) malloc(2 * sizeof(int));  // linha 1: 2 elementos  
matriz[2] = (int*) malloc(5 * sizeof(int));  // linha 2: 5 elementos

matriz[1][0] = 42;

// Liberação em ordem reversa
for(int i = 0; i < 3; i++) {
    free(matriz[i]);
}
free(matriz);
```

---

## 3. Ponteiros e Arrays Multidimensionais

### Conceito
Um array 2D em C é na verdade um "array de arrays". `int matriz[3][4]` significa 3 arrays consecutivos, cada um com 4 ints. Na memória, está tudo em sequência linear. Um ponteiro para array `int (*p)[4]` aponta para um array completo de 4 ints, não para um único int. Isso é diferente de `int **p` (ponteiro para ponteiro). A notação `matriz[i][j]` é apenas açúcar sintático para `*(*(matriz + i) + j)`.

```c
// Array 2D estático - memória contígua
int matriz[3][4] = {
    {1, 2, 3, 4},      // linha 0
    {5, 6, 7, 8},      // linha 1
    {9, 10, 11, 12}    // linha 2
};
// Na memória: [1][2][3][4][5][6][7][8][9][10][11][12] (tudo junto)

// Ponteiro para array de 4 ints (não é ponteiro para ponteiro!)
int (*p)[4] = matriz;  
printf("%d\n", p[1][2]);  // 7
```

### Diferentes formas de acesso

```c
// As diferentes formas de acessar são equivalentes:
printf("%d\n", matriz[1][2]);              // 7 - notação normal
printf("%d\n", *(*(matriz + 1) + 2));      // 7 - aritmética pura
printf("%d\n", (*(matriz + 1))[2]);        // 7 - mista
printf("%d\n", *(&matriz[0][0] + 1*4 + 2)); // 7 - posição linear
```

### Passando para função

```c
void imprime1(int mat[][4], int linhas) { }
void imprime2(int (*mat)[4], int linhas) { }  // equivalente
void imprime3(int *mat, int linhas, int colunas) {
    // acessa como: mat[i * colunas + j]
}
```

### Diferença crucial

```c
int *vet[4];     // array de 4 ponteiros
int (*ptr)[4];   // ponteiro para array de 4 ints
```

---

## 4. Ponteiros para Funções

### Conceito
Funções também têm endereços na memória (no segmento de código). Um ponteiro para função armazena esse endereço e permite chamar a função indiretamente. Isso é fundamental para callbacks (passar funções como argumentos), polimorfismo em C, tabelas de dispatch, e implementar padrões como Strategy e Observer sem orientação a objetos. A sintaxe é confusa, mas o conceito é simples: guardar "qual função executar" como uma variável.

```c
#include <stdio.h>

// Funções simples
int soma(int a, int b) { return a + b; }
int subtrai(int a, int b) { return a - b; }
int multiplica(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

// Declarando ponteiro para função que recebe 2 ints e retorna int
int (*func_ptr)(int, int);

// Função de ordem superior (recebe função como parâmetro)
int calculadora(int x, int y, int (*operacao)(int, int)) {
    printf("Executando operação...\n");
    return operacao(x, y);  // chama a função através do ponteiro
}
```

### Exemplo de uso

```c
int main() {
    // Atribuindo funções ao ponteiro
    func_ptr = soma;           // nome da função é seu endereço
    printf("5 + 3 = %d\n", func_ptr(5, 3));  // 8
    
    func_ptr = multiplica;
    printf("5 * 3 = %d\n", func_ptr(5, 3));  // 15
    
    // Usando callback
    printf("10 - 2 = %d\n", calculadora(10, 2, subtrai));  // 8
    
    return 0;
}
```

### Typedef para simplificar

```c
typedef int (*operacao_binaria)(int, int);

operacao_binaria escolher_op(char op) {
    switch(op) {
        case '+': return soma;
        case '-': return subtrai;
        case '*': return multiplica;
        case '/': return divide;
        default: return NULL;
    }
}
```

---

## 5. Array de Ponteiros para Funções

### Conceito
Você pode criar arrays onde cada elemento é um ponteiro para função. Isso permite criar "menus" de operações, máquinas de estado, parsers de comandos, e implementar polimorfismo. É como ter uma lista de "ações possíveis" que você pode executar dinamicamente baseado em um índice ou condição. Muito usado em sistemas embarcados e interpretadores.

```c
typedef int (*operacao_t)(int, int);

int main() {
    // Array de ponteiros para funções
    operacao_t operacoes[] = {soma, subtrai, multiplica, divide};
    const char *nomes[] = {"Soma", "Subtração", "Multiplicação", "Divisão"};
    
    int a = 20, b = 4;
    
    // Executando todas as operações
    for(int i = 0; i < 4; i++) {
        printf("%s: %d\n", nomes[i], operacoes[i](a, b));
    }
    
    return 0;
}
```

### Máquina de Estados

```c
typedef enum { IDLE, RUNNING, PAUSED, STOPPED } Estado;

void estado_idle() { printf("Sistema ocioso\n"); }
void estado_running() { printf("Sistema executando\n"); }
void estado_paused() { printf("Sistema pausado\n"); }
void estado_stopped() { printf("Sistema parado\n"); }

void (*estados[])() = {
    estado_idle,
    estado_running,
    estado_paused,
    estado_stopped
};

void executar_estado(Estado e) {
    estados[e]();  // chama função correspondente ao estado
}
```

### Sistema de Comandos

```c
typedef struct {
    const char *nome;
    void (*executar)(void);
} Comando;

void cmd_help() { printf("Comandos disponíveis: help, quit, status\n"); }
void cmd_quit() { printf("Encerrando...\n"); }
void cmd_status() { printf("Sistema OK\n"); }

Comando comandos[] = {
    {"help", cmd_help},
    {"quit", cmd_quit},
    {"status", cmd_status},
    {NULL, NULL}  // sentinel
};

void processar_comando(const char *cmd) {
    for(int i = 0; comandos[i].nome != NULL; i++) {
        if(strcmp(comandos[i].nome, cmd) == 0) {
            comandos[i].executar();
            return;
        }
    }
    printf("Comando desconhecido\n");
}
```

---

## 6. Ponteiros e Structs

### Conceito
Structs são blocos de memória contíguos que agrupam diferentes tipos. Passar structs por valor copia toda a struct (lento para structs grandes). Passar ponteiros para struct é eficiente pois copia apenas o endereço (geralmente 8 bytes). O operador `->` é açúcar sintático para `(*ptr).membro` e é usado para acessar membros através de ponteiros. Isso é fundamental para listas encadeadas, árvores, e qualquer estrutura de dados dinâmica.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int idade;
    float salario;
} Pessoa;
```

### Passando por valor vs por ponteiro

```c
// Passando por valor (COPIA toda a struct - ineficiente)
void imprime_por_valor(Pessoa p) {
    printf("%s, %d anos, R$ %.2f\n", p.nome, p.idade, p.salario);
    p.salario += 1000;  // NÃO afeta a struct original!
}

// Passando por ponteiro (EFICIENTE - apenas 8 bytes copiados)
void aumenta_salario(Pessoa *p, float percentual) {
    // p->salario é equivalente a (*p).salario
    p->salario *= (1 + percentual/100);
    // Modifica a struct original!
}
```

### Formas de acesso

```c
int main() {
    Pessoa joao = {"João Silva", 30, 5000.0};
    Pessoa *ptr = &joao;
    
    // Três formas de acessar membros:
    printf("Forma 1: %s\n", joao.nome);        // direto
    printf("Forma 2: %s\n", ptr->nome);        // através de ponteiro (->)
    printf("Forma 3: %s\n", (*ptr).nome);      // dereferência explícita
    
    return 0;
}
```

### Struct com ponteiro interno (autoreferência)

```c
typedef struct Node {
    int valor;
    struct Node *proximo;  // ponteiro para outro Node
} Node;

// Criando lista encadeada
Node *criar_node(int val) {
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo != NULL) {
        novo->valor = val;
        novo->proximo = NULL;
    }
    return novo;
}
```

---

## 7. Ponteiros Const (Imutabilidade)

### Conceito
`const` define o que não pode mudar: o valor apontado ou o próprio ponteiro. A regra: leia da direita para esquerda. `const int *p` = "ponteiro para int constante" (não pode mudar o int). `int *const p` = "ponteiro constante para int" (não pode mudar o ponteiro). `const int *const p` = ambos constantes. Isso garante segurança em funções (evita modificações acidentais) e documenta intenções no código. O compilador gera erro se você tentar violar.

```c
int x = 10, y = 20;

// 1. Ponteiro para constante (valor não pode mudar)
const int *p1 = &x;
int const *p2 = &x;  // equivalente

printf("%d\n", *p1);  // OK - pode ler
// *p1 = 30;          // ERRO! não pode modificar o valor
p1 = &y;              // OK - pode mudar para onde aponta

// 2. Ponteiro constante (ponteiro não pode mudar)
int *const p3 = &x;

*p3 = 30;             // OK - pode modificar o valor
// p3 = &y;           // ERRO! não pode reatribuir o ponteiro

// 3. Ponteiro constante para constante (nada pode mudar)
const int *const p4 = &x;

printf("%d\n", *p4);  // OK - apenas leitura
// *p4 = 40;          // ERRO! valor constante
// p4 = &y;           // ERRO! ponteiro constante
```

### Uso prático: proteção em funções

```c
// Função que não deve modificar o array
int soma_array(const int *arr, int tamanho) {
    int total = 0;
    for(int i = 0; i < tamanho; i++) {
        total += arr[i];
        // arr[i] = 0;  // ERRO! const impede modificação
    }
    return total;
}

// Função que não deve modificar a string
size_t tamanho_string(const char *str) {
    size_t len = 0;
    while(str[len] != '\0') {
        len++;
        // str[len] = 'x';  // ERRO! const protege
    }
    return len;
}
```

---

## 8. Ponteiros void (Genéricos)

### Conceito
`void*` é um ponteiro genérico que pode apontar para qualquer tipo. Não tem tipo específico, então você não pode dereferenciá-lo diretamente (`*ptr` não funciona) nem fazer aritmética de ponteiros. Você precisa fazer cast para o tipo correto antes de usar. É usado em funções genéricas (como `malloc`, `qsort`, `memcpy`) que funcionam com qualquer tipo de dado. É o "escape hatch" para polimorfismo em C, mas perde type safety (o compilador não te avisa de erros de tipo).

```c
// void* permite função genérica
void troca_generica(void *a, void *b, size_t tamanho) {
    // Tratamos como arrays de bytes (unsigned char)
    unsigned char *pa = (unsigned char*)a;
    unsigned char *pb = (unsigned char*)b;
    unsigned char temp;
    
    // Troca byte por byte
    for(size_t i = 0; i < tamanho; i++) {
        temp = pa[i];
        pa[i] = pb[i];
        pb[i] = temp;
    }
}
```

### Exemplo de uso

```c
int main() {
    int x = 5, y = 10;
    printf("Antes: x=%d, y=%d\n", x, y);
    troca_generica(&x, &y, sizeof(int));
    printf("Depois: x=%d, y=%d\n", x, y);
    
    float a = 3.14, b = 2.71;
    printf("Antes: a=%.2f, b=%.2f\n", a, b);
    troca_generica(&a, &b, sizeof(float));
    printf("Depois: a=%.2f, b=%.2f\n", a, b);
    
    return 0;
}
```

### Comparador genérico (para qsort)

```c
int comparar_ints(const void *a, const void *b) {
    // Precisa fazer cast para o tipo correto
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    
    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;
}

// Usando qsort
int numeros[] = {5, 2, 9, 1, 7, 3};
size_t n = sizeof(numeros) / sizeof(numeros[0]);
qsort(numeros, n, sizeof(int), comparar_ints);
```

### ⚠️ ATENÇÃO: void* perde type safety!

```c
void exemplo_perigo() {
    int x = 42;
    void *p = &x;
    
    // Isso compila mas está ERRADO!
    double *d = (double*)p;  // cast errado
    // *d agora interpreta 4 bytes de int como 8 bytes de double!
}
```

---

## 9. Ponteiros e Strings

### Conceito
Em C, strings são arrays de `char` terminados com `\0` (null terminator). Há 3 formas principais de criar strings: (1) literal de string `"texto"` fica em memória read-only e retorna `char*`, modificar causa crash; (2) array `char str[]` fica na stack, é mutável e copia o conteúdo; (3) `malloc` fica no heap, é mutável e precisa de `free`. Ponteiros para strings podem apenas mudar para onde apontam, enquanto arrays de char podem ter seu conteúdo modificado mas o "ponteiro base" é fixo.

```c
// 1. STRING LITERAL (memória read-only)
char *str1 = "Hello";
printf("%s\n", str1);       // OK - leitura
// str1[0] = 'h';           // ERRO! Segmentation Fault
str1 = "World";             // OK - pode apontar para outra string

// 2. ARRAY DE CHAR (stack, mutável)
char str2[] = "Hello";      // cria array [H][e][l][l][o][\0]
str2[0] = 'h';              // OK! modificável
printf("%s\n", str2);       // "hello"
// str2 = "World";          // ERRO! str2 é constante

// 3. ALOCAÇÃO DINÂMICA (heap, mutável)
char *str3 = (char*) malloc(6 * sizeof(char));
strcpy(str3, "Hello");
str3[0] = 'h';              // OK! modificável
free(str3);
```

### Comparando os 3 métodos

```c
printf("sizeof(str1): %zu\n", sizeof(str1));  // 8 (tamanho de ponteiro)
printf("sizeof(str2): %zu\n", sizeof(str2));  // 6 (array inclui \0)
printf("strlen(str2): %zu\n", strlen(str2));  // 5 (não conta \0)
```

### Funções comuns com strings

```c
char str[50];

// Cópia segura (limitando tamanho)
strncpy(str, "Hello World", sizeof(str) - 1);
str[sizeof(str) - 1] = '\0';  // garante terminação

// Concatenação
char dest[100] = "Hello";
strcat(dest, " World");  // dest agora é "Hello World"

// Comparação (retorna 0 se iguais)
if(strcmp(str, dest) == 0) {
    printf("Strings iguais\n");
}

// Busca de caractere
char *pos = strchr(str, 'W');
if(pos != NULL) {
    printf("'W' encontrado na posição: %ld\n", pos - str);
}
```

### Array de strings

```c
// Cada elemento aponta para string literal
char *frutas[] = {
    "Maçã",
    "Banana",
    "Laranja",
    NULL  // sentinel para marcar fim
};

for(int i = 0; frutas[i] != NULL; i++) {
    printf("%s\n", frutas[i]);
}

// Ou array 2D de chars
char cores[][10] = {
    "Vermelho",
    "Azul",
    "Verde"
};
```

### Lendo string do usuário (seguro)

```c
char nome[50];

// ERRADO (buffer overflow possível):
// scanf("%s", nome);
// gets(nome);  // NUNCA use gets()!

// CORRETO (limita tamanho):
scanf("%49s", nome);  // lê no máximo 49 chars + \0

// Ou use fgets (mais seguro):
fgets(nome, sizeof(nome), stdin);

// Remove newline se houver
size_t len = strlen(nome);
if(len > 0 && nome[len-1] == '\n') {
    nome[len-1] = '\0';
}
```

---

## 10. Lista Encadeada (Exemplo Completo)

### Conceito
Uma lista encadeada é uma estrutura de dados dinâmica onde cada elemento (nó) contém dados e um ponteiro para o próximo nó. Diferente de arrays, os nós não precisam estar em memória contígua - podem estar espalhados. O último nó aponta para `NULL` para marcar o fim. A lista é representada por um ponteiro para o primeiro nó (head). Inserções/remoções são O(1) se você tem o ponteiro, mas busca é O(n). Cada nó é alocado dinamicamente e deve ser liberado individualmente.

```c
#include <stdio.h>
#include <stdlib.h>

// Definição do nó (struct autoreferenciada)
typedef struct Node {
    int data;              // dados do nó
    struct Node *next;     // ponteiro para próximo nó
} Node;
```

### Criar novo nó

```c
Node* criar_node(int valor) {
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL) {
        printf("Erro: memória insuficiente\n");
        return NULL;
    }
    novo->data = valor;
    novo->next = NULL;
    return novo;
}
```

### Inserir no início (O(1))

```c
void inserir_inicio(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    novo->next = *head;    // novo aponta para antigo primeiro
    *head = novo;          // head agora aponta para novo
    
    // Por que **head? Precisamos MODIFICAR o ponteiro head original!
}
```

### Inserir no final (O(n))

```c
void inserir_fim(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    // Se lista vazia, novo é o primeiro
    if(*head == NULL) {
        *head = novo;
        return;
    }
    
    // Percorre até o último nó
    Node *atual = *head;
    while(atual->next != NULL) {
        atual = atual->next;
    }
    
    atual->next = novo;  // último nó aponta para novo
}
```

### Buscar valor

```c
Node* buscar(Node *head, int valor) {
    Node *atual = head;
    while(atual != NULL) {
        if(atual->data == valor) {
            return atual;  // encontrou
        }
        atual = atual->next;
    }
    return NULL;  // não encontrou
}
```

### Remover valor

```c
int remover_valor(Node **head, int valor) {
    if(*head == NULL) return 0;
    
    Node *temp;
    
    // Se é o primeiro nó
    if((*head)->data == valor) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return 1;
    }
    
    // Procura o nó anterior ao que será removido
    Node *atual = *head;
    while(atual->next != NULL && atual->next->data != valor) {
        atual = atual->next;
    }
    
    if(atual->next == NULL) return 0;  // não encontrou
    
    temp = atual->next;
    atual->next = temp->next;  // "pula" o nó a ser removido
    free(temp);
    return 1;
}
```

### Imprimir lista

```c
void imprimir(Node *head) {
    Node *atual = head;
    printf("Lista: ");
    while(atual != NULL) {
        printf("%d -> ", atual->data);
        atual = atual->next;
    }
    printf("NULL\n");
}
```

### Inverter lista

```c
void inverter(Node **head) {
    Node *anterior = NULL;
    Node *atual = *head;
    Node *proximo = NULL;
    
    while(atual != NULL) {
        proximo = atual->next;    // salva próximo
        atual->next = anterior;   // inverte o link
        anterior = atual;         // avança anterior
        atual = proximo;          // avança atual
    }
    
    *head = anterior;  // novo head é o antigo último
}
```

### Liberar memória (CRÍTICO!)

```c
void liberar(Node **head) {
    Node *atual = *head;
    Node *temp;
    
    while(atual != NULL) {
        temp = atual;
        atual = atual->next;
        free(temp);
    }
    
    *head = NULL;
}
```

### Exemplo de uso completo

```c
int main() {
    Node *lista = NULL;  // lista vazia
    
    printf("=== Inserindo elementos ===\n");
    inserir_inicio(&lista, 10);
    inserir_inicio(&lista, 20);
    inserir_inicio(&lista, 30);
    imprimir(lista);  // 30 -> 20 -> 10 -> NULL
    
    inserir_fim(&lista, 5);
    inserir_fim(&lista, 1);
    imprimir(lista);  // 30 -> 20 -> 10 -> 5 -> 1 -> NULL
    
    printf("\n=== Removendo elementos ===\n");
    remover_valor(&lista, 15);
    imprimir(lista);
    
    printf("\n=== Invertendo lista ===\n");
    inverter(&lista);
    imprimir(lista);
    
    printf("\n=== Liberando memória ===\n");
    liberar(&lista);
    
    return 0;
}
```

---

## 11. Problemas Comuns e Debugging

### Conceito
Ponteiros são poderosos mas perigosos. Os erros mais comuns são: (1) **Memory leak** - alocar memória e perder a referência sem fazer `free`, acumula até esgotar RAM; (2) **Dangling pointer** - usar ponteiro após o endereço ficar inválido (variável fora de escopo ou já liberada); (3) **Double free** - liberar mesma memória duas vezes, corrompe o heap; (4) **Uninitialized pointer** - ponteiro não inicializado aponta para lixo, acessar causa crash; (5) **Buffer overflow** - escrever além dos limites do array, corrompe memória adjacente.

### 1. Memory Leak

```c
void leak_exemplo() {
    int *p = malloc(sizeof(int));
    *p = 42;
    
    p = malloc(sizeof(int));  // ERRO! perdeu referência do primeiro malloc
    *p = 100;
    
    free(p);  // libera o segundo, mas o primeiro ficou perdido!
}

void leak_em_loop() {
    for(int i = 0; i < 1000; i++) {
        int *p = malloc(sizeof(int));
        // esqueceu de fazer free!
    }
    // Alocou 1000 blocos e perdeu todos!
}
```

### 2. Dangling Pointer

```c
int* dangling_exemplo1() {
    int x = 10;
    return &x;  // ERRO! x sai de escopo, endereço fica inválido
}

void dangling_exemplo2() {
    int *p = malloc(sizeof(int));
    *p = 42;
    free(p);
    
    printf("%d\n", *p);  // ERRO! usando memória já liberada
    *p = 100;            // ERRO! pode crashar
    
    // CORREÇÃO: após free, fazer p = NULL
}
```

### 3. Double Free

```c
void double_free_exemplo() {
    int *p = malloc(sizeof(int));
    *p = 42;
    
    free(p);
    free(p);  // ERRO! liberando duas vezes
    
    // CORREÇÃO:
    // free(p);
    // p = NULL;
    // free(p);  // free(NULL) é seguro
}
```

### 4. Uninitialized Pointer

```c
void uninitialized_exemplo() {
    int *p;  // contém lixo (endereço aleatório)
    
    *p = 10;  // ERRO! escreve em endereço aleatório
    
    // CORREÇÃO:
    // int *p = NULL;
    // p = malloc(sizeof(int));
    // if(p != NULL) { *p = 10; }
}
```

### 5. Buffer Overflow

```c
void buffer_overflow_exemplo() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = arr;
    
    p[10] = 42;  // ERRO! arr só tem 5 elementos
    
    // String overflow
    char nome[5];
    strcpy(nome, "Este nome é muito longo");  // ERRO!
    
    // CORREÇÃO: use strncpy
    // strncpy(nome, "João", sizeof(nome) - 1);
    // nome[sizeof(nome) - 1] = '\0';
}
```

### 6. NULL Pointer Dereference

```c
void null_deref_exemplo() {
    int *p = NULL;
    
    *p = 10;  // ERRO! Segmentation Fault
    
    // CORREÇÃO: sempre verifique
    // if(p != NULL) {
    //     *p = 10;
    // }
}
```

---

## Ferramentas de Debug

### 1. Valgrind (Linux/Mac)

```bash
# Compilar com símbolos de debug
gcc -g programa.c -o programa

# Executar com valgrind
valgrind --leak-check=full ./programa
```

**Detecta:**
- Memory leaks
- Invalid reads/writes
- Use after free
- Double free

### 2. AddressSanitizer (GCC/Clang)

```bash
# Compilar com AddressSanitizer
gcc -fsanitize=address -g programa.c -o programa

# Executar normalmente
./programa
```

**Detecta (mais rápido que valgrind):**
- Buffer overflows
- Use after free
- Memory leaks
- Double free

### 3. GDB (GNU Debugger)

```bash
# Compilar com símbolos de debug
gcc -g programa.c -o programa

# Iniciar debugger
gdb ./programa
```

**Comandos úteis:**
- `break main` - breakpoint na main
- `run` - executa
- `print p` - mostra valor de p
- `print *p` - mostra valor apontado
- `backtrace` - mostra call stack
- `watch *p` - para quando *p mudar

---

## Boas Práticas

### ✅ Sempre inicialize ponteiros
```c
int *p = NULL;
```

### ✅ Sempre verifique malloc
```c
p = malloc(sizeof(int));
if(p == NULL) {
    fprintf(stderr, "Erro ao alocar memória\n");
    return;
}
```

### ✅ Libere memória
```c
free(p);
p = NULL;  // anule após free
```

### ✅ Cuidado com tamanho
```c
int n = 10;
int *arr = malloc(n * sizeof(int));  // sizeof(int), não sizeof(arr)
```

### ❌ Nunca retorne ponteiro para variável local
```c
// NUNCA faça isso:
int* funcao() {
    int x = 10;
    return &x;  // ERRO!
}
```

---

## Tags para Organização

#c #programacao #ponteiros #memoria #estruturas-de-dados #guia

---

## Links Relacionados

- [[Gerenciamento de Memória em C]]
- [[Estruturas de Dados em C]]
- [[Debug e Ferramentas]]
- [[Boas Práticas de Programação]]

---

**Última atualização:** 2025-01-20
