// Dakota Mumford
// Lotoja Race Assignment

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// main function takes user input for the racer's time at each of the Lotoja
// race checkpoints and displays race stats over each interval
int main()
{
	// checkpoint distances from start (in miles)
	int checkPoint1 = 44;
	int checkPoint2 = 87;
	int checkPoint3 = 128;
	int checkPoint4 = 165;
	int checkPoint5 = 207;

	string racerName;
	// gather racer's time at each checkpoint
	int checkPoint1Time, checkPoint2Time, checkPoint3Time, checkPoint4Time, checkPoint5Time;

	cout << "Please enter your name: ", cin >> racerName;
	cout << "Please enter your time at each of the checkpoints (in minutes)...\n";
	cout << "Checkpoint 1: ", cin >> checkPoint1Time;
	cout << "Checkpoint 2: ", cin >> checkPoint2Time;
	cout << "Checkpoint 3: ", cin >> checkPoint3Time;
	cout << "Checkpoint 4: ", cin >> checkPoint4Time;
	cout << "Finish Line:  ", cin >> checkPoint5Time;
	cout << endl;

	// calculate distances between checkpoints and the speeds in miles per hour
	int interval1Distance = checkPoint1;
	int interval2Distance = checkPoint2 - checkPoint1;
	int interval3Distance = checkPoint3 - checkPoint2;
	int interval4Distance = checkPoint4 - checkPoint3;
	int interval5Distance = checkPoint5 - checkPoint4;

	int interval1Time = checkPoint1Time;
	int interval2Time = checkPoint2Time - checkPoint1Time;
	int interval3Time = checkPoint3Time - checkPoint2Time;
	int interval4Time = checkPoint4Time - checkPoint3Time;
	int interval5Time = checkPoint5Time - checkPoint4Time;

	double interval1Speed = static_cast<double>(checkPoint1) * 60 / interval1Time;
	double interval2Speed = static_cast<double>(checkPoint2 - checkPoint1) * 60 / interval2Time;
	double interval3Speed = static_cast<double>(checkPoint3 - checkPoint2) * 60 / interval3Time;
	double interval4Speed = static_cast<double>(checkPoint4 - checkPoint3) * 60 / interval4Time;
	double interval5Speed = static_cast<double>(checkPoint5 - checkPoint4) * 60 / interval5Time;

	// calculate average speed
	double averageSpeed = static_cast<double>(checkPoint5) * 60 / checkPoint5Time;

	// display race stats for each interval
	cout << "Lotoja Race For " << racerName << "\n";
	cout << "================================================================================\n";
	cout << setw(10) << "Location" << setw(30) << "Distance (miles)" << setw(20) << "Time (minutes)" << setw(20) << "Speed (mph)" << endl;
	cout << endl;
	cout << setw(30) << setprecision(0) << fixed << left << setfill('.') << "Interval 1" << setw(20) << setfill(' ') << interval1Distance << setw(20) << interval1Time << setw(20) << setprecision(3) << fixed << interval1Speed << endl;
	cout << setw(30) << setprecision(0) << fixed << left << setfill('.') << "Interval 2" << setw(20) << setfill(' ') << interval2Distance << setw(20) << interval2Time << setw(20) << setprecision(3) << fixed << interval2Speed << endl;
	cout << setw(30) << setprecision(0) << fixed << left << setfill('.') << "Interval 3" << setw(20) << setfill(' ') << interval3Distance << setw(20) << interval3Time << setw(20) << setprecision(3) << fixed << interval3Speed << endl;
	cout << setw(30) << setprecision(0) << fixed << left << setfill('.') << "Interval 4" << setw(20) << setfill(' ') << interval4Distance << setw(20) << interval4Time << setw(20) << setprecision(3) << fixed << interval4Speed << endl;
	cout << setw(30) << setprecision(0) << fixed << left << setfill('.') << "Interval 5" << setw(20) << setfill(' ') << interval5Distance << setw(20) << interval5Time << setw(20) << setprecision(3) << fixed << interval5Speed << endl;
	cout << endl << "Average Speed: " << averageSpeed << " mph" << endl << endl;
	return 0;
}