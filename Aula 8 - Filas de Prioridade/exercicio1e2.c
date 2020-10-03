#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int pai(int i)
{
  return (i - 1) / 2;
}

unsigned int esquerda(unsigned int i)
{
  return 2 * i + 1;
}

unsigned int direita(unsigned int i)
{
  return 2 * i + 2;
}

//copiado da semana passada

void trocar(int V[], int a, int b)
{
  int aux = V[a];
  V[a] = V[b];
  V[b] = aux;
}

void maxHeapify(int V[], unsigned int tam, unsigned int i)
{
  if (V == NULL || i >= tam)
    return;
  int e = esquerda(i);
  int d = direita(i);
  int maior = i;
  if (e < tam && V[e] > V[i])
    maior = e;
  if (d < tam && V[d] > V[maior])
    maior = d;

  if (maior != i)
  {
    trocar(V, i, maior);
    maxHeapify(V, tam, maior);
  }
}

void maxHeapDecreaseKey(int *V, unsigned int tam, unsigned int i, int valor)
{
  if (i < tam)
  {
    int aux = V[i];
    V[i] = valor;
    if (valor < aux)
    {
      maxHeapify(V, tam, i);
    }
  }
}

void minHeapify(int *V, unsigned int tam, unsigned int i)
{
  if (i >= tam)
    return;
  unsigned int esq = esquerda(i);
  unsigned int dir = direita(i);

  int menor = i;
  if (esq < tam && V[esq] < V[i])
    menor = esq;
  if (dir < tam && V[dir] < V[menor])
    menor = dir;

  if (menor != i)
  {
    trocar(V, i, menor);
    minHeapify(V, tam, menor);
  }
}

void buildMinHeap(int *V, unsigned int tam)
{
  int i;
  for (i = tam / 2 - 1; i >= 0; --i)
    minHeapify(V, tam, i);
}

int heapMinimum(int *V, unsigned int tam)
{
  return V[0];
}

unsigned int heapExtractMin(int *V, unsigned int tam)
{
  --tam;
  trocar(V, 0, tam);
  minHeapify(V, tam, 0);
  return tam;
}

void heapDecreaseKey(int *V, unsigned int tam, int i, int valor)
{
  if (i >= tam)
    return;

  V[i] = valor;

  while (pai(i) >= 0 && V[pai(i)] > V[i])
  {
    trocar(V, i, pai(i));
    i = pai(i);
  }
}

unsigned int minHeapInsert(int *V, unsigned int tam, int valor)
{
  //assumindo que o heap tem memória alocada sobrando para aumentá-lo

  V[tam] = INT_MAX;
  ++tam;

  heapDecreaseKey(V, tam, tam - 1, valor);

  return tam;
}

void printHeap(int *V, unsigned int tam)
{
  unsigned int i;
  unsigned int n = 0;
  unsigned int h = 2;
  for (i = 0; i < tam; ++i)
  {
    printf("%d ", V[i]);

    if (i == n)
    {
      printf("\n");
      n += h;
      h *= 2;
    }
  }
  printf("\n");
}

int main()
{
  int heap1[12] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
  const unsigned int tam1 = 12;
  printf("exercicio 1:\n");
  printHeap(heap1, tam1);

  maxHeapDecreaseKey(heap1, tam1, 0, 1);
  printf("apos Max-Heap-Decrease-Key(heap1, N, 0, 1):\n");
  printHeap(heap1, tam1);

  int heap2[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  unsigned int tam2 = 10;
  printf("exercicio 2:\n");
  printHeap(heap2, tam2);

  buildMinHeap(heap2, tam2);
  printf("Build-Min_Heap(V, N):\n");
  printHeap(heap2, tam2);

  printf("Heap-Extract-Min(V, N) == %d\n", heapMinimum(heap2, tam2));
  tam2 = heapExtractMin(heap2, tam2);
  printHeap(heap2, tam2);

  heapDecreaseKey(heap2, tam2, 8, 1);
  printf("Heap-Decrease-Key(V, N, 8, 1):\n");
  printHeap(heap2, tam2);

  tam2 = minHeapInsert(heap2, tam2, 0);
  printf("Min-Heap-Insert(V, N, 0):\n");
  printHeap(heap2, tam2);

  return 0;
}