//#include "player.h"

typedef struct Node{
    Team *teamA;
    Team *teamB;
	struct Node *next;
}Node;

typedef struct Queue{
    Node *head;
    Node *tail;
}Queue;

Queue* createQueue(){
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q==NULL) return NULL;
	q->head=q->tail=NULL;
	return q;
}

int isEmpty(Queue*q){
	return (q->head==NULL);
}

 void enQueue(Queue*q, Team *a, Team *b){
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->teamA = (Team*)malloc(SIZE*sizeof(Team));
	newNode->teamB = (Team*)malloc(SIZE*sizeof(Team));
	newNode->teamA = a;
	newNode->teamB = b;
	newNode->next=NULL;
	if (q->tail==NULL) q->tail=newNode;
	else{
		(q->tail)->next=newNode;
		(q->tail)=newNode;
	}
	if (q->head==NULL) q->head=q->tail;
}

void deQueue(Queue**q, Team **teamA, Team **teamB) {
	Node *aux;
	//Team *team;

	if (isEmpty(*q)) return;

	*teamA = (*q)->head->teamA;
	*teamB = (*q)->head->teamB;
	aux=(*q)->head;
	if((*q)->head != (*q)->tail)
	{
		(*q)->head=((*q)->head)->next;
		free(aux);
		aux = NULL;
	}
	else
	{
		(*q)->head = (*q)->tail = NULL;
		aux = NULL;
	}
	
	//return team;
}

void deleteQueue(Queue **q){
	Node* aux;
	while (!isEmpty(*q)){
		aux=(*q)->head;
		(*q)->head=(*q)->head->next;
		free(aux);
		free((*q)->tail);
	}
	free(q);
}

void displayOpponents(Queue *match, FILE *outputFile)
{
	Node *copy;
	copy = match->head;
	while (copy!=NULL){
		fprintf(outputFile, "\n%-32s - %32s", copy->teamA->teamName, copy->teamB->teamName);
		copy= copy->next;
	}
	fprintf(outputFile,"\n");
}