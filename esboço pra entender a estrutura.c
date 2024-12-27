Graph (struct _GraphHeader)
+------------------------------------------------------------+
| isDigraph (int): indica se o grafo é direcionado           |
| isComplete (int): indica se o grafo é completo             |
| isWeighted (int): indica se o grafo possui pesos           |
| numVertices (unsigned int): número de vértices             |
| numEdges (unsigned int): número de arestas                 |
| verticesList (List*): lista de vértices                    |
+------------------------------------------------------------+
                             |
                             v
Vertices List (List)
+------------------------------------------------------------+
| Elementos: Ponteiros para estruturas _Vertex               |
+------------------------------------------------------------+
      |                            |                       |
      v                            v                       v
Vertex (struct _Vertex)        Vertex (struct _Vertex)    ...
+------------------------------------------------------------+
| id (unsigned int): identificador do vértice               |
| inDegree (unsigned int): grau de entrada                  |
| outDegree (unsigned int): grau de saída                   |
| edgesList (List*): lista de arestas deste vértice         |
+------------------------------------------------------------+
              |
              v
Edges List (List)
+------------------------------------------------------------+
| Elementos: Ponteiros para estruturas _Edge                 |
+------------------------------------------------------------+
      |                            |                       |
      v                            v                       v
Edge (struct _Edge)          Edge (struct _Edge)          ...
+------------------------------------------------------------+
| adjVertex (unsigned int): vértice adjacente (destino)      |
| weight (double): peso da aresta                            |
+------------------------------------------------------------+






































// =====================
// SortedList (struct _SortedList)
// =====================

  +-------------------------------------------------------------+
  | size (int): Tamanho atual da lista                          |
  | head (struct _ListNode*): Ponteiro para o primeiro nó       |
  | tail (struct _ListNode*): Ponteiro para o último nó         |
  | current (struct _ListNode*): Ponteiro para o nó atual       |
  | currentPos (int): Posição do nó atual                      |
  | compare (compFunc): Função para comparar elementos          |
  +-------------------------------------------------------------+
                                  |
                                  

// =====================
// ListNode (struct _ListNode)
// =====================

  +-------------------------------------------------------------+
  | item (void*): Ponteiro para o elemento armazenado           |
  | next (struct _ListNode*): Ponteiro para o próximo nó        |
  +-------------------------------------------------------------+
          |                          |                           |
          v                          v                           v
  Elemento Armazenado         Elemento Armazenado          ...


/* Representação textual com conexões */
