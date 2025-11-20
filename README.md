# 📚 Estudos de Ponteiros em C

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

Material completo sobre ponteiros e estruturas de dados em C, desenvolvido como **projeto pessoal de estudos**.

---

## 📖 Sobre o Projeto

Este repositório contém todo o material de estudo sobre ponteiros em C, desde conceitos básicos até estruturas de dados avançadas. O objetivo é consolidar o aprendizado através de:

- 📘 **Guias teóricos completos** com explicações detalhadas
- 🎓 **Aulas práticas** com código comentado
- 📝 **15 exercícios** progressivos (básico → intermediário → avançado)
- 🚀 **4 projetos completos** para aplicação prática
- ✅ **Soluções comentadas** para todos os exercícios

---

## 📂 Estrutura do Repositório

```
estudos-ponteiros-c/
│
├── 📘 teoria/
│   ├── ponteiros-em-c-guia-completo.md      # Teoria completa
│   ├── exercicios-ponteiros-c.md            # 15 exercícios + 4 projetos
│   └── solucoes-exercicios-ponteiros-c.md   # Soluções comentadas
│
├── 🎓 aulas/
│   ├── aula01-introducao-ponteiros.c        # O que são ponteiros
│   ├── aula02-ponteiros-funcoes.c           # Passagem por referência
│   ├── aula03-aritmetica-ponteiros.c        # Arrays e aritmética
│   └── aula04-alocacao-dinamica.c           # malloc, calloc, free
│
├── 📝 exercicios/
│   ├── nivel1/                               # Exercícios básicos
│   ├── nivel2/                               # Exercícios intermediários
│   └── nivel3/                               # Exercícios avançados
│
├── 🚀 projetos/
│   └── (projetos completos aqui)
│
├── 🧪 testes/
│   └── (área de testes e experimentos)
│
└── 🔧 utils/
    └── (funções auxiliares reutilizáveis)
```

---

## 📚 Conteúdo Abordado

### Fundamentos
- ✅ Ponteiros básicos (`&` e `*`)
- ✅ Declaração e inicialização
- ✅ Ponteiros e variáveis
- ✅ Ponteiros nulos (NULL)

### Intermediário
- ✅ Aritmética de ponteiros
- ✅ Ponteiros e arrays
- ✅ Ponteiros e funções (passagem por referência)
- ✅ Retornar múltiplos valores

### Avançado
- ✅ Alocação dinâmica (`malloc`, `calloc`, `realloc`, `free`)
- ✅ Ponteiros para ponteiros
- ✅ Ponteiros void e const
- ✅ Structs com ponteiros
- ✅ Ponteiros para funções (callbacks)

### Estruturas de Dados
- ✅ Lista Encadeada (Linked List)
- ✅ Lista Duplamente Encadeada
- ✅ Pilha (Stack)
- ✅ Fila (Queue)
- ✅ Árvore Binária de Busca (BST)

---

## 🚀 Como Usar

### 1️⃣ Clone o Repositório

```bash
git clone https://github.com/protonguilherme/estudos-ponteiros-c.git
cd estudos-ponteiros-c
```

### 2️⃣ Compile e Execute as Aulas

```bash
cd aulas

# Compilar
gcc aula01-introducao-ponteiros.c -o aula01

# Executar
./aula01
```

### 3️⃣ Compile com Warnings (Recomendado)

```bash
gcc -Wall -Wextra -g aula01-introducao-ponteiros.c -o aula01
```

**Flags explicadas:**
- `-Wall` → Ativa todos os warnings
- `-Wextra` → Warnings extras
- `-g` → Adiciona símbolos de debug

### 4️⃣ Debug com LLDB

```bash
gcc -g arquivo.c -o programa
lldb programa

# Comandos úteis:
# breakpoint set -n main
# run
# next
# print variavel
# quit
```

---

## 📝 Exercícios

### Nível 1 - Básico
- 1.1: Primeiros Passos com Ponteiros
- 1.2: Troca de Valores
- 1.3: Soma de Array
- 1.4: Maior e Menor Valor
- 1.5: Inverter String

### Nível 2 - Intermediário
- 2.1: Alocação Dinâmica de Array
- 2.2: Matriz Dinâmica
- 2.3: Remover Duplicatas
- 2.4: Struct com Ponteiros
- 2.5: Função Callback

### Nível 3 - Avançado
- 3.1: Lista Encadeada Completa
- 3.2: Lista Duplamente Encadeada
- 3.3: Pilha (Stack)
- 3.4: Fila (Queue)
- 3.5: Árvore Binária de Busca

### Projetos Completos
1. Sistema de Gerenciamento de Estudantes
2. Agenda de Contatos
3. Calculadora de Expressões
4. Editor de Texto Simples

---

## 🛠️ Ferramentas Utilizadas

| Ferramenta | Descrição |
|------------|-----------|
| **GCC/Clang** | Compilador C |
| **VS Code** | Editor de código |
| **LLDB** | Debugger |
| **Git** | Controle de versão |
| **Obsidian** | Organização de notas |

---

## 📊 Progresso de Estudos

- [x] Ambiente de desenvolvimento configurado
- [x] Aulas 01-04 completas
- [x] Guia teórico completo
- [x] Exercícios básicos (1.1 - 1.2)
- [ ] Exercícios básicos (1.3 - 1.5)
- [ ] Exercícios intermediários (2.1 - 2.5)
- [ ] Exercícios avançados (3.1 - 3.5)
- [ ] Projetos completos

---

## 💡 Dicas de Estudo

### 📌 Sempre compile com warnings
```bash
gcc -Wall -Wextra arquivo.c -o programa
```

### 🐛 Use ferramentas de debug
```bash
# Valgrind para detectar memory leaks (Linux)
valgrind --leak-check=full ./programa

# AddressSanitizer (macOS/Linux)
gcc -fsanitize=address -g arquivo.c -o programa
```

### 📖 Siga a sequência
1. Leia a teoria
2. Estude o código da aula
3. Tente o exercício sozinho
4. Compare com a solução
5. Pratique variações

### ✍️ Pratique muito!
Ponteiros só fazem sentido com muita prática. Digite os códigos (não copie/cole), experimente, quebre, conserte!

---

## 🎯 Conceitos-Chave

### Operadores Essenciais
```c
int x = 10;
int *p = &x;    // & = pega endereço
int valor = *p;  // * = dereferencia (acessa valor)
```

### Regras de Ouro
1. ✅ **SEMPRE** inicialize ponteiros (`NULL` ou endereço válido)
2. ✅ **SEMPRE** verifique se `malloc` retornou `NULL`
3. ✅ **SEMPRE** use `free()` no que você alocou
4. ✅ **NUNCA** use ponteiro após `free()`
5. ✅ Faça `ptr = NULL` após `free()`

### Erros Comuns
- ❌ Memory leak (alocar sem liberar)
- ❌ Dangling pointer (usar após free)
- ❌ Double free (liberar duas vezes)
- ❌ Buffer overflow (escrever fora dos limites)
- ❌ Ponteiro não inicializado

---

## 🤝 Contribuindo

Este é um repositório de estudos pessoais, mas sugestões são bem-vindas!

1. Fork o projeto
2. Crie uma branch (`git checkout -b feature/melhoria`)
3. Commit suas mudanças (`git commit -m 'Adiciona recurso X'`)
4. Push para a branch (`git push origin feature/melhoria`)
5. Abra um Pull Request

---

## 📚 Recursos Adicionais

### Livros Recomendados
- **"The C Programming Language"** - Kernighan & Ritchie
- **"C Programming: A Modern Approach"** - K.N. King
- **"Pointers on C"** - Kenneth Reek

### Links Úteis
- [C Reference](https://en.cppreference.com/w/c)
- [Learn C](https://www.learn-c.org/)
- [GeeksforGeeks - C Programming](https://www.geeksforgeeks.org/c-programming-language/)

---

## 👨‍💻 Autor

**Guilherme (Proton)**

- 🎓 Estudante de Programação
- 💻 Apaixonado por desenvolvimento e estruturas de dados
- 🚀 Sempre aprendendo e evoluindo
- 📧 GitHub: [@protonguilherme](https://github.com/protonguilherme)

---

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

```
MIT License

Copyright (c) 2025 Guilherme (Proton)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

## 📞 Contato

Dúvidas ou sugestões? Abra uma [issue](https://github.com/protonguilherme/estudos-ponteiros-c/issues)!

---

<div align="center">

**⭐ Se este material te ajudou, deixe uma estrela no repositório! ⭐**

Made with ❤️ and ☕ by Proton

</div>
