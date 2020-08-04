#include <stdio.h>
#include <stdlib.h>

/*essa seção foi copiada do material disponibilizado pela professora*/
typedef struct _arvore {
   char info;
   struct _arvore *esq;
   struct _arvore *dir;
} Arvore;

Arvore* cria_arv_vazia ();

void destroi_arv (Arvore *arv);

Arvore* constroi_arv (char elem, Arvore *esq, Arvore *dir);

/*a partir daqui conteúdo original*/

Arvore* constroi_folha(char elem);

int arvore_vazia(Arvore* A);