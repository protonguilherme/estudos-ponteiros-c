/*
 * AULA 05 - Structs e Ponteiros
 * 
 * Objetivos:
 * - Entender structs (estruturas)
 * - Usar ponteiros para structs
 * - Alocar structs dinamicamente
 * - Operador -> (seta)
 * - Arrays de structs
 * - Structs aninhadas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// DEFINIÇÃO DE STRUCTS
// ============================================

// Struct simples
struct Pessoa {
    char nome[50];
    int idade;
    float altura;
};

// Typedef facilita o uso
typedef struct {
    char titulo[100];
    char autor[50];
    int ano;
    float preco;
} Livro;

// Struct com ponteiros internos
typedef struct {
    char *nome;
    int matricula;
    float *notas;
    int num_notas;
} Aluno;

// Struct autoreferenciada (para listas)
typedef struct Node {
    int valor;
    struct Node *proximo;
} Node;

// Struct aninhada
typedef struct {
    char rua[100];
    int numero;
    char cidade[50];
} Endereco;

typedef struct {
    char nome[50];
    int idade;
    Endereco endereco;  // struct dentro de struct
} Cliente;

// ============================================
// FUNÇÕES AUXILIARES
// ============================================

// Imprime pessoa (passagem por ponteiro - eficiente)
void imprimir_pessoa(struct Pessoa *p) {
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d anos\n", p->idade);
    printf("Altura: %.2f m\n", p->altura);
}

// Modifica através de ponteiro
void fazer_aniversario(struct Pessoa *p) {
    p->idade++;
    printf("%s fez aniversário! Agora tem %d anos.\n", p->nome, p->idade);
}

// Cria aluno dinâmico
Aluno* criar_aluno(const char *nome, int matricula, int num_notas) {
    Aluno *aluno = (Aluno*) malloc(sizeof(Aluno));
    if(aluno == NULL) return NULL;
    
    aluno->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
    if(aluno->nome == NULL) {
        free(aluno);
        return NULL;
    }
    strcpy(aluno->nome, nome);
    
    aluno->matricula = matricula;
    aluno->notas = (float*) malloc(num_notas * sizeof(float));
    if(aluno->notas == NULL) {
        free(aluno->nome);
        free(aluno);
        return NULL;
    }
    aluno->num_notas = num_notas;
    
    for(int i = 0; i < num_notas; i++) {
        aluno->notas[i] = 0.0;
    }
    
    return aluno;
}

// Calcula média do aluno
float calcular_media(Aluno *aluno) {
    if(aluno == NULL || aluno->num_notas == 0) return 0.0;
    
    float soma = 0.0;
    for(int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    return soma / aluno->num_notas;
}

// Libera aluno
void destruir_aluno(Aluno **aluno) {
    if(aluno == NULL || *aluno == NULL) return;
    
    free((*aluno)->nome);
    free((*aluno)->notas);
    free(*aluno);
    *aluno = NULL;
}

// Imprime livro
void imprimir_livro(Livro *livro) {
    printf("\n--- LIVRO ---\n");
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);
    printf("Preço: R$ %.2f\n", livro->preco);
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("=== AULA 05: STRUCTS E PONTEIROS ===\n\n");
    
    // ============================================
    // PARTE 1: STRUCT BÁSICA
    // ============================================
    printf("--- PARTE 1: Struct Básica ---\n");
    
    struct Pessoa pessoa1;
    strcpy(pessoa1.nome, "João Silva");
    pessoa1.idade = 25;
    pessoa1.altura = 1.75;
    
    printf("Acesso direto com . (ponto):\n");
    printf("Nome: %s, Idade: %d\n\n", pessoa1.nome, pessoa1.idade);
    
    // ============================================
    // PARTE 2: PONTEIRO PARA STRUCT
    // ============================================
    printf("--- PARTE 2: Ponteiro para Struct ---\n");
    
    struct Pessoa *ptr = &pessoa1;
    
    // Duas formas de acessar:
    printf("Forma 1 (com *): %s\n", (*ptr).nome);
    printf("Forma 2 (com ->): %s (MAIS USADO)\n\n", ptr->nome);
    
    // ============================================
    // PARTE 3: MODIFICANDO VIA PONTEIRO
    // ============================================
    printf("--- PARTE 3: Modificando via Ponteiro ---\n");
    
    printf("ANTES:\n");
    imprimir_pessoa(ptr);
    
    printf("\n");
    fazer_aniversario(ptr);
    
    printf("\nDEPOIS:\n");
    imprimir_pessoa(ptr);
    printf("\n");
    
    // ============================================
    // PARTE 4: TYPEDEF (facilita uso)
    // ============================================
    printf("--- PARTE 4: Typedef ---\n");
    
    Livro livro1;  // sem typedef seria: struct Livro livro1;
    strcpy(livro1.titulo, "C Programming");
    strcpy(livro1.autor, "Kernighan & Ritchie");
    livro1.ano = 1978;
    livro1.preco = 59.90;
    
    imprimir_livro(&livro1);
    printf("\n");
    
    // ============================================
    // PARTE 5: ARRAY DE STRUCTS
    // ============================================
    printf("--- PARTE 5: Array de Structs ---\n");
    
    Livro biblioteca[3] = {
        {"The C Programming Language", "Kernighan & Ritchie", 1978, 59.90},
        {"Clean Code", "Robert Martin", 2008, 79.90},
        {"Algorithms", "Cormen et al", 1990, 129.90}
    };
    
    printf("BIBLIOTECA (%zu livros):\n", sizeof(biblioteca)/sizeof(Livro));
    for(int i = 0; i < 3; i++) {
        printf("%d. %s - R$ %.2f\n", 
               i+1, biblioteca[i].titulo, biblioteca[i].preco);
    }
    printf("\n");
    
    // ============================================
    // PARTE 6: STRUCT DINÂMICA
    // ============================================
    printf("--- PARTE 6: Struct Dinâmica ---\n");
    
    Livro *livro_dinamico = (Livro*) malloc(sizeof(Livro));
    
    if(livro_dinamico != NULL) {
        strcpy(livro_dinamico->titulo, "SICP");
        strcpy(livro_dinamico->autor, "Abelson & Sussman");
        livro_dinamico->ano = 1985;
        livro_dinamico->preco = 89.90;
        
        imprimir_livro(livro_dinamico);
        
        free(livro_dinamico);
        livro_dinamico = NULL;
    }
    printf("\n");
    
    // ============================================
    // PARTE 7: STRUCT COM PONTEIROS INTERNOS
    // ============================================
    printf("--- PARTE 7: Struct com Ponteiros Internos ---\n");
    
    Aluno *aluno1 = criar_aluno("Ana Silva", 12345, 4);
    
    if(aluno1 != NULL) {
        aluno1->notas[0] = 8.5;
        aluno1->notas[1] = 9.0;
        aluno1->notas[2] = 7.5;
        aluno1->notas[3] = 8.0;
        
        printf("Aluno: %s (Mat: %d)\n", aluno1->nome, aluno1->matricula);
        printf("Notas: ");
        for(int i = 0; i < aluno1->num_notas; i++) {
            printf("%.1f ", aluno1->notas[i]);
        }
        printf("\nMédia: %.2f\n", calcular_media(aluno1));
        
        destruir_aluno(&aluno1);
    }
    printf("\n");
    
    // ============================================
    // PARTE 8: STRUCT ANINHADA
    // ============================================
    printf("--- PARTE 8: Struct Aninhada ---\n");
    
    Cliente cliente1;
    strcpy(cliente1.nome, "Carlos Souza");
    cliente1.idade = 35;
    strcpy(cliente1.endereco.rua, "Av. Paulista");
    cliente1.endereco.numero = 1000;
    strcpy(cliente1.endereco.cidade, "São Paulo");
    
    printf("Cliente: %s (%d anos)\n", cliente1.nome, cliente1.idade);
    printf("Endereço: %s, %d - %s\n\n", 
           cliente1.endereco.rua, 
           cliente1.endereco.numero,
           cliente1.endereco.cidade);
    
    // ============================================
    // PARTE 9: STRUCT AUTOREFERENCIADA
    // ============================================
    printf("--- PARTE 9: Struct Autoreferenciada (Preview Lista) ---\n");
    
    Node *no1 = (Node*) malloc(sizeof(Node));
    Node *no2 = (Node*) malloc(sizeof(Node));
    Node *no3 = (Node*) malloc(sizeof(Node));
    
    if(no1 && no2 && no3) {
        no1->valor = 10;
        no1->proximo = no2;
        
        no2->valor = 20;
        no2->proximo = no3;
        
        no3->valor = 30;
        no3->proximo = NULL;
        
        printf("Lista encadeada (prévia): ");
        Node *atual = no1;
        while(atual != NULL) {
            printf("%d -> ", atual->valor);
            atual = atual->proximo;
        }
        printf("NULL\n");
        
        free(no1);
        free(no2);
        free(no3);
    }
    printf("\n");
    
    // ============================================
    // EXERCÍCIOS
    // ============================================
    printf("--- EXERCÍCIOS ---\n");
    printf("1. Crie struct Retângulo com área e perímetro\n");
    printf("2. Crie struct Contato com nome, telefone, email\n");
    printf("3. Crie array dinâmico de Contatos\n");
    printf("4. Crie struct Data e calcule diferença entre datas\n\n");
    
    printf("=== FIM DA AULA 05 ===\n");
    
    return 0;
}

/*
 * RESUMO DA AULA:
 * 
 * 1. Struct agrupa dados relacionados
 * 2. Acesso direto: struct.membro
 * 3. Acesso via ponteiro: ptr->membro (equivalente a (*ptr).membro)
 * 4. typedef simplifica (não precisa "struct")
 * 5. Structs podem conter ponteiros
 * 6. Sempre libere memória alocada dentro de structs
 * 7. Struct autoreferenciada permite listas/árvores
 * 
 * DIFERENÇAS:
 * - . (ponto) → struct normal
 * - -> (seta) → ponteiro para struct
 * - Passar por valor = copia tudo (ineficiente)
 * - Passar ponteiro = eficiente
 * 
 * PRÓXIMA AULA: Lista Encadeada Completa
 */
