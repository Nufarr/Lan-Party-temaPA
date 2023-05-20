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

void deleteTop8(Top8** head)
{
	Top8  *aux;
	while ((*head) != NULL){
		aux=*head;
		*head=(*head)->next;
		free(aux);
	}
}