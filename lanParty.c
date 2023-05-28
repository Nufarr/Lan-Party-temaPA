#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "player.h"
#include "cozi.h"
#include "stive.h"
#include "Top8.h"
#include "BST.h"
#include "AVL.h"
#include "tasks.h"

int main(int argc, char *argv[])
{
    FILE *inputFile, *cFile;
    //Deschidem fisierul c.in
    cFile = fopen(argv[1], "rt");
    if(cFile == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    int *cinput;
    cinput = (int*)malloc(5*sizeof(int));
    for(int i = 0; i < 5; i++)
        fscanf(cFile, "%d ", &cinput[i]);

    //Deschidem fisierul d.in
    inputFile = fopen(argv[2], "rt");
    if(inputFile == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    
    //Deschidem fisierul r.out
    FILE *outputFile;
    outputFile = fopen(argv[3], "wt");
    if(outputFile == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }


//************************** TASK 1 *******************************
    Team *teams = NULL;
    int numOfTeams;
    if(cinput[0] == 1) //daca cerinta e 1
    task1(inputFile, &teams, &numOfTeams);
    fclose(inputFile);

//************************** TASK 2 *******************************

    if(cinput[1] == 1) //daca cerinta e 2
    {
        task2(&teams,&numOfTeams);
    }

    //Afisare Task 1 + Task 2
    if(cinput[0] == 1 || cinput[1] == 1)
    displayTeams(teams, numOfTeams, outputFile);
    //fprintf(outputFile, "\n");


//************************** TASK 3 *******************************

    Top8 *top8 = NULL; //lista de Top8
    
    if(cinput[2] == 1) //daca cerinta e 3
    {
        task3(&top8, &teams, numOfTeams, outputFile);
    }

//************************** TASK 4 *******************************
    Top8 *top8ord = NULL; //lista de Top 8 echipe ordonate descrescator
    if(cinput[3] == 1) //daca cerinta e 4
    {
        task4(top8, &top8ord, outputFile);
    }
    deleteTop8(&top8);

//************************** TASK 5 *******************************
    if(cinput[4] == 1) //daca cerinta e 5
    {
        task5(top8ord, outputFile);
    }
    deleteTop8(&top8ord);
    deleteAllTeams(&teams);
    fclose(outputFile);
    fclose(cFile);
    free(cinput);
}
