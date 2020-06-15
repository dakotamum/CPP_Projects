// Dakota Mumford
// Parallel Global Sum Project

#include <iostream>
#include <mpi.h>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <complex>
#include <vector>
#include <chrono>

#define MCW MPI_COMM_WORLD
#define MASTAH 0

using namespace std ;

int main(int argc, char **argv){
    int pid, np;
    int data;
    int choice;
    int signal = 1;
    int integerVector[8] = {2, 3, 0, 4, 1, 2, 5, 1}; // vector that will be summed
    double t1, t2;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MCW, &pid);
    MPI_Comm_size(MCW, &np);

    int myInt = integerVector[pid]; // get user input for the method they would like to use
    if (pid == 0){
        printf ( " Please select a method for computing the global sum :\n1. Slave - master method \n2. Binary tree-ish method \n3. Ring method \n");
        cin >> choice ;
        MPI_Bcast(&choice, 1, MPI_INT, 0, MCW); // send the choice to the other processes
    }
    else {
        MPI_Bcast(&choice, 1, MPI_INT, 0, MCW);
    }

    switch (choice){
        case 1:
            // slave - master method
            if(pid !=0){
                MPI_Send (&myInt, 1, MPI_INT, 0, 1, MCW);
            }
            else
            {
                t1 = MPI_Wtime();

                for(int i = 1; i < np; i ++){
                    MPI_Recv(&data, 1, MPI_INT, i, 1, MCW, MPI_STATUS_IGNORE);
                    myInt += data;
                }
                t2 = MPI_Wtime();
                printf("The global sum is %i.\n" , myInt);
                printf("The processing time was %f seconds \n" , t2 - t1);
            }
            break;

        case 2: // binary tree-ish method
            if(pid == 0){
                t1 = MPI_Wtime() ; // start time
                MPI_Bcast(&signal ,1 ,MPI_INT ,2 ,MCW); // send the okay for the other processes to do their thang
            }
            else{
                MPI_Bcast(&signal, 1, MPI_INT, 2, MCW);
            }
            for (int i = 0; i < log2(np); i++){
                if(pid % static_cast<int>((pow(2, i + 1))) == 0){
                    if(pid == 0){t1 = MPI_Wtime();}
                    MPI_Recv(&data, 1, MPI_INT, pid + static_cast<int>(pow(2, i)),1 ,MCW , MPI_STATUS_IGNORE);
                    myInt += data;
                    if(i == log2(np) - 1){
                        printf("The global sum is %i.\n",myInt);
                        if(pid == 0){
                            t2 = MPI_Wtime();
                            printf("The processing time was %f seconds.\n", t2 - t1);
                        }
                    }
                }
                else {
                    MPI_Send(&myInt, 1,MPI_INT ,pid - static_cast<int>(pow(2, i)),1 , MCW);
                    break;
                }
            }

            break;

        case 3: // pass-along method
            if (pid == 0){
                MPI_Recv(&signal, 1, MPI_INT, np - 1, 1, MCW, MPI_STATUS_IGNORE); // wait for the okay
                MPI_Send(&myInt, 1, MPI_INT, pid + 1, 1, MCW); // initiate the summing in the ring
            }
            else{
                if( pid == np - 1) {
                    t1 = MPI_Wtime(); // start timing from last process in ring
                    MPI_Send(&signal, 1, MPI_INT, 0, 1, MCW);
                }
                MPI_Recv(&data, 1, MPI_INT, pid - 1, 1, MCW, MPI_STATUS_IGNORE);
                myInt += data;
                if(pid == np - 1){
                    printf("The global sum is %i.\n", myInt);
                    t2 = MPI_Wtime();
                    printf( "The processing time was %f seconds.\n", t2 - t1);
                }
                else {
                    MPI_Send(&myInt, 1, MPI_INT, pid + 1, 1, MCW);
                }
            }
            break ;
    }

    MPI_Finalize();
    return 0;
}
