#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void increaseDiceTreshold(int *, int, int, int);
int main() {
    int diceCount,diceFace, sumCount, diceSum, i, j;
    float diceProb;
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    //Get the number of dice and the number of faces
    printf("Enter the number of dices: ");
    scanf("%d", &diceCount);
    printf("Enter the number of faces: ");
    scanf("%d", &diceFace);

    //Allocate memory for the arrays
    diceProb = 1/pow(diceFace, diceCount);
    sumCount = (diceFace*diceCount) - diceCount+1;
    float **dice = (float **)calloc(sumCount, sizeof(float *));
    for(i = 0; i < sumCount; i++)
        dice[i] = (float *)calloc(2, sizeof(float));

    int *diceRoll = (int *)calloc(diceCount*diceFace, sizeof(int)); //Holds the dice rolls for every dice in order
    int *diceTreshold = (int *)calloc(diceCount, sizeof(int)); //Holds the tresholds for every dice to be used with diceRoll array: diceRoll[diceTreshold[1]] => rolled value of dice 1

    //Set the arrays
    for(i = 0; i < sumCount; i++)
        dice[i][0] = i+diceCount;
    for(i = 0; i < diceCount*diceFace; i++)
        diceRoll[i] = (i%diceFace)+1;
    
    //Calculate the probabilities
    for(i = 1; i <= pow(diceFace, diceCount); i++){
        increaseDiceTreshold(diceTreshold, diceCount, diceFace, i);
        diceSum = 0;
        for(j = 0; j < diceCount; j++){
            diceSum += diceRoll[diceTreshold[j]];
        }
        for(j = 0; j < sumCount; j++){
            if(diceSum == (int)dice[j][0]){
                dice[j][1] += diceProb;
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //Print the results
    printf("Sum\tProbability\n");
    for(i = 0; i < sumCount; i++){
        printf("%d\t%f\n", (int)dice[i][0], dice[i][1]);
    }
    float sumCheck = 0, maxProb = 0;
    int maxProbIndex = 0, secMaxProbIndex = -1;
    for(i = 0; i < sumCount; i++)
        sumCheck += dice[i][1];
    printf("Sum of all probabilities: %f\n", sumCheck);
    //Find the maximum probability
    for(i = 0; i<sumCount; i++){
        if(dice[i][1] > maxProb){
            maxProb = dice[i][1];
            maxProbIndex = i;
        }
        else if(dice[i][1] == maxProb)
            secMaxProbIndex = i;
    }
    if(secMaxProbIndex == -1)
        printf("Maximum Probability Value: %d\nProbability: %f\n", (int)dice[maxProbIndex][0], dice[maxProbIndex][1]);
    else if(secMaxProbIndex != -1)
        printf("Maximum Probability Values: %d, %d \nProbability: %f", (int)dice[maxProbIndex][0], (int)dice[secMaxProbIndex][0], dice[maxProbIndex][1]);
    printf("\nTime elapsed: %fs\n", cpu_time_used);

    //Free the allocated memory
    for(i = 0; i<sumCount; i++)
        free(dice[i]);
    free(dice);
    free(diceRoll);
    free(diceTreshold);

    return 0;
}
void increaseDiceTreshold(int *diceTreshold, int diceCount, int diceFace, int step) {
    int division = step, i;
    for(i = 0; i<diceCount; i++){
        diceTreshold[i] = ((division % diceFace)) + (i*diceFace);
        division /= diceFace;
    }
}