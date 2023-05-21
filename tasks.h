//************************** TASK 1 *******************************
void task1(FILE* inputFile, Team **T1teams, int *T1numOfTeams)
{
    Team *teams = *T1teams;
    int numOfTeams = *T1numOfTeams;
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
            firstName = (char*)malloc(SIZE*sizeof(char));
            secondName = (char*)malloc(SIZE*sizeof(char));
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
    free(buffer);
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
    *T1teams = teams;
    *T1numOfTeams = numOfTeams;
}

//************************** TASK 2 *******************************
void task2(Team **T2teams, int *T2numOfTeams)
{
    Team *teams = *T2teams;
    int numOfTeams = *T2numOfTeams;
    teams = calculateALLTeamScore(teams);
        int Nmax = calculateNMax(numOfTeams);
        while(numOfTeams > Nmax)
        {
            float minScore  = calculateMinScore(teams);
            removeTeam(&teams, minScore);
            numOfTeams--;
        }
    *T2teams = teams;
    *T2numOfTeams = numOfTeams;
}

//************************** TASK 3 *******************************
Top8 *createTop8(Top8 *top8, Stack **winners, Queue **match)
{
    Stack *top;
    top = *winners;
    //punem in top8 echipele din winners pt bst
    while(top != NULL)
    {
        pushTop8(&top8, top->val->teamName, top->val->score); 
        top = top->next;
    }
                
    while(!isEmptyStack(*winners))
    {
        Team *A = pop(winners);
        Team *B = pop(winners);
        enQueue(*match, A, B);
    }

    return top8;
}

void task3(Top8 **T3top8,Team **T3teams, int numOfTeams, FILE *outputFile)
{
    Team *teams = *T3teams;
    Top8 *top8 = *T3top8;
    Queue *match = NULL;
        match = createQueue(match, teams);
        Stack *winners = NULL;
        Stack *losers = NULL;
        int roundNum = 0;
        createMatches(match, teams);
        Team *A = NULL,*B = NULL;
        
        while(numOfTeams != 1)
        {
            roundNum ++;
            fprintf(outputFile, "\n--- ROUND NO:%d", roundNum);
            displayOpponents(match, outputFile);
            decideWinnersAndLosers(&match, &winners, &losers, &A, &B);
            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d", roundNum);
            displayWinners(winners, outputFile);

            if(numOfTeams/2 == 8)
            {
                top8 = createTop8(top8, &winners, &match);
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
       free(match); // a ramas o singura echipa
       //deleteAllTeams(T3teams);
       *T3top8 = top8;
}

//************************** TASK 4 *******************************
void task4(Top8 *top8, Top8 **top8ord, FILE *outputFile)
{
    Graph *bst;
    bst = (Graph*)malloc(sizeof(Graph));
    bst = NULL;
    bst = createBST(bst, top8);
    fprintf(outputFile, "\nTOP 8 TEAMS:\n");
    //inorder(bst, outputFile);
        
    inorder(bst, top8ord);
    Top8 *aux;
    aux = *top8ord;
    while(aux != NULL)
    {
        fprintf(outputFile, "%-33s -  %0.2f\n", aux->teamName, aux->score);
        aux = aux->next;
    }
    bst = deleteGraph(bst);
}

//************************** TASK 5 *******************************
void task5(Top8 *top8ord, FILE *outputFile)
{
    Graph *avl = NULL;
    while(top8ord != NULL)
    {
        avl = insertAVL(avl, top8ord);
        top8ord = top8ord->next;
    }
    fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE:\n");
    displayLvl2(avl, outputFile);
    avl = deleteGraph(avl);
}