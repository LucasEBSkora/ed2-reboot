#include "exercicios_aula1.h"

#include <stdio.h>

//exercício 1

void imprime_pre_ordem(Arvore *a) {
  if (!arvore_vazia(a)) {
    printf("%c\n", a->info);
    imprime_pre_ordem(a->esq);
    imprime_pre_ordem(a->dir);
  }
}

void imprime_in_ordem(Arvore *a) {
  if (!arvore_vazia(a)) {
    imprime_in_ordem(a->esq);
    printf("%c\n", a->info);
    imprime_in_ordem(a->dir);
  }
}

void imprime_pos_ordem(Arvore *a) {
  if (!arvore_vazia(a)) {
    imprime_pos_ordem(a->esq);
    imprime_pos_ordem(a->dir);
    printf("%c\n", a->info);
  }
}

//exercicio 2

//pre-ordem

void imprime_arvore_marcadores(Arvore* arv) {
  printf("<");
  if (!arvore_vazia(arv)) {
    printf("%c",arv->info);
    imprime_arvore_marcadores(arv->esq);
    imprime_arvore_marcadores(arv->dir);
  }
  printf(">");
}

//exercício 3

int pertence_arv(Arvore *a, char c) {
  if (arvore_vazia(a)) return 0;
  else return a->info == c || pertence_arv(a->esq, c) || pertence_arv(a->dir, c);
}

//exercício 4

int conta_nos(Arvore* a) {
  if (arvore_vazia(a)) return 0;
  else return conta_nos(a->esq) + conta_nos(a->dir) + 1;
}

//exercício 5
int calcula_altura_arvore(Arvore* a) {
  if (arvore_vazia(a)) return -1;
  int altura_esq = calcula_altura_arvore(a->esq);
  int altura_dir = calcula_altura_arvore(a->dir);
  return 1 + ((altura_esq > altura_dir) ? altura_esq : altura_dir);
}

//exercicio 6
int conta_nos_folha(Arvore* a) {
  if (arvore_vazia(a)) return 0;
  if (arvore_vazia(a->esq) && arvore_vazia(a->dir)) return 1;
  else return conta_nos_folha(a->esq) + conta_nos_folha(a->dir);
}

int main()
{

  Arvore *a = constroi_arv(
    'a',
    constroi_arv('b', cria_arv_vazia(), constroi_folha('d')),
    constroi_arv('c', constroi_folha('e'), constroi_folha('f'))
  );

  imprime_pre_ordem(a);
  printf("\n");
  
  imprime_in_ordem(a);
  printf("\n");
  
  imprime_pos_ordem(a);
  printf("\n");
  
  imprime_arvore_marcadores(a);
  printf("\n");
  
  char c;
  for (c = 'a'; c < 'h'; ++c) 
    printf("%c E a = %s\n", c, (pertence_arv(a, c) ? "verdadeiro" : "falso"));
  
  printf("a arvore tem %d nos,", conta_nos(a));
  printf("dos quais %d sao folhas", conta_nos_folha(a));
  printf(", e sua altura e %d\n", calcula_altura_arvore(a));
  
  return 0;
}

/*Copiado do material disponibilizado pela professora*/
Arvore *cria_arv_vazia()
{
  return NULL;
}

void destroi_arv(Arvore *arv)
{
  if (arv != NULL)
  {
    destroi_arv(arv->esq);
    destroi_arv(arv->dir);
    free(arv);
  }
}

Arvore *constroi_arv(char elem, Arvore *esq, Arvore *dir)
{
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->info = elem;
  arv->esq = esq;
  arv->dir = dir;
  return arv;
}
/*Aqui novamente conteúdo original*/

Arvore *constroi_folha(char elem) {
  return constroi_arv(elem, NULL, NULL);
}

int arvore_vazia(Arvore* A) {
  return A == NULL;
}