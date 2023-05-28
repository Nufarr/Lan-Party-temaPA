typedef struct Top8{
    char *teamName;
    float score;
    struct Top8 *next;
}Top8;

void pushTop8(Top8 **top, char *teamName, float score) {
	Top8* newNode;
    newNode = (Top8*)malloc(sizeof(Top8));
	newNode->teamName = teamName;
    newNode->score = score;
	newNode->next = *top;
	*top=newNode;
}

void addAtBeginning(Top8 **head, char *teamName, float score)
{
	Top8* newNode = (Top8*)malloc(sizeof(Top8));
	newNode->teamName = teamName;
    newNode->score = score;
	newNode->next = *head;
	*head = newNode;
}

void addAtEnd(Top8** head, char *teamName, float score)
{
	Top8 *aux=*head;
	Top8* newNode = (Top8*)malloc(sizeof(Top8));
	newNode->teamName = teamName;
    newNode->score = score;
	if (*head == NULL) addAtBeginning(&*head, teamName, score);
	else{
		while (aux->next!=NULL) aux = aux->next;
		aux->next = newNode;
		newNode->next = NULL;
	}
}

Top8 *createTop8(Top8 *top8, Stack **winners, Queue **match) //creaza lista de top 8 pentru task-ul 4
{
    Stack *top;
    top = *winners;
    //punem in top8 echipele din winners pt bst
    while(top != NULL)
    {
        pushTop8(&top8, top->val->teamName, top->val->score); 
        top = top->next;
    }
                
    while(!isEmptyStack(*winners))
    {
        Team *A = pop(winners);
        Team *B = pop(winners);
        enQueue(*match, A, B);
    }

    return top8;
}

void deleteTop8(Top8** head)  //sterge lista de Top8
{
	Top8  *aux;
	while ((*head) != NULL){
		aux=*head;
		*head=(*head)->next;
		free(aux);
	}
}