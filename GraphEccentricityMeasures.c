//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"
#include <limits.h>  
struct _GraphEccentricityMeasures
{
  unsigned int *
      centralVertices; // centralVertices[0] = number of central vertices
                       // array size is (number of central vertices + 1)
  int *eccentricity;   // the eccentricity value of each vertex
  Graph *graph;        // the graph
  int graphRadius;     // the graph radius
  int graphDiameter;   // the graph diameter
};

// Auxiliary function: Compute eccentricity of a vertex
static int _ComputeVertexEccentricity(const int *distances, unsigned int numVertices)
{
  int maxDistance = -1;
  for (unsigned int i = 0; i < numVertices; i++)
  {
    if (distances[i] != -1 && distances[i] > maxDistance)
    {
      maxDistance = distances[i];
    }
  }
  return maxDistance;
}

// Allocate memory and compute the eccentricity measures
GraphEccentricityMeasures *GraphEccentricityMeasuresCompute(Graph *g)
{
  assert(g != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  // Criar e inicializar a estrutura para as medidas de excentricidade
  GraphEccentricityMeasures *measures =
      (GraphEccentricityMeasures *)malloc(sizeof(GraphEccentricityMeasures));
  assert(measures != NULL);

  measures->eccentricity = (int *)malloc(numVertices * sizeof(int));
  assert(measures->eccentricity != NULL);

  measures->graph = g;
  measures->graphRadius = INT_MAX; // Inicializar com valores extremos
  measures->graphDiameter = INT_MIN;

  // Obter todas as distâncias entre os pares de vértices
  GraphAllPairsShortestDistances *apsd = GraphAllPairsShortestDistancesExecute(g);
  if (apsd == NULL)
  {
    printf("Erro ao calcular as distâncias entre os pares de vértices.\n");
    free(measures->eccentricity);
    free(measures);
    return NULL;
  }

  // Calcular a excentricidade de cada vértice
  for (unsigned int v = 0; v < numVertices; v++)
  {
    int maxDistance = INT_MIN;
    for (unsigned int w = 0; w < numVertices; w++)
    {
      int distance = GraphGetDistanceVW(apsd, v, w);
      if (distance != -1 && distance > maxDistance)
      {
        maxDistance = distance;
      }
    }
    measures->eccentricity[v] = maxDistance;

    // Atualizar o raio e o diâmetro
    if (maxDistance < measures->graphRadius)
    {
      measures->graphRadius = maxDistance;
    }
    if (maxDistance > measures->graphDiameter)
    {
      measures->graphDiameter = maxDistance;
    }
  }

  // Determinar os vértices centrais
  unsigned int centralVerticesCount = 0;
  for (unsigned int v = 0; v < numVertices; v++)
  {
    if (measures->eccentricity[v] == measures->graphRadius)
    {
      centralVerticesCount++;
    }
  }

  measures->centralVertices = (unsigned int *)malloc((centralVerticesCount + 1) * sizeof(unsigned int));
  assert(measures->centralVertices != NULL);

  measures->centralVertices[0] = centralVerticesCount;
  unsigned int index = 1;
  for (unsigned int v = 0; v < numVertices; v++)
  {
    if (measures->eccentricity[v] == measures->graphRadius)
    {
      measures->centralVertices[index++] = v;
    }
  }

  // Limpar o módulo de distâncias
  GraphAllPairsShortestDistancesDestroy(&apsd);

  return measures;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures **p)
{
  assert(*p != NULL);

  GraphEccentricityMeasures *aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures *p,
                               unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int *GraphGetCentralVertices(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  unsigned int centralCount = p->centralVertices[0];
  unsigned int *centralCopy =
      (unsigned int *)malloc((centralCount + 1) * sizeof(unsigned int));
  assert(centralCopy != NULL);

  for (unsigned int i = 0; i <= centralCount; i++)
  {
    centralCopy[i] = p->centralVertices[i];
  }

  return centralCopy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  printf("Vertex Eccentricities:\n");
  unsigned int numVertices = GraphGetNumVertices(p->graph);
  for (unsigned int v = 0; v < numVertices; v++) {
    printf(" Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  printf("Central Vertices (Radius = %d):\n", p->graphRadius);
  for (unsigned int i = 1; i <= p->centralVertices[0]; i++) {
    printf(" %u", p->centralVertices[i]);
  }
  printf("\n");
}
