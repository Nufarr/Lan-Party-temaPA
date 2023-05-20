#define SIZE 100
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
    float score;
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

void addAtBeginningPlayer(Player **head, char *firstName, char *secondName, int points)
{
	Player* newNode = (Player*)malloc(sizeof(Player));
	newNode->points = points;
    newNode->firstName = firstName;
    newNode->secondName = secondName;
	newNode->next = *head;
	*head = newNode;
}

void displayTeams(Team *teams, int numOfTeams, FILE *outputFile)
{
    while (teams!=NULL)
    {
        fprintf(outputFile, "%s\n", teams->teamName);
       teams=teams->next;
    }
}

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
            copy->score /= team->numOfPlayers;
            copy = copy->next;
        }
    return team;
}

float calculateMinScore(Team *team)
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
    return minimum;
}

void removeTeam(Team **team, float x)
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

int calculateNMax(int num)
{
    int x=1;
    while(x <= num)
        x*=2;
    x/=2;
    return x;
}

