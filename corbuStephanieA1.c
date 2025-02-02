#include <stdio.h>
#include "givenA1.h"
#include <math.h>

//Task 1
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){
    int lineNum=0;
    FILE *fptr;
    //opens file that was passed into the function in the read mode
    fptr=fopen (fName, "r");

    //if there was an error in opening the file then the function returns -1
    if (fptr==NULL){
        printf("Error opening file\n");
        return -1;
    }

    //otherwise if the file opens then the function reads the contents of the file and adds the information into the array passed into the function until the end of the file is reached. The function then returns 1. 
    else{

        while (!feof(fptr)){
            fscanf(fptr, "%s ", dataZoo[lineNum].animalName);
            for (int i=0; i<NUM_FEATURES; i++){
                fscanf(fptr,"%d", &dataZoo[lineNum].features[i]);
            }
            fscanf(fptr,"%d", &dataZoo[lineNum].classLabel);
            lineNum++;
        }

        fclose(fptr);

        return 1;
    }
}


//Task 2
void distanceFunctions (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclideanDistance, int * hammingDistance, float * jaccardSimilarity){
    int num1Matches=0;
    int num0Matches=0;
    float euc=0;
    int ham=0;
    float jac=0;

    //this function calculates the distance between two vectors with three different equations.

    //calculates the euclidean distance between vector1 and vecotr2 given the formula provided
    for (int i=0; i<NUM_FEATURES; i++){
        euc+=pow(vector1[i]-vector2[i],2);
    }
    euc=sqrt(euc);


    //calculates the hamming distance between vector1 and vecotr2 given the formula provided
    for (int i=0; i<NUM_FEATURES; i++){
        if (vector1[i]!=vector2[i]){
            ham++;
        }
    }

    //calculates the jaccard similarity between vector1 and vecotr2 given the formula provided
    for (int i=0; i<NUM_FEATURES; i++){
        if (vector1[i]==1 && vector2[i]==1){
           num1Matches++;
        }
        if(vector1[i]==0 && vector2[i]==0){
            num0Matches++;
        }
    }

    jac=(float)num1Matches/(NUM_FEATURES-num0Matches);
    //returns the values of euclidean distance, hamming distance and jaccard similarity using call by reference.
    *euclideanDistance=euc;
    *hammingDistance=ham;
    *jaccardSimilarity=jac;
}

//Task 3
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){
   float euclideanDistance=0;
   float distances[NUM_SAMPLES];
   int hammingDistance=0;
   int num1Matches=0;
   int num0Matches=0;
   float jaccardSimilarity;
   int indicies[NUM_SAMPLES];
   int j=0;


    //this checks if the value of k is valid
    if(k>NUM_SAMPLES){
        k=NUM_SAMPLES;
    }

    //this for loop populates the array indicies
    for (int i=0; i<NUM_SAMPLES; i++){
        indicies[i]=j;
        j++;
    }


    //if whichDistanceFunction is equal to 1, it populates the array distances with the distances between newSample and dataZoo.features using euclidean distance
    if (whichDistanceFunction==1){
        for (int i=0; i<NUM_SAMPLES; i++){
            for (int j=0; j<NUM_FEATURES; j++){
                euclideanDistance+=pow(newSample[j]-dataZoo[i].features[j],2);
            }
            euclideanDistance=sqrt(euclideanDistance);
            distances[i]=euclideanDistance;
            euclideanDistance=0;
        }
    }


    //if whichDistanceFunction is equal to 1, it populates the array distances with the distances between newSample and dataZoo.features using hamming distance
    else if (whichDistanceFunction==2){
        for (int i=0; i<NUM_SAMPLES; i++){
           for (int j=0; j<NUM_FEATURES; j++){
                if (newSample[j]!=dataZoo[i].features[j]){
                    hammingDistance++;
                }
            }
            distances[i]=hammingDistance;
            hammingDistance=0;
        }

    }

    //if whichDistanceFunction is equal to 1, it populates the array distances with the distances between newSample and dataZoo.features using jaccards similarity
    else{
        for(int i=0; i<NUM_SAMPLES; i++){
            for (int j=0; j<NUM_FEATURES; j++){
                if (newSample[j]==1 && dataZoo[i].features[j]==1){
                    num1Matches++;
                }
                if(newSample[j]==0 && dataZoo[i].features[j]==0){
                    num0Matches++;
                }
            }
            jaccardSimilarity= (float)num1Matches/(NUM_FEATURES-num0Matches);
            distances[i]=jaccardSimilarity;
            num1Matches=0;
            num0Matches=0;
            jaccardSimilarity=0;
        }
    }


    //if distance function is equal to 1 or 2 then it sorts the distances in increasesing order and it sorts the indicies array based in the distances array
    if (whichDistanceFunction==1 || whichDistanceFunction==2){
        //this sorting is insertion sort found on geeksforgeeks.org
        //https://www.geeksforgeeks.org/insertion-sort-algorithm/
        for (int i = 1; i < NUM_SAMPLES; ++i) {
            float key = distances[i];
            float key2 = indicies[i];
            int j = i - 1;
            while (j >= 0 && distances[j] > key) {
                distances[j + 1] = distances[j];
                indicies[j+1] = indicies[j];
                j = j - 1;
            }
            distances[j + 1] = key;
            indicies[j + 1 ] = key2;
        }

    }

    //if whichDistanceFunction is equal to 3 it then sorts the distances in decreasing order and sorts the indicies array based on the distances array
    else{
	//this sorting is selection sort in desending order found on geeksforgeeks.org
        //https://www.geeksforgeeks.org/c-program-to-sort-the-elements-of-an-array-in-descending-order/
        for (int i = 0; i < NUM_SAMPLES - 1; i++) {
            int max = i;
            for (int j = i + 1; j < NUM_SAMPLES; j++) {
                if (distances[j] > distances[max]){
                    max = j;
                }
            }
            if (max!= i) {
                float temp = distances[max];
                float temp2 = indicies[max];
                distances[max] = distances[i];
                indicies[max] = indicies[i];
                distances[i] = temp;
                indicies[i] = temp2;
            }
        }
    }

    //this for loop populates the array kNearestNeighbors with the first k elements in the indicies array
    for (int i=0; i<k; i++){
        kNearestNeighbors[i]=indicies[i];
    }

}

//task 4
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES],int whichDistanceFunction, int k){
    int kNearestNeighbors [NUM_SAMPLES];
    int maxcount = 0;
    int mostFrequentClass=0;
    int classes[k];

    //this calls the third function
    findKNearestNeighbors (dataZoo , newSample, k, whichDistanceFunction, kNearestNeighbors);

    //this for loop populates an array called classes with the classes of each of the k nearest neighbors
    for (int i=0; i<k; i++){
        classes[i]=dataZoo[kNearestNeighbors[i]].classLabel;
    }

    //this for loop loops through the array classes and finds the most frequent class
    for (int i = 0; i < k; i++) {
        int count = 0;
        for (int j = 0; j < k; j++) {
            if (classes[i] == classes[j]){
                count++;
            }
        }
        //if too classes are equally as frequent then it takes the lowest class as the predicted class
        if (count >= maxcount) {
            if(count==maxcount){
                if(classes[i]<mostFrequentClass){
                    mostFrequentClass=classes[i];
                }
            }
            else{
                maxcount = count;
                mostFrequentClass= classes[i];
            }

        }
    }
    //the function then returns the predicted class
    return mostFrequentClass;
}

float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k){
    int class;
    int correctPredictions=0;
    float accuracy;
    FILE *fptr;
    //opens the file testData.csv in the read mode
    fptr=fopen("testData.csv","r");
    char input[50];
    char * token;

    //if the file couldn't be open the function returns -1
    if(fptr==NULL){
        printf("Could not open file");
        return -1.00;
    }

    //if the file does open then this for loop populates the array testData with the contents from the testData.csv file
    else{

        for (int a=0; a<NUM_TEST_DATA; a++){
            fgets(input,50,fptr);

            token = strtok(input, ",");
            strcpy(testData[0].animalName, token);

            for (int b=0; b<NUM_FEATURES; b++){
                token= strtok(NULL, ",");
                testData[a].features[b]= atoi(token);
            }

            token =strtok(NULL, ",");
            testData[a].classLabel = atoi(token);
        }

        //this checks if k is valid
        if (k>NUM_TEST_DATA){
            k=NUM_TEST_DATA;
        }

        //this for loops calls the fourth function and predicits the class of each of the samples in testData
        for (int i=0; i<NUM_TEST_DATA; i++){
            class=predictClass ( dataZoo, testData[i].features, whichDistanceFunction, k);
            printf("%d ", class);
            if (class==testData[i].classLabel){
                //if the class prediction is correct the number of correct predictions increases by 1
                correctPredictions++;
            }
        }
        printf("\n%d\n", correctPredictions);
        printf("%d\n", NUM_TEST_DATA);

        //calculates the accuracy by dividing the number of correct predictions of the num of samples
        accuracy = (float)correctPredictions / NUM_TEST_DATA;
        //this function returns the accuracy
        return accuracy;
    }
}
