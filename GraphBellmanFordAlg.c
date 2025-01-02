//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Ruben André
// Student Number : 117592
// Student Name : Mario Silva
// Student Number : 110657

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg
{
  unsigned int *marked; // To mark vertices when reached for the first time
  int *distance;        // The number of edges on the path from the start vertex
                        // distance[i]=-1, if no path found from the start vertex to i
  int *predecessor;     // The predecessor vertex in the shortest path
                        // predecessor[i]=-1, if no predecessor exists
  Graph *graph;
  unsigned int startVertex; // The root of the shortest-paths tree
};

GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result = (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  result->distance = malloc(sizeof(int) * numVertices);
  assert(result->distance != NULL);
  result->marked = malloc(sizeof(unsigned int) * numVertices);
  assert(result->marked != NULL);
  result->predecessor = malloc(sizeof(int) * numVertices);
  assert(result->predecessor != NULL);

  // Inicializa os valores
  for (unsigned int i = 0; i < numVertices; i++) {
    result->marked[i] = 0;       // Nenhum vértice alcançado ainda
    result->distance[i] = -1;    // Distância "infinita"
    result->predecessor[i] = -1; // Sem predecessor
  }

  // Configura o vértice inicial
  result->marked[startVertex] = 1;
  result->distance[startVertex] = 0;

  // Verifica o tipo do grafo
  int isDigraph = GraphIsDigraph(g);
  int start_v_degree = isDigraph ? GraphGetVertexOutDegree(g, startVertex) : GraphGetVertexDegree(g, startVertex);
  int n_vertices = GraphGetNumVertices(result->graph);

  // Não existe nenhum caminho
  if (n_vertices == 0 || start_v_degree == 0) {
    return result;
  }

  // Implementar uma pilha para percorrer os vértices
  Stack* vertices = StackCreate(n_vertices); 
  StackPush(vertices, startVertex);

  // Algoritmo de Bellman-Ford
  while(!StackIsEmpty(vertices)) {
    // Obter os vértices adjacentes de u
    unsigned int v = StackPop(vertices);      
    result->marked[v] = 1;
    unsigned int* adjacents = GraphGetAdjacentsTo(g, v);

    if (adjacents == NULL || adjacents[0] == 0) {
      continue;
    }

    for (unsigned int i = 1; i <= adjacents[0]; i++) {
      unsigned int u = adjacents[i];
      
      // relaxar as arestas
      if (result->distance[u] == -1 || result->distance[u] > result->distance[v] + 1) {
        result->distance[u] = result->distance[v] + 1;
        result->predecessor[u] = v;
      }

      if (!result->marked[u])
        StackPush(vertices, u);

    }
  }

  StackDestroy(&vertices);

  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg **p)
{
  assert(*p != NULL);

  GraphBellmanFordAlg *aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack *GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0)
  {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current])
  {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0)
  {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg *p)
{
  assert(p != NULL);

  Graph *original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph *paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++)
  {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1)
    {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
