void task1(FILE* inputFile, Team **t1teams, int *t1numOfTeams)
{
    Team *teams = *t1teams;
    int numOfTeams = *t1numOfTeams;
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

    //pentru spatiile in plus din checker
    Team *copy;
    copy = teams;
    for(int i = numOfTeams-1; i>=0; i--)
    {
        copy->teamName[strlen(copy->teamName) - 2] = '\0';
        while(copy->teamName[strlen(copy->teamName)-1] == ' ')
            copy->teamName[strlen(copy->teamName)-1] = '\0';
        copy = copy->next;
    }

    *t1teams = teams;
    *t1numOfTeams = numOfTeams;
}
