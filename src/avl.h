#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int chave;
    struct No *esq;
    struct No *dir;
    int altura;
} No;

typedef struct
{
    No *raiz;
    int n;
} Arvore;

/* Criação e propriedades básicas */
Arvore *criaArvore(void);
int arvoreVazia(const Arvore *A);
int numeroNos(const Arvore *A);
int alturaArvore(const Arvore *A);

/* Operações fundamentais */
No *busca(const Arvore *A, int chave);
int insere(Arvore *A, int chave);
int removeChave(Arvore *A, int chave);

/* Auxiliares comuns */
No *minimo(No *r);
No *maximo(No *r);

/* Percursos */
void imprimeInOrdem(No *r);
void imprimePreOrdem(No *r);
void imprimePosOrdem(No *r);

/* Destruição */
void destroiArvore(Arvore *A);

/* Funções implementadas */

/**
 * Imprime a árvore na estrutura hierárquica, com identação proporcional ao nível
 */
void imprimeEstruturada(No* r, int nivel);

/**
 * Retorna quantos nós existem em determinado nível da árvore
 */
int contaNivel(No *r, int nivel);



#endif /* AVL_H */
