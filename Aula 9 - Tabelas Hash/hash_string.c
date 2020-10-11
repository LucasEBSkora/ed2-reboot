#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  char k[256];
  struct node *next;
} Node;

typedef struct _hash
{
  unsigned int M;
  Node **tabela;
} Hash;

unsigned int hash_function(const char *v, unsigned int M)
{
  int i, h = v[0];
  for (i = 1; v[i] != '\0'; ++i)
    h = (h * 128 + v[i]) % 7; //um char é um valor entre -127 e 127, mas só utilizamos os positivos
  return h;
}

Hash *create_hash(unsigned int M)
{
  Hash *novo = (Hash *)malloc(sizeof(Hash));
  novo->M = M;
  novo->tabela = (Node **)calloc(M, sizeof(Node));
  return novo;
}

void insert_chained(Hash* H, const char* v) {
  int valorHash = hash_function(v, H->M);
  Node* novoNo = (Node*) malloc(sizeof(Node));
  strcpy(novoNo->k, v);
  novoNo->next = H->tabela[valorHash];
  H->tabela[valorHash] = novoNo;
}

void print_hash(Hash *H)
{
  int h;
  for (h = 0; h < H->M; h++)
  {
    Node *aux;
    for (aux = H->tabela[h]; aux != NULL; aux = aux->next)
    {
      printf("| %s ", aux->k);
    }
    printf("| \n");
  }
}

void free_hash(Hash *H)
{
  int h;
  for (h = 0; h < H->M; h++)
  {
    free(H->tabela[h]);
  }
  free(H);
}

int main()
{

  int M = 7;

  Hash *H = create_hash(M);

  const char *nomes[12] = {
      "Marina",
      "Pedro",
      "Joana",
      "Thais",
      "Fabio",
      "Jonas",
      "Joaquim",
      "Mauricio",
      "Jorge",
      "Ana",
      "Patricia",
      "Henrique",
  };
  int i = 0;

  for (; i < 12; ++i)
    insert_chained(H, nomes[i]);

  print_hash(H);

  free_hash(H);

  return 0;
}
