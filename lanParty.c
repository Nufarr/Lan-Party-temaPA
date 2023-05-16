#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "player.h"
#include "stive.h"
#include "cozi.h"
#include "BST.h"
#include "tasks.h"

int main(int argc, char *argv[])
{
    FILE *inputFile, *cFile;
    cFile = fopen(argv[1], "rt");
    //cFile = fopen("c.in", "rt");
    if(cFile == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }
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

//************************** TASK 1 *******************************
    Team *teams;
    teams = NULL;
    int numOfTeams;
    if(cinput[0] == 1)
    task1(inputFile, &teams, &numOfTeams);
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
                while(top != NULL)
                {
                    addAtEnd(&top8, top->val); 
                    top = top->next;
                }
                Top8 *aux = top8;
                while(!isEmptyStack(winners))
                {
                    A = pop(&winners);
                    B = pop(&winners);
                    enQueue(match, A, B);
                }
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

    if(cinput[3] == 1)
    {
        Graph *graph;
        graph = (Graph*)malloc(sizeof(Graph));
        graph = NULL;
        graph = createBST(graph, top8);
        fprintf(outputFile, "\nTOP 8 TEAMS:\n");
        inorder(graph, outputFile);
    }
    fclose(outputFile);
    fclose(cFile);
    deleteTeam(&teams);
}
