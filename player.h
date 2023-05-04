#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Data;

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player *next;
} Player;

typedef struct Team
{
    int numOfPlayers;
    int score;
    char* teamName;
    Player *player;
    struct Team *next;
} Team;

void addAtBeginningTeam(Team **head, int numofPlayers, char* teamName, Player *player)
{
	Team* newNode = (Team*)malloc(sizeof(Team));
	newNode->numOfPlayers = numofPlayers;
    newNode->teamName = teamName;
	newNode->next = *head;
    newNode->player = player;
	*head = newNode;
}
/*
void addAtEndTeam(Team** head, int numofPlayers, char* teamName, Player *player)
{
	Team *aux=*head;
	Team* newNode = (Team*)malloc(sizeof(Team));
	newNode->numOfPlayers = numofPlayers;
    newNode->teamName = teamName;
    newNode->player = player;
	if (*head == NULL) addAtBeginningTeam(&*head, numofPlayers, teamName, player);
	else{
		while (aux->next!=NULL) aux = aux->next;
		aux->next = newNode;
		newNode->next = NULL;
	}
}
*/
void addAtBeginningPlayer(Player **head, char *firstName, char *secondName, int points)
{
	Player* newNode = (Player*)malloc(sizeof(Player));
	newNode->points = points;
    newNode->firstName = firstName;
    newNode->secondName = secondName;
	newNode->next = *head;
	*head = newNode;
}
/*
void addAtEndPlayer(Player** head, char *firstName, char *secondName, int points)
{
	Player *aux=*head;
	Player* newNode = (Player*)malloc(sizeof(Player));
	newNode->points = points;
    newNode->firstName = firstName;
    newNode->secondName = secondName;
	if (*head == NULL) addAtBeginningPlayer(&*head, firstName, secondName, points);
	else{
		while (aux->next!=NULL) aux = aux->next;
		aux->next = newNode;
		newNode->next = NULL;
	}
}
*/
void displayTeams(Team *teams, int numOfTeams, FILE *outputFile)
{
    //fprintf(outputFile, "%d\n\n", numOfTeams);

    while (teams!=NULL)
    {
		//fprintf(outputFile, "%d ", teams->numOfPlayers);
        fprintf(outputFile, "%s\n", teams->teamName);
        /*
        while (teams -> player!=NULL)
        {
            fprintf(outputFile,"%s ", teams->player->firstName);
            fprintf(outputFile,"%s ", teams->player->secondName);
            fprintf(outputFile,"%d\n", teams->player->points);
	    teams->player = teams->player->next;
        }
        fprintf(outputFile, "_____________________________________\n");
        */
       teams=teams->next;
    }
}

/*
void displayTeam(Team *head)
{
	while (head!=NULL){
		printf ("%d ", head->);
		head=head->next;
	}
	printf("\n");
}

*/

void deleteTeam(Team **head)
{
    Team *newNode;
    while(*head!=NULL)
    {
        newNode=(*head)->next;
        free(*head);
        *head=newNode;
    }

    *head=NULL;
}


//************************** TASK 2 *******************************

int calculateTeamScore(Player *player)
{
    int sum = 0;
    Player *copy = (Player*)malloc(sizeof(Player));
    copy = player;
    while(copy != NULL)
    {
        sum = sum + copy->points;
        copy = copy->next;
    }
    return sum;
}

Team* calculateALLTeamScore(Team *team)
{
    Team *copy;
    copy = (Team*)malloc(sizeof(Team));
    copy = team;
    while(copy != NULL)
        {
            copy->score = calculateTeamScore(copy->player);
            copy = copy->next;
        }
    return team;
}

int calculateMinScore(Team *team)
{
    Team *copy;
    copy = (Team*)malloc(sizeof(Team));
    int minimum = 10000;
    copy = team;
    while(copy != NULL)
    {
        if(copy->score < minimum)
            minimum = copy->score;
        copy = copy->next;
    }
    return minimum;
}

void removeTeam(Team **team, int x)
{
    if(*team == NULL) return;
    Team *copy;
    //copy = (Team*)malloc(sizeof(Team));
    copy = *team;
    if(copy -> score == x){
        *team = (*team)->next;
        free(copy);
        return;
    }
    /*
    while(copy->next->score != x)
    {
        copy = copy->next;
    }
    Team* newNode=copy->next;
    free(copy);
    copy=newNode;
    */
   Team *prev;
   while(copy != NULL)
   {
        if(copy->score != x){
            prev = copy;
            copy = copy->next;
        }
        else
        {
            prev->next = copy->next;
            free(copy);
            return;
        }
   }
    //return;
}

int calculateNMin(int num)
{
    int x=1;
    while(x < num)
        x*=2;
    x/=2;
    return x;
}