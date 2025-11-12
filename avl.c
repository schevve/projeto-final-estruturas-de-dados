#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

static int alt(No *r) { return r ? r->altura : -1; }
static int max2(int a, int b) { return (a > b ? a : b); }
static void atualizaAltura(No *r)
{
    if (r)
        r->altura = 1 + max2(alt(r->esq), alt(r->dir));
}
static int fb(No *r) { return r ? (alt(r->esq) - alt(r->dir)) : 0; }

static No *rotacaoLL(No *r)
{
    No *B = r->esq;
    r->esq = B->dir;
    B->dir = r;
    atualizaAltura(r);
    atualizaAltura(B);
    return B;
}

static No *rotacaoRR(No *r)
{
    No *B = r->dir;
    r->dir = B->esq;
    B->esq = r;
    atualizaAltura(r);
    atualizaAltura(B);
    return B;
}

static No *rotacaoLR(No *r)
{
    r->esq = rotacaoRR(r->esq);
    return rotacaoLL(r);
}
static No *rotacaoRL(No *r)
{
    r->dir = rotacaoLL(r->dir);
    return rotacaoRR(r);
}

static No *novoNo(int x)
{
    No *p = (No *)malloc(sizeof(No));
    if (!p)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    p->chave = x;
    p->esq = p->dir = NULL;
    p->altura = 0;
    return p;
}

Arvore *criaArvore(void)
{
    Arvore *A = (Arvore *)malloc(sizeof(Arvore));
    if (!A)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    A->raiz = NULL;
    A->n = 0;
    return A;
}

int arvoreVazia(const Arvore *A) { return (!A || A->n == 0); }
int numeroNos(const Arvore *A) { return A ? A->n : 0; }

static int alturaRec(No *r)
{
    if (!r)
        return -1;
    int he = alturaRec(r->esq), hd = alturaRec(r->dir);
    return 1 + (he > hd ? he : hd);
}

int alturaArvore(const Arvore *A) { return A ? alturaRec(A->raiz) : -1; }
static void liberaRec(No *r)
{
    if (!r)
        return;
    liberaRec(r->esq);
    liberaRec(r->dir);
    free(r);
}
void destroiArvore(Arvore *A)
{
    if (!A)
        return;
    liberaRec(A->raiz);
    free(A);
}

No *busca(const Arvore *A, int x)
{
    No *p = (A ? A->raiz : NULL);
    while (p)
    {
        if (x == p->chave)
            return p;
        p = (x < p->chave) ? p->esq : p->dir;
    }
    return NULL;
}

No *minimo(No *r)
{
    if (!r)
        return NULL;
    while (r->esq)
        r = r->esq;
    return r;
}
No *maximo(No *r)
{
    if (!r)
        return NULL;
    while (r->dir)
        r = r->dir;
    return r;
}

static No *insereRec(No *r, int x, int *cresceu)
{
    if (!r)
    {
        *cresceu = 1;
        return novoNo(x);
    }
    if (x < r->chave)
        r->esq = insereRec(r->esq, x, cresceu);
    else if (x > r->chave)
        r->dir = insereRec(r->dir, x, cresceu);
    else
    {
        *cresceu = 0;
        return r;
    }
    atualizaAltura(r);
    int f = fb(r);
    if (f > 1 && x < r->esq->chave)
        return rotacaoLL(r);
    if (f < -1 && x > r->dir->chave)
        return rotacaoRR(r);
    if (f > 1 && x > r->esq->chave)
        return rotacaoLR(r);
    if (f < -1 && x < r->dir->chave)
        return rotacaoRL(r);
    return r;
}

int insere(Arvore *A, int x)
{
    if (!A)
        return 0;
    int cresceu = 0;
    A->raiz = insereRec(A->raiz, x, &cresceu);
    if (cresceu)
        A->n++;
    return cresceu;
}

static No *removeRec(No *r, int x, int *diminuiu)
{
    if (!r)
        return NULL;
    if (x < r->chave)
        r->esq = removeRec(r->esq, x, diminuiu);
    else if (x > r->chave)
        r->dir = removeRec(r->dir, x, diminuiu);
    else
    {
        if (!r->esq || !r->dir)
        {
            No *aux = r->esq ? r->esq : r->dir;
            free(r);
            *diminuiu = 1;
            return aux;
        }
        else
        {
            No *s = minimo(r->dir);
            r->chave = s->chave;
            r->dir = removeRec(r->dir, s->chave, diminuiu);
        }
    }
    if (!r)
        return NULL;
    atualizaAltura(r);
    int f = fb(r);
    if (f > 1 && fb(r->esq) >= 0)
        return rotacaoLL(r);
    if (f > 1 && fb(r->esq) < 0)
        return rotacaoLR(r);
    if (f < -1 && fb(r->dir) <= 0)
        return rotacaoRR(r);
    if (f < -1 && fb(r->dir) > 0)
        return rotacaoRL(r);
    return r;
}

int removeChave(Arvore *A, int x)
{
    if (!A || !A->raiz)
        return 0;
    int diminuiu = 0;
    A->raiz = removeRec(A->raiz, x, &diminuiu);
    if (diminuiu)
        A->n--;
    return diminuiu;
}

void imprimeInOrdem(No *r)
{
    if (!r)
        return;
    imprimeInOrdem(r->esq);
    printf("%d ", r->chave);
    imprimeInOrdem(r->dir);
}
void imprimePreOrdem(No *r)
{
    if (!r)
        return;
    printf("%d ", r->chave);
    imprimePreOrdem(r->esq);
    imprimePreOrdem(r->dir);
}
void imprimePosOrdem(No *r)
{
    if (!r)
        return;
    imprimePosOrdem(r->esq);
    imprimePosOrdem(r->dir);
    printf("%d ", r->chave);
}
