#include <stdio.h>
#include <math.h>

int pai(int i)
{
   return (i - 1) / 2;
}

int esquerda(int i)
{
   return 2 * i + 1;
}

int direita(int i)
{
   return 2 * i + 2;
}

void trocar(int V[], int a, int b)
{
   int aux = V[a];
   V[a] = V[b];
   V[b] = aux;
}

void imprimir(int V[], int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      printf("%d ", V[i]);
   }
   printf("\n");
}

void max_heapify(int V[], int size, int i)
{
   if (V == NULL || i >= size)
      return;
   int e = esquerda(i);
   int d = direita(i);
   int maior = i;
   if (e < size && V[e] > V[i])
      maior = e;
   if (d < size && V[d] > V[maior])
      maior = d;

   if (maior != i)
   {
      trocar(V, i, maior);
      max_heapify(V, size, maior);
   }
}

void build_max_heap(int V[], int size)
{
   int i;
   for (i = (int)floor(size / 2) - 1; i >= 0; i--) //-1 pois começamos indexando em 0 
   {
    
      max_heapify(V, size, i);
   }
}

void heap_sort(int V[], int size)
{
   build_max_heap(V, size);
   int i;
   for (i = size - 1; i > 0; --i) {
      trocar(V, 0, i);
      max_heapify(V, i, 0);
   }
}

int main()
{

   int i;

   int size = 10;

   int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

   printf("Vetor inicial : ");
   imprimir(V, size);

   heap_sort(V, size);

   printf("Vetor ordenado: ");
   imprimir(V, size);

   return 0;
}
