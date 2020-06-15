//Dakota Mumford
//Parallel Integer Sort Project

#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <array>
#define MCW MPI_COMM_WORLD
#define MASTAH 0

using namespace std;

// master/slave integer sort
int main(int argc, char **argv)
{
    int pid, np;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &pid);
    MPI_Comm_size(MCW, &np);
    if(pid == MASTAH){ // master node
        // unsorted array
        int masterArraySize = 12;
        int masterArray[masterArraySize] = {7, 3, 5, 2, 4, 1, 30, 18, 11, 21, 4, 3};
        printf("Unsorted array: ");
        for(int i = 0; i < masterArraySize; i++)printf("%i ", masterArray[i]);
        printf("\n\n");
        int numArrays = np - 1;
        int elementsPerArray = masterArraySize / numArrays;
        int indexOfMasterArray = 0;
        // send arrays to slave nodes
        for(int i = 0; i < numArrays; i++){
            data = elementsPerArray;
            MPI_Send(&data, 1, MPI_INT, i+1, i+1, MCW);
            for(int j = 0; j < elementsPerArray; j++){
                data = masterArray[indexOfMasterArray];
                MPI_Send(&data, 1, MPI_INT, i+1, i+1, MCW);
                indexOfMasterArray++;
            }
        }
        // set up 2D array to receive sub-sorted arrays from processes
        int receivingMatrix[numArrays][elementsPerArray];
        for(int i = 0; i < numArrays; i++){
            for(int j = 0; j < elementsPerArray; j++){
                MPI_Recv(&data, 1, MPI_INT, i+1, i+1, MCW, MPI_STATUS_IGNORE);
                receivingMatrix[i][j] = data;
            }
        }
        printf("Sorted arrays returned from the other processes: \n");
        for(int i = 0; i < numArrays; i++){
            for(int j = 0; j < elementsPerArray; j++){
                printf("%i ", receivingMatrix[i][j]);
            }
            printf("\n");
        }
        // set up two arrays to alternate holding the merged array in progress
        int mergedArray2[masterArraySize];
        for (int i = 0; i < elementsPerArray; i++) mergedArray2[i] = receivingMatrix[0][i];
        int mergedArray1[masterArraySize];
        int mergedSortArraySize = elementsPerArray;
        // cycle through rows in 2D array and merge with the arrays
        for(int i = 0; i < numArrays - 1; i++){
            int mergedSortArray[mergedSortArraySize];
            if(i %2 == 0)
                for(int j = 0; j < mergedSortArraySize; j++) mergedSortArray[j] =
                    mergedArray2[j];
            else
                for(int j = 0; j < mergedSortArraySize; j++) mergedSortArray[j] =
                    mergedArray1[j];
            int newMergedSortArray[masterArraySize];
            int index1 = 0;
            int index2 = 0;
            int currentMergeIndex = 0;
            bool index1Done = false;
            bool index2Done = false;
            printf("\nComparing these two arrays: \n");
            for(int j = 0; j < mergedSortArraySize; j++)printf("%i ", mergedSortArray[j]);
            printf("\n");
            for(int j = 0; j < elementsPerArray; j++)printf("%i ", receivingMatrix[i+1][j]);
            printf("\n");
            while(index1 < mergedSortArraySize || index2 < elementsPerArray)
            {
                if(index1Done){
                    newMergedSortArray[currentMergeIndex] =
                        receivingMatrix[i+1][index2];
                    index2++;
                    currentMergeIndex++;
                }
                else if(index2Done){
                    newMergedSortArray[currentMergeIndex] =
                        mergedSortArray[index1];
                    index1++;
                    currentMergeIndex++;
                }
                else
                {
                    if(mergedSortArray[index1] <= receivingMatrix[i+1][index2]){
                        newMergedSortArray[currentMergeIndex] =
                            mergedSortArray[index1];
                        index1++;
                        if(index1 >= mergedSortArraySize)index1Done = true;
                    }
                    else
                    {
                        newMergedSortArray[currentMergeIndex] =
                            receivingMatrix[i+1][index2];
                        index2++;
                        if(index2 >= elementsPerArray)index2Done = true;
                    }
                    currentMergeIndex++;
                }
            }
            mergedSortArraySize += elementsPerArray;
            printf("merged array: "); for(int i = 0; i < mergedSortArraySize; i++)
                printf("%i ", newMergedSortArray[i]);
            printf("\n");
            if(i %2 == 0)
                for(int j = 0; j < mergedSortArraySize; j++)mergedArray1[j] =
                    newMergedSortArray[j];
            else
                for(int j = 0; j < mergedSortArraySize; j++)mergedArray2[j] =
                    newMergedSortArray[j];
        }
        if(numArrays %2 == 0)
            for(int j = 0; j < masterArraySize; j++)masterArray[j] = mergedArray1[j];
        else
            for(int j = 0; j < masterArraySize; j++)masterArray[j] = mergedArray2[j];
        printf("\nFinal sorted array: ");
        for(int i = 0; i < masterArraySize; i++)printf("%i ", masterArray[i]);
        printf("\n");
    }
    else{ // slave node receives a sub array, sorts it, and sends it back to the master
        MPI_Recv(&data, 1, MPI_INT, 0, pid, MCW, MPI_STATUS_IGNORE);
        int numArrays = data;
        int mySubArray[numArrays];
        for(int i = 0; i < numArrays; i++){
            MPI_Recv(&data, 1, MPI_INT, 0, pid, MCW, MPI_STATUS_IGNORE);
            mySubArray[i] = data;
        }
        for (int i = 0; i < numArrays; i++){
            int flag = 0;
            for (int j = 0; j < numArrays - 1; j++)
            {
                if (mySubArray[j] > mySubArray[j+1])
                {
                    int temp = mySubArray[j];
                    mySubArray[j] = mySubArray[j+1];
                    mySubArray[j+1] = temp;
                    flag = 1;
                }
            }
            if(flag == 0){
                break;
            }
        }
        for (int i = 0; i < numArrays; i++){
            data = mySubArray[i];
            MPI_Send(&data, 1, MPI_INT, 0, pid, MCW);
        }
    }
    MPI_Finalize();
    return 0;
}
