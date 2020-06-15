//Dakota Mumford
//Parallel Hot Potato Project

#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#define MCW MPI_COMM_WORLD
using namespace std;
// time bomb program
int main(int argc, char **argv)
{
    // seed random time generator and randomize initial time and process
    srand((time(NULL)));
    int rank, size;
    int random_timer_number = rand()%30 + 10;
    int timer = random_timer_number;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    int random_initial_process = rand()%size;
    // first process to send the time bomb
    if(rank == random_initial_process && timer == random_timer_number)
    {
        printf("I am process %i! Here’s a timebomb with %i seconds on it.
        Passing it on!\n", rank + 1, timer);
        timer--;
        int random_process = rand()%size;
        // ensure this process sends to another random process
        while(random_process == rank)
        {
            random_process = rand()%size;
        }
        sleep(1);
        MPI_Send(&timer, 1, MPI_INT, random_process, 0, MCW);
    }
    while(timer >= 0)
    {
        // listen for incoming bomb
        MPI_Recv(&timer, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
        if(timer == 0)
        {
            printf("I am process %i! Oh darn. I received the bomb with %i
            seconds left. I lose!\n", rank + 1, timer);
            timer = -1;
            // send -1 to other processes to get past the MPI_Recv and out
            // of the while loop
            for(int i = 0; i < size; i++)
            {
                if(i != rank)
                {
                    MPI_Send(&timer, 1, MPI_INT, i, 0, MCW);
                }
            }
            break;
        }
        else if (timer > 0)
        {
            // decrement the time and send to another random process
            printf("I am process %i! I just received the bomb with %i
            seconds left. Passing it on...\n", rank + 1, timer);
            timer--;
            sleep(1);
            int random_process = rand()%size;
            while(random_process == rank)
            {
                random_process = rand()%size;
            }
            MPI_Send(&timer, 1, MPI_INT, random_process, 0, MCW);
        }
        else
        {
            break;
        }
    }
    MPI_Finalize();
    return 0;
}
