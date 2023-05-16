
typedef struct Graph{
    char *teamName;
    float score;
    struct Graph *left, *right;
}Graph;

Graph* newGraph(Top8* data)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->teamName = data->teamName;
    graph->score = data->score;
    graph->left = graph->right = NULL;
    return graph;
}

Graph* insert(Graph *graph, Top8 *key)
{
    // daca subarborele este gol
    if(graph == NULL)
        return newGraph(key);

    if(key->score < graph->score)
        graph->left = insert(graph->left, key);
    else if(key->score > graph->score)
        graph->right = insert(graph->right, key);
    else if(key->score == graph->score)
    {
        if(strcmp(key->teamName, graph->teamName) < 0)
        graph->left = insert(graph->left, key);
        else if(strcmp(key->teamName, graph->teamName) > 0)
        graph->right = insert(graph->right, key);
    }
    return graph;
}

Graph* createBST(Graph *graph, Top8 *top)
{
    Top8 *aux;
    aux = top;
    while(aux != NULL)
    {
        graph = insert(graph, aux);
        aux = aux->next;
    }
    return graph;
}

Graph* inorder(Graph *graph, FILE* outputFile)
{
    if(graph){
        inorder(graph->right, outputFile);
        fprintf(outputFile, "%-33s -  %0.2f\n", graph->teamName, graph->score);
        inorder(graph->left, outputFile);
    }
}