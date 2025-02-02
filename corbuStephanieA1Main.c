#include <stdio.h>
#include "givenA1.h"
#include <math.h>

int main(int argc, char *argv[]){
    int choice;
    struct Animal dataZoo[NUM_SAMPLES];
    struct Animal testData[NUM_TEST_DATA];
    int fileResult=0;
    int vector1[NUM_FEATURES]={1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int vector2[NUM_FEATURES]={1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    float euclideanDistance;
    int hammingDistance;
    float jaccardSimilarity;
    int newSample[NUM_FEATURES]={1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int kNearestNeighbors[NUM_SAMPLES];
    int k=5;
    int predictedClass;
    float accuracy;

    printf("Here is the menu - enter a number between 1 and 5: ");
    scanf("%d", &choice);

    //loops until user enters an invalid choice
    while (choice>=1 && choice<=5){

        if (choice==1){
            //if choice equals 1 then function 1 is called
            fileResult= readFromFile (argv[1], dataZoo);
            //if the function returns 1 meaning that the file was read successfully it then prints what the array which contains the information from the given file
            if (fileResult==1){
                for (int i=0; i<NUM_SAMPLES; i++){
                    printf("%s ",dataZoo[i].animalName);
                    for (int j=0; j<NUM_FEATURES; j++){
                        printf("%d ", dataZoo[i].features[j]);
                    }
                    printf("%d\n", dataZoo[i].classLabel);
                }
            }
        }
        //if choice equals 2 then function two is called
        else if (choice==2){
            //if fileResult equals 1 meaning that the file was successfully opened then function two is called and prints the euclidean distance, hamming distance and the jaccard similarity between vector1 and vector2
            if(fileResult==1){
                distanceFunctions (vector1, vector2, &euclideanDistance, &hammingDistance, &jaccardSimilarity);
                printf("Euclidean Distance: %f\n", euclideanDistance);
                printf("Hamming Distance: %d\n", hammingDistance);
                printf("Jaccard Similarity: %f\n",jaccardSimilarity);
            }
            //if choice 1 wasn't run before choice 2 then it exists the program
            else{
                break;
            }
        }

        //if choice equals 3 then function three is called
        else if(choice==3){
            //function 1 must be run before function three is called
            if (fileResult==1){
                //calls function 3 three different times which each distance function
                //it prints the k nearest neighbors with each distance function
                findKNearestNeighbors (dataZoo , newSample, k, 1, kNearestNeighbors);
                printf("Nearest neighbors for sample with Euclidean Distance: ");
                for (int i=0; i<k; i++){
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");
                findKNearestNeighbors (dataZoo , newSample, k, 2, kNearestNeighbors);
                printf("Nearest neighbors for sample with Hamming Distance: ");
                for (int i=0; i<k; i++){
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");
                findKNearestNeighbors (dataZoo , newSample, k, 3, kNearestNeighbors);
                printf("Nearest neighbors for sample with Jaccard Similarity: ");
                for (int i=0; i<k; i++){
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");
            }
            //function 1 must be run before function 3 if it is not then it exits the program
            else{
                break;
            }
        }

        //if choice equals 4 then function 4 is called
        else if (choice==4){
            //function 4 must be called after function 1 is called
            if (fileResult==1){
                //calls function 4 three times with each distance function the predicted class is then printed based on the distance function
                predictedClass= predictClass (dataZoo, newSample, 1, k);
                printf("The predicted class is: %d\n", predictedClass);
                predictedClass= predictClass (dataZoo, newSample, 2, k);
                printf("The predicted class is: %d\n", predictedClass);
                predictedClass= predictClass (dataZoo, newSample, 3, k);
                printf("The predicted class is: %d\n", predictedClass);
            }

            //if function 1 isn't run before function 2 then it exits the program
            else{
                break;
            }
        }

        //if choice equals 5 then function 5 is called
        else{
            //function 1 must be run before function
            if (fileResult==1){
                //calls function 5 three times with each distance function it then prints the accuracy of the predicted classes based on the distance function
                accuracy =findAccuracy (dataZoo, 1, testData, k);
                printf("The accuracy for the test data is %f\n", accuracy);
                accuracy =findAccuracy (dataZoo, 2, testData, k);
                printf("The accuracy for the test data is %f\n", accuracy);
                accuracy =findAccuracy (dataZoo, 3, testData, k);
                printf("The accuracy for the test data is %f\n", accuracy);
            }
            //if function 1 isn't called before function 5 it then exists the program
            else{
                break;
            }

        }

        printf("Here is the menu - enter a number between 1 and 5: ");
        scanf("%d", &choice);

    }

}
