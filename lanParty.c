#include "player.h"

#define SIZE 100

int main(int argc, char *argv[])
{

    Team *teams;
    teams = NULL;

    FILE *inputFile, *cFile;
    cFile = fopen(argv[1]/*"c.in"*/, "rt");
    int *cinput;
    cinput = (int*)malloc(5*sizeof(int));
    for(int i = 0; i < 5; i++)
        fscanf(cFile, "%d ", &cinput[i]);

    inputFile = fopen(argv[2]/*"d.in"*/, "rt");
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
        if(teamName[strlen(teamName)-1] == '\n')
        teamName[strlen(teamName)-1] = '\0';
        
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
    outputFile = fopen(argv[3]/*"r.out"*/, "wt");
    if(outputFile == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }

    if(cinput[1] == 1)
    {
        teams = calculateALLTeamScore(teams);
        Team *copy;
        copy = teams;
        int Nmin = calculateNMin(numOfTeams);
        while(numOfTeams > Nmin)
        {
            int minScore  = calculateMinScore(teams);
            removeTeam(&teams, minScore);
            numOfTeams--;
        }
    }
    if(cinput[0] == 1 || cinput[1] == 1)
    displayTeams(teams, numOfTeams, outputFile);

    fclose(outputFile);
    fclose(cFile);
    deleteTeam(&teams);
}