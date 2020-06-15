// Dakota Mumford
// Parallel Mandelbrot Project

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

// function that returns a color based on the mandelbrot iteration value
int gimmeColor(complex<double>complexNum){
    int color=0;
    complex<double>currentMandValue(0,0);
    for(int i = 0; i < 25; i++){
        complex<double> mand = currentMandValue * currentMandValue + complexNum;
        currentMandValue = mand;
        if(abs(currentMandValue)>2)
        {
            color = (25 - i)*10;
            break;
        }
    }
    return color;
}

// mpi program that creates a mandelbrot image with the processes in parallel
int main (int argc, char **argv){
    int pid, np, data;
    double coordinates[3];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &pid);
    MPI_Comm_size(MCW, &np);

    // master node’s code to execute
    if (pid == MASTAH)
    {
        // write to ppm file
        ofstream myPicture ;
        myPicture.open("image.ppm");
        myPicture << "P3\n512 512\n255\n\n";

        // get user input for the zoom window
        printf ("Please tell me about the box you want to see :\nRe0: ");
        cin >> coordinates [0]; printf ( " Im0 : " ) ; cin >> coordinates [1];
        printf ("Re1: ");
        cin >> coordinates [2];

        // send coordinates to the other processes
        MPI_Bcast(coordinates, 3, MPI_DOUBLE, MASTAH, MCW);

        // start the clock
        auto start = std::chrono::system_clock::now();

        // fill master’s chunk of the picture with mandelbrot color values
        int rowmin = (512/np) * pid;
        int rowmax = (512/np) * pid + 512/np;
        int mandelbrot2dArray[512/np][512];
        for (int i = rowmin; i < rowmax; i ++)
        {
            for (int j = 0; j < 512; j++)
            {
                complex<double> compNum(coordinates[0] + (j*(coordinates[2] - coordinates[0])/512), coordinates[1] - (i *(coordinates[2] - coordinates[0])/512) ) ;
                mandelbrot2dArray[i-rowmin][j] = gimmeColor(compNum);
            }
        }

        // print master’s chunk of the picure to image.ppm file
        for (int i = 0; i < 512/np; i++)
        {
            for (int j = 0; j < 512; j++)
            {
                myPicture << ’0 ’ << " " << ’0 ’ << " " << mandelbrot2dArray[i][j] << " ";
            }
            myPicture << endl;
        }
        myPicture.close();

        // send message to the next process to trigger them to print to the image.ppm file
        MPI_Send(&pid, 1, MPI_INT, pid+1, 1, MCW);

        // receive message from last process indicating everyone is done and the master can stop timing
        MPI_Recv (&data , 1, MPI_INT, np-1, 1, MCW, MPI_STATUS_IGNORE);

        // stop the clock and calculate processing time
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> time = end - start;

        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout<<"\nprocessing time : " << time.count() << " s \n";
    }

    // every other processor’s code to execute
    else
    {
        // receive the coordinates from the master process and initialize mandelbrot2dArray
        MPI_Bcast(coordinates, 3, MPI_DOUBLE, MASTAH, MCW);
        int mandelbrot2dArray [512/np][512];

        int rowmin = (512/np) * pid;
        int rowmax = (512/np) * pid + 512/np;

        // fill mandelbrot2dArray with mandelbrot color values
        for ( int i = rowmin; i < rowmax; i++)
        {
            for ( int j = 0; j < 512; j++)
            {
                complex<double> compNum(coordinates[0] + (j *(coordinates[2] - coordinates[0])/512) ,coordinates[1] - ( i *( coordinates[2] - coordinates[0])/512) ) ; mandelbrot2dArray[i - rowmin][j] = gimmeColor(compNum);
            }
        }

        // receive the trigger for this process to start printing to image.ppm file
        MPI_Recv(&data, 1, MPI_INT, pid - 1, 1, MCW, MPI_STATUS_IGNORE);
        ofstream myPicture;
        myPicture.open( "image.ppm", ios::app);

        // output the mandelbrot2dArray to image . ppm file
        for (int i = 0; i < 512/np ; i++)
        {
            for (int j = 0; j < 512; j++)
            {
                myPicture << ’0 ’ << " " << ’0 ’ << " " << mandelbrot2dArray [i][j] << " ";
            }
            myPicture << endl;
        }
        myPicture.close();
        if (pid == np - 1) // check if this process is the last one . If so , send message to master . If not , send the okay
        { // for the next process to output to image.ppm
            MPI_Send(&pid,1 ,MPI_INT ,0 ,1 ,MCW);
        }
        else
        {
            MPI_Send(&pid, 1 ,MPI_INT ,pid + 1 ,1 ,MCW);
        }
    }

    MPI_Finalize();
    return 0;
}
