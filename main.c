#include "avl.h"
#include <stdio.h>
#include <ctype.h>

static void mostraMinMax(No *r)
{
    No *a = minimo(r);
    No *b = maximo(r);
    printf("Min: ");
    a ? printf("%d", a->chave) : printf("NA");
    printf("  |  Max: ");
    b ? printf("%d", b->chave) : printf("NA");
    puts("");
}

int main(void)
{
    Arvore *A = criaArvore();
    int op, x;
    do
    {
        printf("\n=== MENU AVL ===\n");
        printf("1 - Inserir\n2 - Remover\n3 - Buscar\n4 - In-Ordem\n5 - Pre-Ordem\n6 - Pos-Ordem\n7 - Min e Max\n8 - Altura e Tamanho\n9 - Destruir e Recriar\n0 - Sair\nOpcao: ");
        if (scanf("%d", &op) != 1)
        {
            puts("Entrada invalida.");
            break;
        }
        switch (op)
        {
        case 1:
            printf("Valor: ");
            if (scanf("%d", &x) != 1)
            {
                puts("Entrada invalida.");
                break;
            }
            puts(insere(A, x) ? "Inserido!" : "Duplicado: nao inserido.");
            break;
        case 2:
            printf("Valor: ");
            if (scanf("%d", &x) != 1)
            {
                puts("Entrada invalida.");
                break;
            }
            puts(removeChave(A, x) ? "Removido!" : "Nao encontrado.");
            break;
        case 3:
            printf("Valor: ");
            if (scanf("%d", &x) != 1)
            {
                puts("Entrada invalida.");
                break;
            }
            puts(busca(A, x) ? "Encontrado!" : "Nao encontrado.");
            break;
        case 4:
            printf("In-Ordem: ");
            imprimeInOrdem(A->raiz);
            puts("");
            break;
        case 5:
            printf("Pre-Ordem: ");
            imprimePreOrdem(A->raiz);
            puts("");
            break;
        case 6:
            printf("Pos-Ordem: ");
            imprimePosOrdem(A->raiz);
            puts("");
            break;
        case 7:
            mostraMinMax(A->raiz);
            break;
        case 8:
            printf("Altura: %d  Tamanho: %d\n", alturaArvore(A), numeroNos(A));
            break;
        case 9:
            destroiArvore(A);
            puts("Arvore destruida.");
            A = criaArvore();
            puts("Arvore recriada (vazia).");
            break;
        case 0:
            break;
        default:
            puts("Opcao invalida.");
        }
    } while (op != 0);
    destroiArvore(A);
    return 0;
}
