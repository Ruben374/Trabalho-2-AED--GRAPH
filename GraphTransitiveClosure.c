//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // Número de vértices no grafo original
  unsigned int numVertices = GraphGetNumVertices(g);

  // Criar o grafo para armazenar o fecho transitivo
  Graph* transitiveClosure = GraphCreate(numVertices, 1, 0); // Digraph, sem pesos

  // Iterar sobre todos os vértices para calcular os vértices alcançáveis
  for (unsigned int u = 0; u < numVertices; u++) {
    // Executar Bellman-Ford a partir do vértice `u`
    GraphBellmanFordAlg* bellmanFordResult = GraphBellmanFordAlgExecute(g, u);
    if (bellmanFordResult == NULL) {
      // Ciclo negativo detectado no grafo original
      printf("Ciclo de peso negativo detectado no grafo original!\n");
      GraphDestroy(&transitiveClosure);
      return NULL;
    }

    // Para cada vértice `v` no grafo, verificar se é alcançável a partir de `u`
    for (unsigned int v = 0; v < numVertices; v++) {
      if (u != v && GraphBellmanFordAlgReached(bellmanFordResult, v)) {
        // Se `v` é alcançável a partir de `u` e não é um loop, adicionar a aresta (u, v)
        GraphAddEdge(transitiveClosure, u, v);
      }
    }

    // Destruir o resultado de Bellman-Ford para liberar memória
    GraphBellmanFordAlgDestroy(&bellmanFordResult);
  }

  // Retornar o grafo de fecho transitivo
  return transitiveClosure;
}

