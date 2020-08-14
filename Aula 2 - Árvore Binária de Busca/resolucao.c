#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

typedef struct arvore
{
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

Arvore *cria_arvore_vazia(void)
{
  return NULL;
}

void arvore_libera(Arvore *a)
{
  if (a != NULL)
  {
    arvore_libera(a->esq);
    arvore_libera(a->dir);
    free(a);
  }
}

void in_order(Arvore *a)
{
  if (a != NULL)
  {
    in_order(a->esq);
    printf("%d ", a->info);
    in_order(a->dir);
  }
}

//exercicio 1

Arvore *inserir(Arvore *a, int v)
{
  //começa nova árvore
  if (a == NULL)
  {
    a = (Arvore *)malloc(sizeof(Arvore));
    a->info = v;
    a->esq = NULL;
    a->dir = NULL;
  }
  else if (v < a->info)
  { //insere de verdade
    a->esq = inserir(a->esq, v);
  }
  else if (a->info < v)
  {
    a->dir = inserir(a->dir, v);
  } //caso a->info == v => a chave já existe
  return a;
}

Arvore *remover(Arvore *a, int v)
{
  if (a != NULL)
  {
    if (v < a->info)
      a->esq = remover(a->esq, v); //procurar na esquerda
    else if (a->info < v)
      a->dir = remover(a->dir, v); //procurar na direita
    else
    { //achou
      if (a->esq == NULL && a->dir == NULL)
      { //é folha = só remover
        free(a);
        a = NULL;
      }
      else if (a->esq == NULL)
      { //achou e só tem uma subárvore: sobe ela pra posição da atual
        Arvore *tmp = a->dir;
        free(a);
        a = tmp;
      }
      else if (a->dir == NULL)
      {
        Arvore *tmp = a->esq;
        free(a);
        a = tmp;
      }
      else
      { //tem ambas as subárvores => mais complicado. Pegamos o maior elemento na subárvore da esquerda (funcionaria com o menor da direita tbm) e o na posição desse.
        Arvore *tmp = a->esq;

        while (tmp->dir != NULL)
          tmp = tmp->dir;

        a->info = tmp->info;

        remover(a->esq, tmp->info);
      }
    }
  }

  return a;
}

int buscar(Arvore *a, int v)
{
  if (a != NULL)
  {
    if (a->info == v)
      return 1;
    if (a->info < v)
      return buscar(a->dir, v);
    if (a->info > v)
      return buscar(a->esq, v);
  }
  return 0;
}

//exercicio 2

int min(Arvore *a)
{
  //por segurança
  if (a == NULL)
    return INT_MAX;
  while (a->esq != NULL)
    a = a->esq;

  return a->info;
}

int max(Arvore *a)
{
  //por segurança
  if (a == NULL)
    return INT_MIN;
  while (a->dir != NULL)
    a = a->dir;

  return a->info;
}

//exercicio 3

Arvore *gera_arvore_ordenada(int n)
{
  Arvore *a = cria_arvore_vazia();
  int i;
  for (int i = 0; i < n; ++i)
    a = inserir(a, i);

  return a;
}

//exercicio 4

Arvore *gera_arvore_aleatoria(int n)
{
  srand(time(NULL));
  Arvore *a = cria_arvore_vazia();
  int i;
  for (int i = 0; i < n; ++i)
    a = inserir(a, rand());

  return a;
}

//exercicio 5

void imprime_decrescente(Arvore *a)
{
  if (a != NULL)
  {
    imprime_decrescente(a->dir);
    printf("%d ", a->info);
    imprime_decrescente(a->esq);
  }
}

//exercicio 6

int maior_ramo(Arvore *a)
{
  if (a != NULL)
  {
    int ramo_esq = maior_ramo(a->esq);
    int ramo_dir = maior_ramo(a->dir);
    return a->info + (ramo_esq > ramo_dir ? ramo_esq : ramo_dir);
  }
  return 0;
}

//exercicio 7

int ancestral(Arvore *a, int e1, int e2) {
  if (a != NULL) {
    if (e1 == e2) { //se os elementos são iguais e estão na árvore, o maior ancestral comum é o próprio elemento
      if (buscar(a, e1)) return e1;
    }
    //Se os elementos não estão presentes na árvore, nem faz sentido pensar em ancestral comum
    if (buscar(a, e1) && buscar(a, e2)) {
      //garantidos que ambos os elementos estão na árvore, o ancestral comum de maior ordem será aquele com a menor chave em sua subárvore da esquerda e a maior em sua direita
      //ou com uma das duas sendo ele mesmo
      if (e1 > e2) {
        int aux = e1;
        e1 = e2;
        e2 = aux;
      }

      while (a != NULL) {
        if (buscar(a->dir, e1)) a = a->dir;
        else if (buscar(a->esq, e2)) a = a->esq;
        else return a->info;
      }

    }
  }
  return INT_MIN;
}

int main()
{

  printf("ex1:\n");

  Arvore *a = cria_arvore_vazia();

  a = inserir(a, 50);
  a = inserir(a, 30);
  a = inserir(a, 90);
  a = inserir(a, 20);
  a = inserir(a, 40);
  a = inserir(a, 95);
  a = inserir(a, 10);
  a = inserir(a, 35);
  a = inserir(a, 37);

  printf("\tConstruindo:\n");

  in_order(a);

  printf("\n\tbuscando:\n");
  const int v[3] = {20, 95, 40};
  int i;
  for (i = 0; i < 3; ++i)
  {
    if (buscar(a, v[i]))
      printf("\t%d está presente na árvore\n", v[i]);
    else
      printf("\t%d não está presente na árvore\n", v[i]);
  }

  a = remover(a, 20);
  a = remover(a, 95);
  a = remover(a, 40);
  printf("\tDestruindo:\n");
  in_order(a);
  printf("\n");

  for (i = 0; i < 3; ++i)
  {
    if (buscar(a, v[i]))
      printf("\t%d está presente na árvore\n", v[i]);
    else
      printf("\t%d não está presente na árvore\n", v[i]);
  }

  a = inserir(a, 40);
  a = inserir(a, 95);
  a = inserir(a, 20);

  printf("arvore restaurada:\n");
  in_order(a);

  printf("\n\nex2:\n");

  printf("\to minimo dessa arvore e: %d\n", min(a));
  printf("\to maximo dessa arvore e: %d\n", max(a));

  printf("\n\n\nex3:\n");

  Arvore *b = gera_arvore_ordenada(10000);

  printf("\tGerou arvore ordenada\n");

  struct timespec inicial, final;

  timespec_get(&inicial, TIME_UTC);

  buscar(b, 10000);

  timespec_get(&final, TIME_UTC);

  printf("\ta busca demorou %lu nanosegundos\n", (final.tv_sec - inicial.tv_sec) * (long int)1e9 + final.tv_nsec - inicial.tv_nsec);

  printf("\n\n\nex4:\n");

  b = gera_arvore_aleatoria(10000);

  printf("\tGerou arvore aleatoria\n");

  timespec_get(&inicial, TIME_UTC);

  buscar(b, 10000);

  timespec_get(&final, TIME_UTC);

  printf("\ta busca demorou %lu nanosegundos\n", (final.tv_sec - inicial.tv_sec) * (long int)1e9 + final.tv_nsec - inicial.tv_nsec);

  printf("\n\n\nex5:\n\t");

  imprime_decrescente(a);

  printf("\n\n\nex6:\n");

  printf("\t o valor do maior ramo da arvore e %d\n", maior_ramo(a));

  printf("\n\n\nex7:\n");

  Arvore *c = cria_arvore_vazia();

  c = inserir(c, 20);
  c = inserir(c, 22);
  c = inserir(c, 8);
  c = inserir(c, 4);
  c = inserir(c, 12);
  c = inserir(c, 10);
  c = inserir(c, 14);

  printf("\to maior ancestral comum de 4 e 14 e %d\n", ancestral(c, 4, 14));
  printf("\to maior ancestral comum de 4 e 22 e %d\n", ancestral(c, 4, 22));
  printf("\to maior ancestral comum de 10 e 14 e %d\n", ancestral(c, 10, 14));

  arvore_libera(a);
  arvore_libera(b);
  arvore_libera(c);
  return 0;
}
