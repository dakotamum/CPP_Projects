// Dakota Mumford
// Averaging Scores Assignment

#include <iostream>
using namespace std;

// main function takes user input for scores and averages them
int main()
{
	char selection = 'y';
	int numberOfValues = 0;
	int sum = 0;
	int score;

	cout << "Please enter a score: ";
	cin >> score;
	cout << endl;
	sum += score;
	numberOfValues++;

	// ask user for additional scores
	do
	{
		cout << "Do you have another score to enter? (y/n): ";
		cin >> selection;
		cout << endl;
		if (selection == 'y')
		{
			cout << "Please enter another score: ";
			cin >> score;
			cout << endl;
			sum += score;
			numberOfValues++;
		}
	} while (selection == 'y');

	// calculate the average and display the average and number of scores
	double average = static_cast<double>(sum) / numberOfValues;
	cout << "Average: " << average << endl;
	cout << "Number of Scores: " << numberOfValues << endl;
}
