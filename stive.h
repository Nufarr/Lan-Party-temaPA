//#include "player.h"

typedef struct Stack{
    Team *val;
    struct Stack *next;
}Stack;

void push(Stack **top, Team *v) {
	Stack* newNode;
    newNode = (Stack*)malloc(sizeof(Stack));
	newNode->val = v;
	newNode->next = *top;
	*top=newNode;
}

int isEmptyStack(Stack *top){
	return top==NULL;
}


Team* pop(Stack **top) {
	if (isEmptyStack(*top)) return NULL;
	Stack *temp = (*top);
	Team *aux;
    aux = (Team*)malloc(sizeof(Team));
    aux = temp->val;
	*top = (*top)->next;
	free(temp);
	return aux;
}

void deleteStack(Stack **top){
	Stack  *temp;
	while (!isEmptyStack(*top)){
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
}


void displayWinners(Stack *winners, FILE *outputFile)
{
	while (winners!=NULL){
		fprintf(outputFile, "\n%-33s -  %0.2f", winners->val->teamName, winners->val->score);
		winners = winners->next;
	}
	fprintf(outputFile,"\n");
}