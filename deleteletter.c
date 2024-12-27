Graph *GraphCreateTranspose(const Graph *g)
{
    assert(g != NULL);
    assert(g->isDigraph);
    assert(g->isComplete == 0);

    // Cria o grafo transposto com os mesmos parâmetros do original
    Graph *gT = GraphCreate(g->numVertices, g->isDigraph, g->isWeighted);

    // Itera sobre todos os vértices do grafo original
    List *originalVerticesList = g->verticesList;
    ListMoveToHead(originalVerticesList);

    for (unsigned int i = 0; i < g->numVertices; i++)
    {
        // Obtém o vértice atual do grafo original
        struct _Vertex *originalVertex = ListGetCurrentItem(originalVerticesList);
        assert(originalVertex != NULL);

        // Itera sobre as arestas do vértice atual
        List *originalEdgesList = originalVertex->edgesList;
        ListMoveToHead(originalEdgesList);

        for (unsigned int j = 0; j < ListGetSize(originalEdgesList); j++)
        {
            struct _Edge *originalEdge = ListGetCurrentItem(originalEdgesList);
            assert(originalEdge != NULL);

            // Obtém o vértice de destino no grafo transposto
            unsigned int targetId = originalEdge->adjVertex;
            struct _Vertex *targetVertex = NULL;

            // Localiza o vértice de destino no grafo transposto pelo ID
            ListMoveToHead(gT->verticesList);
            for (unsigned int k = 0; k < gT->numVertices; k++)
            {
                struct _Vertex *currentVertex = ListGetCurrentItem(gT->verticesList);
                if (currentVertex->id == targetId)
                {
                    targetVertex = currentVertex;
                    break;
                }
                ListMoveToNext(gT->verticesList);
            }
            assert(targetVertex != NULL);

            // Cria uma nova aresta no grafo transposto
            struct _Edge *newEdge = (struct _Edge *)malloc(sizeof(struct _Edge));
            if (newEdge == NULL)
                abort();

            newEdge->adjVertex = originalVertex->id; // Inverte a direção da aresta
            newEdge->weight = originalEdge->weight;

            // Insere a nova aresta no grafo transposto
            ListInsert(targetVertex->edgesList, newEdge);

            // Atualiza os graus de entrada e saída
            targetVertex->outDegree++;
            originalVertex->inDegree++;

            // Avança para a próxima aresta
            ListMoveToNext(originalEdgesList);
        }

        // Avança para o próximo vértice
        ListMoveToNext(originalVerticesList);
    }

    return gT;
}
