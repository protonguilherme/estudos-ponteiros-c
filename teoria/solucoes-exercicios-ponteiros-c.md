# Soluções - Exercícios de Ponteiros em C

> ⚠️ **AVISO:** Tente resolver os exercícios por conta própria antes de ver as soluções!

## Índice
- [[#Soluções Nível 1 - Básico]]
- [[#Soluções Nível 2 - Intermediário]]
- [[#Soluções Nível 3 - Avançado]]
- [[#Explicações Detalhadas]]

---

## Soluções Nível 1 - Básico

### Solução 1.1: Primeiros Passos com Ponteiros

```c
#include <stdio.h>

int main() {
    int x = 42;
    int *p = &x;  // p aponta para x
    
    printf("Valor através do ponteiro: %d\n", *p);
    
    *p = 100;  // modifica x através do ponteiro
    
    printf("Novo valor: %d\n", x);
    
    return 0;
}
```

**Explicação:**
- `int *p = &x;` - ponteiro p recebe o endereço de x
- `*p` - dereferencia o ponteiro para acessar/modificar o valor
- Modificar `*p` é o mesmo que modificar `x`

---

### Solução 1.2: Troca de Valores

```c
#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;  // salva valor de a
    *a = *b;        // a recebe valor de b
    *b = temp;      // b recebe valor original de a
}

int main() {
    int x = 10, y = 20;
    
    printf("Antes: x=%d, y=%d\n", x, y);
    trocar(&x, &y);
    printf("Depois: x=%d, y=%d\n", x, y);
    
    return 0;
}
```

**Explicação:**
- Passamos `&x` e `&y` (endereços) para a função
- Dentro da função, usamos `*a` e `*b` para modificar os valores originais
- Sem ponteiros, a troca não funcionaria (passagem por valor apenas copiaria)

---

### Solução 1.3: Soma de Array

```c
#include <stdio.h>

int soma_array(int *arr, int tamanho) {
    int soma = 0;
    int *p = arr;  // ponteiro para o início
    
    for(int i = 0; i < tamanho; i++) {
        soma += *p;  // soma o valor apontado
        p++;         // avança para o próximo elemento
    }
    
    return soma;
}

// Alternativa mais concisa:
int soma_array_v2(int *arr, int tamanho) {
    int soma = 0;
    for(int i = 0; i < tamanho; i++) {
        soma += *(arr + i);  // aritmética de ponteiros
    }
    return soma;
}

int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int tamanho = 5;
    
    int resultado = soma_array(numeros, tamanho);
    printf("Soma: %d\n", resultado);
    
    return 0;
}
```

**Explicação:**
- `arr` já é um ponteiro para o primeiro elemento
- `p++` avança `sizeof(int)` bytes automaticamente
- `*(arr + i)` é equivalente a `arr[i]`

---

### Solução 1.4: Maior e Menor Valor

```c
#include <stdio.h>

void encontrar_max_min(int *arr, int tamanho, int *max, int *min) {
    if(tamanho == 0) return;
    
    // Inicializa com o primeiro elemento
    *max = *arr;
    *min = *arr;
    
    // Percorre o resto do array
    for(int i = 1; i < tamanho; i++) {
        if(*(arr + i) > *max) {
            *max = *(arr + i);
        }
        if(*(arr + i) < *min) {
            *min = *(arr + i);
        }
    }
}

int main() {
    int numeros[] = {45, 12, 89, 3, 67, 23};
    int tamanho = 6;
    int maior, menor;
    
    encontrar_max_min(numeros, tamanho, &maior, &menor);
    
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);
    
    return 0;
}
```

**Explicação:**
- Passamos `&maior` e `&menor` para que a função possa modificá-los
- Usamos `*max` e `*min` dentro da função para atribuir valores
- Isso permite retornar dois valores através dos parâmetros

---

### Solução 1.5: Inverter String

```c
#include <stdio.h>
#include <string.h>

void inverter_string(char *str) {
    if(str == NULL) return;
    
    char *inicio = str;
    char *fim = str + strlen(str) - 1;  // último caractere
    
    while(inicio < fim) {
        // Troca os caracteres
        char temp = *inicio;
        *inicio = *fim;
        *fim = temp;
        
        // Avança início e recua fim
        inicio++;
        fim--;
    }
}

int main() {
    char texto[] = "Ponteiros";
    
    printf("Antes: %s\n", texto);
    inverter_string(texto);
    printf("Depois: %s\n", texto);
    
    return 0;
}
```

**Explicação:**
- Dois ponteiros: um no início, outro no fim
- Trocamos os valores e movemos os ponteiros em direção ao centro
- Para quando `inicio >= fim` (se encontraram no meio)

---

## Soluções Nível 2 - Intermediário

### Solução 2.1: Alocação Dinâmica de Array

```c
#include <stdio.h>
#include <stdlib.h>

int* criar_array_sequencial(int tamanho) {
    // Aloca memória
    int *arr = (int*) malloc(tamanho * sizeof(int));
    
    if(arr == NULL) {
        return NULL;  // falha na alocação
    }
    
    // Preenche com valores de 1 a tamanho
    for(int i = 0; i < tamanho; i++) {
        arr[i] = i + 1;
    }
    
    return arr;
}

int main() {
    int tamanho = 10;
    int *arr = criar_array_sequencial(tamanho);
    
    if(arr == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);  // SEMPRE libere!
    return 0;
}
```

**Explicação:**
- `malloc` aloca memória no heap
- Sempre verifique se `malloc` retornou NULL
- Quem chama a função é responsável por dar `free`

---

### Solução 2.2: Matriz Dinâmica

```c
#include <stdio.h>
#include <stdlib.h>

int** criar_matriz(int linhas, int colunas) {
    // Aloca array de ponteiros (linhas)
    int **matriz = (int**) malloc(linhas * sizeof(int*));
    if(matriz == NULL) return NULL;
    
    // Aloca cada linha
    for(int i = 0; i < linhas; i++) {
        matriz[i] = (int*) malloc(colunas * sizeof(int));
        if(matriz[i] == NULL) {
            // Se falhar, libera o que já foi alocado
            for(int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }
    
    return matriz;
}

void preencher_matriz(int **matriz, int linhas, int colunas, int valor) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            matriz[i][j] = valor;
        }
    }
}

void imprimir_matriz(int **matriz, int linhas, int colunas) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz(int **matriz, int linhas) {
    // Libera cada linha primeiro
    for(int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    // Depois libera o array de ponteiros
    free(matriz);
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

**Explicação:**
- Matriz dinâmica = array de ponteiros, cada um aponta para uma linha
- Liberar na ordem reversa: primeiro as linhas, depois o array principal
- Tratamento de erro: se uma alocação falhar, libera tudo que já foi alocado

---

### Solução 2.3: Remover Duplicatas

```c
#include <stdio.h>
#include <stdlib.h>

int* remover_duplicatas(int *arr, int tamanho, int *novo_tamanho) {
    if(tamanho == 0) {
        *novo_tamanho = 0;
        return NULL;
    }
    
    // Aloca array temporário (pior caso: todos únicos)
    int *temp = (int*) malloc(tamanho * sizeof(int));
    if(temp == NULL) return NULL;
    
    int count = 0;
    
    // Para cada elemento, verifica se já está no resultado
    for(int i = 0; i < tamanho; i++) {
        int duplicado = 0;
        
        for(int j = 0; j < count; j++) {
            if(arr[i] == temp[j]) {
                duplicado = 1;
                break;
            }
        }
        
        if(!duplicado) {
            temp[count] = arr[i];
            count++;
        }
    }
    
    // Aloca array do tamanho exato
    int *resultado = (int*) malloc(count * sizeof(int));
    if(resultado == NULL) {
        free(temp);
        return NULL;
    }
    
    // Copia elementos únicos
    for(int i = 0; i < count; i++) {
        resultado[i] = temp[i];
    }
    
    free(temp);
    *novo_tamanho = count;
    return resultado;
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

**Explicação:**
- Usa array temporário para construir resultado
- Verifica cada elemento se já existe no resultado
- Aloca array final do tamanho exato necessário
- Complexidade: O(n²) - para array ordenado pode ser O(n)

---

### Solução 2.4: Struct com Ponteiros

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

Aluno* criar_aluno(const char *nome, int idade, int num_notas) {
    Aluno *aluno = (Aluno*) malloc(sizeof(Aluno));
    if(aluno == NULL) return NULL;
    
    // Aloca e copia nome
    aluno->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
    if(aluno->nome == NULL) {
        free(aluno);
        return NULL;
    }
    strcpy(aluno->nome, nome);
    
    // Define idade
    aluno->idade = idade;
    
    // Aloca array de notas
    aluno->notas = (float*) malloc(num_notas * sizeof(float));
    if(aluno->notas == NULL) {
        free(aluno->nome);
        free(aluno);
        return NULL;
    }
    aluno->num_notas = num_notas;
    
    // Inicializa notas com 0
    for(int i = 0; i < num_notas; i++) {
        aluno->notas[i] = 0.0;
    }
    
    return aluno;
}

void adicionar_nota(Aluno *aluno, int indice, float nota) {
    if(aluno == NULL || indice < 0 || indice >= aluno->num_notas) {
        return;
    }
    aluno->notas[indice] = nota;
}

float calcular_media(Aluno *aluno) {
    if(aluno == NULL || aluno->num_notas == 0) {
        return 0.0;
    }
    
    float soma = 0.0;
    for(int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    
    return soma / aluno->num_notas;
}

void destruir_aluno(Aluno **aluno) {
    if(aluno == NULL || *aluno == NULL) return;
    
    // Libera na ordem: strings, arrays, struct
    free((*aluno)->nome);
    free((*aluno)->notas);
    free(*aluno);
    
    *aluno = NULL;  // evita dangling pointer
}

int main() {
    Aluno *aluno = criar_aluno("João Silva", 20, 4);
    
    if(aluno == NULL) {
        printf("Erro ao criar aluno\n");
        return 1;
    }
    
    adicionar_nota(aluno, 0, 8.5);
    adicionar_nota(aluno, 1, 9.0);
    adicionar_nota(aluno, 2, 7.5);
    adicionar_nota(aluno, 3, 8.0);
    
    printf("Aluno: %s\n", aluno->nome);
    printf("Idade: %d\n", aluno->idade);
    printf("Média: %.2f\n", calcular_media(aluno));
    
    destruir_aluno(&aluno);
    
    return 0;
}
```

**Explicação:**
- Struct contém ponteiros que precisam ser alocados separadamente
- Sempre verifique cada `malloc` e limpe se algum falhar
- Libere na ordem reversa da alocação
- Use `**aluno` em destruir para poder anular o ponteiro original

---

### Solução 2.5: Função Callback

```c
#include <stdio.h>

void aplicar_operacao(int *arr, int tamanho, int (*operacao)(int)) {
    for(int i = 0; i < tamanho; i++) {
        arr[i] = operacao(arr[i]);  // aplica função a cada elemento
    }
}

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
    
    // Resetar array
    int numeros2[] = {1, 2, 3, 4, 5};
    
    aplicar_operacao(numeros2, tamanho, quadrado);
    printf("Quadrado: ");
    for(int i = 0; i < tamanho; i++) printf("%d ", numeros2[i]);
    printf("\n");
    
    return 0;
}
```

**Explicação:**
- `int (*operacao)(int)` é um ponteiro para função
- Podemos passar diferentes funções como argumento
- A função é chamada normalmente: `operacao(valor)`
- Permite criar código genérico e reutilizável

---

## Soluções Nível 3 - Avançado

### Solução 3.1: Lista Encadeada Completa

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* criar_node(int valor) {
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL) return NULL;
    
    novo->data = valor;
    novo->next = NULL;
    return novo;
}

void inserir_inicio(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    novo->next = *head;
    *head = novo;
}

void inserir_fim(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    if(*head == NULL) {
        *head = novo;
        return;
    }
    
    Node *atual = *head;
    while(atual->next != NULL) {
        atual = atual->next;
    }
    atual->next = novo;
}

void inserir_ordenado(Node **head, int valor) {
    Node *novo = criar_node(valor);
    if(novo == NULL) return;
    
    // Se lista vazia ou valor menor que o primeiro
    if(*head == NULL || (*head)->data >= valor) {
        novo->next = *head;
        *head = novo;
        return;
    }
    
    // Encontra posição correta
    Node *atual = *head;
    while(atual->next != NULL && atual->next->data < valor) {
        atual = atual->next;
    }
    
    novo->next = atual->next;
    atual->next = novo;
}

int remover_valor(Node **head, int valor) {
    if(*head == NULL) return 0;
    
    Node *temp;
    
    if((*head)->data == valor) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return 1;
    }
    
    Node *atual = *head;
    while(atual->next != NULL && atual->next->data != valor) {
        atual = atual->next;
    }
    
    if(atual->next == NULL) return 0;
    
    temp = atual->next;
    atual->next = temp->next;
    free(temp);
    return 1;
}

int remover_indice(Node **head, int indice) {
    if(*head == NULL || indice < 0) return 0;
    
    Node *temp;
    
    if(indice == 0) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return 1;
    }
    
    Node *atual = *head;
    for(int i = 0; i < indice - 1 && atual->next != NULL; i++) {
        atual = atual->next;
    }
    
    if(atual->next == NULL) return 0;
    
    temp = atual->next;
    atual->next = temp->next;
    free(temp);
    return 1;
}

Node* buscar(Node *head, int valor) {
    Node *atual = head;
    while(atual != NULL) {
        if(atual->data == valor) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

int contar(Node *head) {
    int count = 0;
    Node *atual = head;
    while(atual != NULL) {
        count++;
        atual = atual->next;
    }
    return count;
}

void inverter(Node **head) {
    Node *anterior = NULL;
    Node *atual = *head;
    Node *proximo = NULL;
    
    while(atual != NULL) {
        proximo = atual->next;
        atual->next = anterior;
        anterior = atual;
        atual = proximo;
    }
    
    *head = anterior;
}

void remover_duplicatas(Node **head) {
    if(*head == NULL) return;
    
    Node *atual = *head;
    
    while(atual != NULL && atual->next != NULL) {
        Node *runner = atual;
        
        while(runner->next != NULL) {
            if(runner->next->data == atual->data) {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        
        atual = atual->next;
    }
}

void imprimir(Node *head) {
    Node *atual = head;
    printf("Lista: ");
    while(atual != NULL) {
        printf("%d -> ", atual->data);
        atual = atual->next;
    }
    printf("NULL\n");
}

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

int main() {
    Node *lista = NULL;
    
    printf("=== Testando inserções ===\n");
    inserir_inicio(&lista, 5);
    inserir_inicio(&lista, 10);
    inserir_fim(&lista, 3);
    inserir_ordenado(&lista, 7);
    imprimir(lista);
    
    printf("\n=== Informações ===\n");
    printf("Quantidade: %d\n", contar(lista));
    
    printf("\n=== Buscando valor 7 ===\n");
    Node *encontrado = buscar(lista, 7);
    if(encontrado) {
        printf("Encontrado: %d\n", encontrado->data);
    }
    
    printf("\n=== Invertendo lista ===\n");
    inverter(&lista);
    imprimir(lista);
    
    printf("\n=== Removendo duplicatas ===\n");
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 5);
    imprimir(lista);
    remover_duplicatas(&lista);
    imprimir(lista);
    
    liberar(&lista);
    
    return 0;
}
```

---

### Solução 3.2: Lista Duplamente Encadeada

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

DNode* criar_dnode(int valor) {
    DNode *novo = (DNode*) malloc(sizeof(DNode));
    if(novo == NULL) return NULL;
    
    novo->data = valor;
    novo->prev = NULL;
    novo->next = NULL;
    return novo;
}

void inserir_inicio(DNode **head, int valor) {
    DNode *novo = criar_dnode(valor);
    if(novo == NULL) return;
    
    if(*head != NULL) {
        (*head)->prev = novo;
    }
    
    novo->next = *head;
    *head = novo;
}

void inserir_fim(DNode **head, int valor) {
    DNode *novo = criar_dnode(valor);
    if(novo == NULL) return;
    
    if(*head == NULL) {
        *head = novo;
        return;
    }
    
    DNode *atual = *head;
    while(atual->next != NULL) {
        atual = atual->next;
    }
    
    atual->next = novo;
    novo->prev = atual;
}

void remover_valor(DNode **head, int valor) {
    if(*head == NULL) return;
    
    DNode *atual = *head;
    
    // Busca o nó
    while(atual != NULL && atual->data != valor) {
        atual = atual->next;
    }
    
    if(atual == NULL) return;  // não encontrou
    
    // Se é o primeiro nó
    if(atual->prev == NULL) {
        *head = atual->next;
        if(*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        atual->prev->next = atual->next;
        if(atual->next != NULL) {
            atual->next->prev = atual->prev;
        }
    }
    
    free(atual);
}

void imprimir_frente(DNode *head) {
    DNode *atual = head;
    printf("Frente: ");
    while(atual != NULL) {
        printf("%d ", atual->data);
        atual = atual->next;
    }
    printf("\n");
}

void imprimir_tras(DNode *head) {
    if(head == NULL) {
        printf("Trás: \n");
        return;
    }
    
    // Vai até o final
    DNode *atual = head;
    while(atual->next != NULL) {
        atual = atual->next;
    }
    
    // Imprime de trás para frente
    printf("Trás: ");
    while(atual != NULL) {
        printf("%d ", atual->data);
        atual = atual->prev;
    }
    printf("\n");
}

void liberar(DNode **head) {
    DNode *atual = *head;
    DNode *temp;
    
    while(atual != NULL) {
        temp = atual;
        atual = atual->next;
        free(temp);
    }
    
    *head = NULL;
}

int main() {
    DNode *lista = NULL;
    
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 20);
    inserir_fim(&lista, 30);
    inserir_inicio(&lista, 5);
    
    imprimir_frente(lista);
    imprimir_tras(lista);
    
    remover_valor(&lista, 20);
    imprimir_frente(lista);
    
    liberar(&lista);
    
    return 0;
}
```

---

### Solução 3.3: Pilha (Stack)

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

Pilha* criar_pilha() {
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    if(pilha == NULL) return NULL;
    
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

int esta_vazia(Pilha *pilha) {
    return pilha == NULL || pilha->topo == NULL;
}

void empilhar(Pilha *pilha, int valor) {
    if(pilha == NULL) return;
    
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL) return;
    
    novo->data = valor;
    novo->next = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

int desempilhar(Pilha *pilha, int *valor) {
    if(esta_vazia(pilha)) return 0;
    
    Node *temp = pilha->topo;
    *valor = temp->data;
    
    pilha->topo = pilha->topo->next;
    pilha->tamanho--;
    
    free(temp);
    return 1;
}

int topo(Pilha *pilha, int *valor) {
    if(esta_vazia(pilha)) return 0;
    
    *valor = pilha->topo->data;
    return 1;
}

int tamanho(Pilha *pilha) {
    return pilha == NULL ? 0 : pilha->tamanho;
}

void destruir_pilha(Pilha **pilha) {
    if(pilha == NULL || *pilha == NULL) return;
    
    int valor;
    while(!esta_vazia(*pilha)) {
        desempilhar(*pilha, &valor);
    }
    
    free(*pilha);
    *pilha = NULL;
}

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
    
    printf("\nDesempilhando:\n");
    while(!esta_vazia(pilha)) {
        desempilhar(pilha, &valor);
        printf("Desempilhou: %d\n", valor);
    }
    
    destruir_pilha(&pilha);
    
    return 0;
}
```

---

### Solução 3.4: Fila (Queue)

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

Fila* criar_fila() {
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    if(fila == NULL) return NULL;
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

int esta_vazia(Fila *fila) {
    return fila == NULL || fila->inicio == NULL;
}

void enfileirar(Fila *fila, int valor) {
    if(fila == NULL) return;
    
    Node *novo = (Node*) malloc(sizeof(Node));
    if(novo == NULL) return;
    
    novo->data = valor;
    novo->next = NULL;
    
    if(esta_vazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->next = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
}

int desenfileirar(Fila *fila, int *valor) {
    if(esta_vazia(fila)) return 0;
    
    Node *temp = fila->inicio;
    *valor = temp->data;
    
    fila->inicio = fila->inicio->next;
    
    if(fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    fila->tamanho--;
    free(temp);
    return 1;
}

int primeiro(Fila *fila, int *valor) {
    if(esta_vazia(fila)) return 0;
    
    *valor = fila->inicio->data;
    return 1;
}

int tamanho(Fila *fila) {
    return fila == NULL ? 0 : fila->tamanho;
}

void destruir_fila(Fila **fila) {
    if(fila == NULL || *fila == NULL) return;
    
    int valor;
    while(!esta_vazia(*fila)) {
        desenfileirar(*fila, &valor);
    }
    
    free(*fila);
    *fila = NULL;
}

int main() {
    Fila *fila = criar_fila();
    
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);
    
    printf("Tamanho: %d\n", tamanho(fila));
    
    int valor;
    if(primeiro(fila, &valor)) {
        printf("Primeiro: %d\n", valor);
    }
    
    printf("\nDesenfileirando:\n");
    while(!esta_vazia(fila)) {
        desenfileirar(fila, &valor);
        printf("Desenfileirou: %d\n", valor);
    }
    
    destruir_fila(&fila);
    
    return 0;
}
```

---

### Solução 3.5: Árvore Binária de Busca

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *esquerda;
    struct TreeNode *direita;
} TreeNode;

TreeNode* criar_node(int valor) {
    TreeNode *novo = (TreeNode*) malloc(sizeof(TreeNode));
    if(novo == NULL) return NULL;
    
    novo->data = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

TreeNode* inserir(TreeNode *raiz, int valor) {
    if(raiz == NULL) {
        return criar_node(valor);
    }
    
    if(valor < raiz->data) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if(valor > raiz->data) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    // Se valor == raiz->data, não insere (evita duplicatas)
    
    return raiz;
}

TreeNode* buscar(TreeNode *raiz, int valor) {
    if(raiz == NULL || raiz->data == valor) {
        return raiz;
    }
    
    if(valor < raiz->data) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

int altura(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    int alt_esq = altura(raiz->esquerda);
    int alt_dir = altura(raiz->direita);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

int contar_nos(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    return 1 + contar_nos(raiz->esquerda) + contar_nos(raiz->direita);
}

void imprimir_em_ordem(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    imprimir_em_ordem(raiz->esquerda);
    printf("%d ", raiz->data);
    imprimir_em_ordem(raiz->direita);
}

void imprimir_pre_ordem(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    printf("%d ", raiz->data);
    imprimir_pre_ordem(raiz->esquerda);
    imprimir_pre_ordem(raiz->direita);
}

void imprimir_pos_ordem(TreeNode *raiz) {
    if(raiz == NULL) return;
    
    imprimir_pos_ordem(raiz->esquerda);
    imprimir_pos_ordem(raiz->direita);
    printf("%d ", raiz->data);
}

void liberar_arvore(TreeNode **raiz) {
    if(*raiz == NULL) return;
    
    liberar_arvore(&(*raiz)->esquerda);
    liberar_arvore(&(*raiz)->direita);
    free(*raiz);
    *raiz = NULL;
}

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
    
    printf("Pré ordem: ");
    imprimir_pre_ordem(raiz);
    printf("\n");
    
    printf("Pós ordem: ");
    imprimir_pos_ordem(raiz);
    printf("\n");
    
    printf("\nAltura: %d\n", altura(raiz));
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

## Explicações Detalhadas

### Por que usar `**head` nas funções de lista?

```c
void inserir(Node **head, int valor) {
    // ...
}
```

**Resposta:** Porque precisamos modificar o próprio ponteiro `head`, não apenas o valor apontado.

- Com `Node *head`: poderíamos modificar os nós, mas não o ponteiro head original
- Com `Node **head`: podemos modificar o ponteiro head do caller

**Exemplo:**
```c
// ERRADO - não modifica head original
void inserir_errado(Node *head, int valor) {
    Node *novo = criar_node(valor);
    novo->next = head;
    head = novo;  // modifica apenas cópia local!
}

// CORRETO - modifica head original
void inserir_correto(Node **head, int valor) {
    Node *novo = criar_node(valor);
    novo->next = *head;
    *head = novo;  // modifica ponteiro original!
}
```

---

### Ordem de liberação de memória

**Regra:** Libere na ordem REVERSA da alocação.

```c
// Alocação:
int **matriz = malloc(...);        // 1. aloca array de ponteiros
matriz[i] = malloc(...);           // 2. aloca cada linha

// Liberação (ordem reversa):
for(int i = 0; i < linhas; i++) {
    free(matriz[i]);               // 2. libera linhas primeiro
}
free(matriz);                      // 1. libera array de ponteiros depois
```

**Por quê?** Se liberar o array principal primeiro, você perde as referências para as linhas!

---

### Recursão vs Iteração

Muitas operações em árvores são mais simples com recursão:

```c
// Recursivo (simples e elegante)
int altura_recursivo(TreeNode *raiz) {
    if(raiz == NULL) return 0;
    
    int alt_esq = altura_recursivo(raiz->esquerda);
    int alt_dir = altura_recursivo(raiz->direita);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Iterativo (mais complexo, requer pilha auxiliar)
int altura_iterativo(TreeNode *raiz) {
    // Implementação com pilha...
    // Muito mais código!
}
```

**Quando usar cada um:**
- **Recursão:** Mais simples, código limpo, árvores/listas
- **Iteração:** Melhor performance, evita stack overflow em estruturas grandes

---

## Dicas de Estudo

### ✅ Como praticar efetivamente

1. **Não copie e cole** - digite o código você mesmo
2. **Modifique os exemplos** - tente variações
3. **Adicione prints** - entenda o fluxo de execução
4. **Use debugger** - veja os ponteiros mudando
5. **Desenhe no papel** - visualize a memória

### 🐛 Debugando ponteiros

```c
// Adicione prints temporários
printf("DEBUG: p = %p, *p = %d\n", (void*)p, *p);

// Verifique antes de usar
if(p == NULL) {
    printf("ERRO: ponteiro nulo!\n");
    return;
}

// Use assert para condições críticas
#include <assert.h>
assert(p != NULL);
```

### 📊 Complexidade das Operações

| Estrutura | Busca | Inserção | Remoção |
|-----------|-------|----------|---------|
| Lista Encadeada | O(n) | O(1)* | O(1)* |
| Lista Ordenada | O(n) | O(n) | O(n) |
| Pilha | - | O(1) | O(1) |
| Fila | - | O(1) | O(1) |
| BST (balanceada) | O(log n) | O(log n) | O(log n) |
| BST (degenerada) | O(n) | O(n) | O(n) |

*Se você já tem o ponteiro para a posição

---

## Próximos Passos

Depois de dominar esses exercícios:

1. ✅ Implemente variações (lista circular, pilha com array)
2. ✅ Estude algoritmos de ordenação com ponteiros
3. ✅ Aprenda sobre hash tables
4. ✅ Explore grafos e suas representações
5. ✅ Pratique com problemas de plataformas online

---

## Links Relacionados

- [[Ponteiros em C - Guia Completo]]
- [[Exercícios de Ponteiros em C]]
- [[Estruturas de Dados Avançadas]]
- [[Algoritmos e Complexidade]]

---

## Tags

#c #solucoes #ponteiros #estruturas-de-dados #algoritmos #pratica

---

**Última atualização:** 2025-01-20

**Lembre-se:** A melhor forma de aprender é praticando! Tente resolver por conta própria antes de ver as soluções.
