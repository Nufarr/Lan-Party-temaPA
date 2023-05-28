
typedef struct Stack{
	struct Stack *next;
    Team *val;
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

void decideWinnersAndLosers(Queue **match,Stack **winners, Stack **losers, Team **A, Team **B) //creaza listele de catigatori si pierzatori
{
    while(!isEmpty(*match))
        {
            deQueue(match, A, B);
            if((*A)->score <= (*B)->score)
            {
                push(losers, *A);
                (*B)->score++;
                push(winners, *B);
            }
            else
            {
                push(losers, *B);
                (*A)->score++;
                push(winners, *A);   
            }
        }
}

void displayWinners(Stack *winners, FILE *outputFile) //afiseaza listele de castigatori
{
	while (winners!=NULL){
		fprintf(outputFile, "\n%-33s -  %0.2f", winners->val->teamName, winners->val->score);
		winners = winners->next;
	}
	fprintf(outputFile,"\n");
}
