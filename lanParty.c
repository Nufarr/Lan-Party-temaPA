#include "player.h"
#include "stive.h"
#include "cozi.h"

int main(int argc, char *argv[])
{
    Team *teams;
    teams = NULL;

    FILE *inputFile, *cFile;
    cFile = fopen(argv[1], "rt");
    //cFile = fopen("c.in", "rt");
    int *cinput;
    cinput = (int*)malloc(5*sizeof(int));
    for(int i = 0; i < 5; i++)
        fscanf(cFile, "%d ", &cinput[i]);

    inputFile = fopen(argv[2], "rt");
    //inputFile = fopen("d.in", "rt");
    if(inputFile == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }

    int numOfTeams;
    char *buffer;
    buffer = (char*)malloc(sizeof(char)*2);

    fscanf(inputFile, "%d", &numOfTeams);
    fgets(buffer , 2, inputFile);


    for(int i = 0; i < numOfTeams; i++)
    {
        int numOfPlayers;
        char *teamName;
        teamName = (char*)malloc(SIZE*sizeof(char));

        fscanf(inputFile, "%d", &numOfPlayers);
        fgets(buffer , 2, inputFile);
        fgets(teamName, SIZE, inputFile);

        Player *player;
        player = NULL;
        for(int j = 0; j < numOfPlayers; j++)
        {
            char* firstName;
            char* secondName;
            int points;
            firstName = (char*)malloc(sizeof(char));
            secondName = (char*)malloc(sizeof(char));
            fscanf(inputFile, "%s", firstName);
            fgets(buffer , 2, inputFile);
            fscanf(inputFile, "%s", secondName);
            fgets(buffer , 2, inputFile);
            fscanf(inputFile, "%d", &points);
            fgets(buffer , 2, inputFile);
            addAtBeginningPlayer(&player, firstName, secondName, points);
        }
        addAtBeginningTeam(&teams, numOfPlayers, teamName, player);   
    }

    fclose(inputFile);


    //   AFISARE

    FILE *outputFile;
    outputFile = fopen(argv[3], "wt");
    //outputFile = fopen("r.out", "wt");
    if(outputFile == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }

//************************** TASK 2 *******************************

    Team *copy;
    copy = teams;
    for(int i = numOfTeams-1; i>=0; i--)
    {
        copy->teamName[strlen(copy->teamName) - 2] = '\0';
        while(copy->teamName[strlen(copy->teamName)-1] == ' ')
            copy->teamName[strlen(copy->teamName)-1] = '\0';
        copy = copy->next;
    }

    if(cinput[1] == 1)
    {
        teams = calculateALLTeamScore(teams);
        int Nmin = calculateNMin(numOfTeams);
        while(numOfTeams > Nmin)
        {
            float minScore  = calculateMinScore(teams);
            removeTeam(&teams, minScore);
            numOfTeams--;
        }
    }
    if(cinput[0] == 1 || cinput[1] == 1)
    displayTeams(teams, numOfTeams, outputFile);
    //fprintf(outputFile, "\n");


//************************** TASK 3 *******************************

    Queue *match;
    match = createQueue(match);
    Stack *winners;
    winners = (Stack*)malloc(sizeof(Stack));
    winners = NULL;
    Stack *losers;
    losers = (Stack*)malloc(sizeof(Stack));
    losers = NULL;

    Top8 *top8;
    top8 = NULL;
    
    if(cinput[2] == 1)
    {
        int roundNum = 0;
        Team *copy;
        copy = teams;
        while(copy != NULL)
        {
            enQueue(match, copy, copy->next);
            copy = copy->next->next;
        }

        Team *A,*B;
        A = (Team*)malloc(sizeof(Team));
        B = (Team*)malloc(sizeof(Team));
        
        while(numOfTeams != 1)
        {
            roundNum ++;

            fprintf(outputFile, "\n--- ROUND NO:%d", roundNum);
            displayOpponents(match, outputFile);

            while(!isEmpty(match))
            {
                deQueue(&match, &A, &B);
                if(A->score <= B->score)
                {
                    push(&losers, A);
                    B->score++;
                    push(&winners, B);
                }
                else
                {
                    push(&losers, B);
                    A->score++;
                    push(&winners, A);   
                }
            }

            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d", roundNum);
            displayWinners(winners, outputFile);

            if(numOfTeams/2 == 8)
            {
                Stack *top;
                top = winners;
                //punem in top8 echipele din winners pt bst
                while(!isEmptyStack(top))
                {
                    addAtEnd(&top8, pop(&top)); 
                }
                Top8 *aux = top8;
                while(aux->next->next != NULL)
                {
                    enQueue(match, aux->val, aux->next->val);
                    aux = aux->next->next;
                }
                enQueue(match, aux->val, aux->next->val);
                numOfTeams/=2;
                deleteStack(&winners);
                continue;
            }
            numOfTeams/=2;
            deleteStack(&losers);
            while(!isEmptyStack(winners))
            {
                A = pop(&winners);
                B = pop(&winners);
                enQueue(match, A, B);
            }
            
       }
       deleteStack(&winners);
    }


    fclose(outputFile);
    fclose(cFile);
    deleteTeam(&teams);
}
