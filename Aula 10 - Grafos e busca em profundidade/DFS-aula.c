#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BRANCO 1
#define CINZA 2
#define PRETO 3

/*Estrutura para um vértice em uma lista encadeada: */
typedef struct vertice
{
   int d;
   int f;
   int cor;
   int pai;
   int identificador;       /*Identificador do vértice armazenado no nó. */
   struct vertice *proximo; /* Próximo nó na lista encadeada. */
} Vertice;

/*Estrutura do Grafo: */
typedef struct grafo
{
   int E;              /* Quantidade de arestas. */
   int V;              /* Quantidade de vértices. */
   Vertice **listaAdj; /* Lista de adjacências. */
} Grafo;

/* */
Grafo *criar_grafo(int tamanho)
{
   int v;
   Grafo *G = (Grafo *)malloc(sizeof(Grafo));
   G->E = 0;
   G->V = tamanho;
   G->listaAdj = (Vertice **)malloc(tamanho * sizeof(Vertice *));
   for (v = 0; v < G->V; v++)
   {
      G->listaAdj[v] = NULL;
   }
   return G;
}

/* */
void liberar_grafo(Grafo *G)
{
   int v;
   for (v = 0; v < G->V; v++)
   {
      if (G->listaAdj[v] != NULL)
      {
         free(G->listaAdj[v]);
      }
   }
   free(G->listaAdj);
   free(G);
}

/* */
void inserir_aresta(Grafo *G, int u, int v)
{
   Vertice *temp, *ultimo = NULL;
   /* Verificando se o vértice v já existe na lista de adjacência de u: */
   for (temp = G->listaAdj[u]; temp != NULL; temp = temp->proximo)
   {
      if (temp->identificador == v)
      {
         return;
      }
      ultimo = temp;
   }
   /* Inserindo a aresta (u,v): */
   Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
   novo->identificador = v;
   novo->proximo = NULL;
   if (ultimo != NULL)
   {
      /* Inserção na última posição da lista: */
      ultimo->proximo = novo;
   }
   else
   {
      /* Nova cabeça da lista: */
      G->listaAdj[u] = novo;
   }
   /* Incrementando o número de arestas: */
   G->E++;
}

/* */
void imprimir_grafo(Grafo *G)
{
   printf("Lista de adjacência de G:\n");
   int v;
   for (v = 0; v < G->V; v++)
   {
      if (G->listaAdj[v] != NULL)
      {
         Vertice *temp;
         printf("Nó %d : ", v);
         for (temp = G->listaAdj[v]; temp != NULL; temp = temp->proximo)
         {
            printf(" %d ", temp->identificador);
         }
         printf("\n");
      }
   }
}

void adicionar_string(char *c, int u)
{
   char aux[4];
   sprintf(aux, "%d ", u);
   strcat(c, aux);
}

/* */
void DFS_Visit(Grafo *G, Vertice *V, int u, int *tempo, char *str)
{
   adicionar_string(str, u);
   V[u].cor = CINZA;
   *tempo = (*tempo) + 1;
   V[u].d = (*tempo);
   Vertice *v;
   for (v = G->listaAdj[u]; v != NULL; v = v->proximo)
   {
      if (V[v->identificador].cor == BRANCO)
      {
         printf("Aresta arvore: %d -> %d\n", u, v->identificador);
         V[v->identificador].pai = u;
         DFS_Visit(G, V, v->identificador, tempo, str);
      }
      else
         printf("Aresta outra: %d -> %d\n", u, v->identificador);
   }
   V[u].cor = PRETO;
   *tempo = (*tempo) + 1;
   V[u].f = *tempo;
}

/* */
void Busca_Profundidade(Grafo *G)
{
   //permitir grafos conexos com até 999 elementos
   char *c = malloc(G->V * 4 * sizeof(char));
   c[0] = '\0';
   int u;
   int tempo = 0;
   Vertice *V = (Vertice *)malloc(G->V * sizeof(Vertice));
   for (u = 0; u < G->V; u++)
   {
      V[u].cor = BRANCO;
      V[u].pai = -1;
   }
   for (u = 0; u < G->V; u++)
   {
      if (V[u].cor == BRANCO)
      {
         DFS_Visit(G, V, u, &tempo, c);
         printf("Comecando do vertice %d (DFS): %s\n", u, c);
         c[0] = '\0';
      }
   }
   printf("Busca em profundidade:\n");
   for (u = 0; u < G->V; u++)
   {
      printf("%d = [d : %2d, f : %2d, pai : %2d]\n", u, V[u].d, V[u].f, V[u].pai);
   }

   free(c);
}

/* */
int main()
{

   int tamanho = 8; /*Número de vértices!*/

   Grafo *G = criar_grafo(tamanho);

   /* Ordem dos vértices da busca em
      profundidade vista em aula:
      2  1  0  5
      3  4  7  6
   */

   /*Inserção das arestas conforme a aula: */
   inserir_aresta(G, 0, 1);
   inserir_aresta(G, 0, 4);
   inserir_aresta(G, 1, 2);
   inserir_aresta(G, 1, 4);
   inserir_aresta(G, 2, 3);
   inserir_aresta(G, 3, 1);
   inserir_aresta(G, 4, 3);
   inserir_aresta(G, 5, 7);
   inserir_aresta(G, 5, 6);
   inserir_aresta(G, 6, 7);
   inserir_aresta(G, 6, 5);
   inserir_aresta(G, 7, 0);
   inserir_aresta(G, 7, 4);

   imprimir_grafo(G);

   Busca_Profundidade(G);

   liberar_grafo(G);

   tamanho = 12;

   G = criar_grafo(tamanho);

   inserir_aresta(G, 0, 1);
   inserir_aresta(G, 0, 3);
   inserir_aresta(G, 1, 2);
   inserir_aresta(G, 2, 5);
   inserir_aresta(G, 5, 4);
   inserir_aresta(G, 5, 6);
   inserir_aresta(G, 4, 1);
   inserir_aresta(G, 6, 0);
   inserir_aresta(G, 6, 3);
   inserir_aresta(G, 6, 4);
   inserir_aresta(G, 7, 8);
   inserir_aresta(G, 9, 10);
   inserir_aresta(G, 10, 11);
   inserir_aresta(G, 11, 9);

   imprimir_grafo(G);
   Busca_Profundidade(G);

   liberar_grafo(G);

   return 0;
}
