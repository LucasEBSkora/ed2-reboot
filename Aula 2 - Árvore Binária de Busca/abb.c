#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {  
   int info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;

Arvore* cria_arvore_vazia (void) {
   return NULL;
}

void arvore_libera (Arvore* a) {
   if (a != NULL) {
      arvore_libera (a->esq);
      arvore_libera (a->dir);
      free(a);
   }
}


Arvore* inserir (Arvore *a, int v) {
   /* Completar */
   return a;
}

Arvore* remover (Arvore *a, int v) {
   /* Completar */
   
   return a;
}



int buscar (Arvore *a, int v) {
   /* Completar */
  
  return 1; 
    
}


void pre_order (Arvore* a) {
   if (a != NULL) {
      printf("%d ", a->info);
      pre_order (a->esq);
      pre_order (a->dir);
   } 
}

int main () {

   int i;

   Arvore *a = cria_arvore_vazia ();

   a = inserir (a, 50);
   a = inserir (a, 30);
   a = inserir (a, 90);
   a = inserir (a, 20);
   a = inserir (a, 40);
   a = inserir (a, 95);
   a = inserir (a, 10);
   a = inserir (a, 35);
   a = inserir (a, 37);

   /*a = remover (a, 20);
    ...
   */

   printf("\n");
   pre_order (a);	
   printf("\n");

   return 0;
}


