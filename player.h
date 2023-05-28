#define SIZE 100
typedef int Data;

typedef struct Player
{
    int points;
    char* firstName;
    char* secondName;
    struct Player *next;
} Player;

typedef struct Team
{
    int numOfPlayers;
    float score;
    char* teamName;
    Player *player;
    struct Team *next;
} Team;

void addAtBeginningTeam(Team **head, int numofPlayers, char* teamName, Player *player) //adauga echipa la inceput
{
	Team* newNode = (Team*)malloc(sizeof(Team));
	newNode->numOfPlayers = numofPlayers;
    newNode->teamName = teamName;
	newNode->next = *head;
    newNode->player = player;
	*head = newNode;
}

void addAtBeginningPlayer(Player **head, char *firstName, char *secondName, int points) //adauga playeri la inceput
{
	Player* newNode = (Player*)malloc(sizeof(Player));
	newNode->points = points;
    newNode->firstName = firstName;
    newNode->secondName = secondName;
	newNode->next = *head;
	*head = newNode;
}

void displayTeams(Team *teams, int numOfTeams, FILE *outputFile) //afiseaza echipele
{
    while (teams!=NULL)
    {
        fprintf(outputFile, "%s\n", teams->teamName);
       teams=teams->next;
    }
}

void deleteTeam(Team **head) //sterge o echipa din lista
{
    Player *newPNode;
    while((*head)->player!=NULL)
        {
            newPNode=((*head)->player)->next;
            free((*head)->player->firstName);
            free((*head)->player->secondName);
            //free((*head)->player->points);
            free((*head)->player);
            (*head)->player = newPNode;
        }
    free((*head)->teamName);
    free(newPNode);
    free(*head);
}

void deleteAllTeams(Team **head) //sterge toate echipele din liste
{
    Team *newNode;
    while(*head!=NULL)
    {
        newNode=(*head)->next;
        deleteTeam(head);
        *head=newNode;
    }
    *head=NULL;
}


//************************** TASK 2 *******************************

int calculateNMax(int num) //calculeaza numarul maxim de forma 2^n
{
    int x=1;
    while(x <= num)
        x*=2;
    x/=2;
    return x;
}


int calculateTeamScore(Player *player)  //calculeaza scorul pentru o echipa
{
    int sum = 0;
    Player *copy;
    copy = player;
    while(copy != NULL)
    {
        sum = sum + copy->points;
        copy = copy->next;
    }
    return sum;
}

Team* calculateALLTeamScore(Team *team)  //calculeaza scorurile pentru toate echipe
{
    Team *copy;
    copy = team;
    while(copy != NULL)
        {
            copy->score = calculateTeamScore(copy->player);
            copy->score /= team->numOfPlayers;
            copy = copy->next;
        }
    return team;
}

float calculateMinScore(Team *team)  //calculeaza scorul minim din toate echipele
{
    Team *copy;
    copy = (Team*)malloc(sizeof(Team));
    float minimum = 10000;
    copy = team;
    while(copy != NULL)
    {
        if(copy->score < minimum)
            minimum = copy->score;
        copy = copy->next;
    }
    free(copy);
    return minimum;
}

void removeTeam(Team **team, float x) //sterge o echipa care are un scor dat
{
    if(*team == NULL) return;
    Team *copy;
    copy = *team;
    if(copy -> score == x){
        *team = (*team)->next;
        deleteTeam(&copy);
        return;
    }

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
            deleteTeam(&copy);
            return;
        }
   }
}


