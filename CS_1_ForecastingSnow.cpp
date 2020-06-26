// Dakota Mumford
// Forecasting Snow Assignment

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;
// main function takes a minimum snowfall value and a maximum snowfall value and generates a snowfall
// forecast for the weeked with random values within the minimum and maximum range.
int main()
{
	int minSnowFall = 0, maxSnowFall = 0;
	string skiResortName;

	// seed the random number generator
	srand(time(0));

	// get user input for min and max snowfall
	cout << "I am your magical snowfall forecaster. I will give you the weekend snowfall amount; I just need a little help...\n";
	cout << "Please enter the minimum amount of snow expected: ", cin >> minSnowFall;
	cout << "Please enter the maximum amount of snow expected: ", cin >> maxSnowFall;
	cout << "Please enter the name of the ski resort: ", cin.ignore(), getline(cin, skiResortName);
	cout << endl;

	// print snowfall forecast with random values
	cout << "Snowfall Forecast for " << skiResortName << ":" << endl;
	cout << "========================================================\n";
	cout << "Snowfall for Friday: " << rand() % (maxSnowFall - minSnowFall) + minSnowFall << " inches" << endl;
	cout << "Snowfall for Saturday: " << rand() % (maxSnowFall - minSnowFall) + minSnowFall << " inches" << endl;
	cout << "Snowfall for Sunday: " << rand() % (maxSnowFall - minSnowFall) + minSnowFall << " inches" << endl;

	cout << "Have a great weekend!" << endl << endl;

	return 0;
}