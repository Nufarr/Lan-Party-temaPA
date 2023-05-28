

int max(int a, int b){
	if(a >= b)
		return a;
	else return b;
}

int graphHeight(Graph *root){
	if(root == NULL)
		return -1;
	int kl=0,kr=0;
	kl = graphHeight(root->left)+1;
	kr = graphHeight(root->right)+1;
	return max(kl, kr);
}

Graph *rightRotation(Graph *z) {
	Graph *y = z->left;
	Graph *T3 = y->right;
	y->right = z;
	z->left = T3;
	return y;
}

Graph *leftRotation(Graph *z) {
	Graph *y = z->right;
	Graph *T2 = y->left;
	y->left = z;
	z->right = T2;
	return y;
}

Graph* LRRotation(Graph *z) {
	z->left = leftRotation(z->left);
	return rightRotation(z);
}

Graph* RLRotation(Graph *z) {
	z->right = rightRotation(z->right);
	return leftRotation(z);
}

Graph* newGraphAVL(Top8* data)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->teamName = data->teamName;
    graph->score = data->score;
    graph->left = graph->right = NULL;
	graph->height = 0;
    return graph;
}

Graph* insertAVL(Graph *graph, Top8 *key) //inserarea unui nod in avl
{
	if(graph == NULL)
        return newGraphAVL(key);

    if(key->score < graph->score)
        graph->left = insertAVL(graph->left, key);
    else if(key->score > graph->score)
        graph->right = insertAVL(graph->right, key);
    else if(key->score == graph->score)
    {
        if(strcmp(key->teamName, graph->teamName) < 0)
        graph->left = insertAVL(graph->left, key);
        else if(strcmp(key->teamName, graph->teamName) > 0)
        graph->right = insertAVL(graph->right, key);
    }
	
    graph->height = 1 + max(graphHeight(graph->left),graphHeight(graph->right));
	
	int k = (graphHeight(graph->left) - graphHeight(graph->right));

	//LL
	if(k > 1 && (key->score < graph->left->score || (key->score == graph->left->score && strcmp(key->teamName,graph->left->teamName)<0)))
		return rightRotation(graph);
	
	//RR
	if(k < -1 && (key->score > graph->right->score || (key->score == graph->right->score && strcmp(key->teamName,graph->right->teamName)>0)))
		return leftRotation(graph);
	
	//LR
	if(k > 1 && (key->score > graph->left->score || (key->score == graph->left->score && strcmp(key->teamName,graph->left->teamName)>0)))
		return LRRotation(graph);

	//RL
	if(k < -1 && (key->score < graph->right->score || (key->score == graph->right->score && strcmp(key->teamName,graph->right->teamName)<0)))
		return RLRotation(graph);

	return graph;
}

void displayLvl2(Graph *avl, FILE *outputFile) //afisseaza nivelul 2 din avl
{
	Graph *ravl = avl->right, *lavl = avl->left;
	fprintf(outputFile, "%s\n%s\n", ravl->right->teamName, ravl->left->teamName);
	fprintf(outputFile, "%s\n%s\n", lavl->right->teamName, lavl->left->teamName);
}