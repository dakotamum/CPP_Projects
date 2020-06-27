// Dakota Mumford
// Sorting Statistics Assignment

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

// function for generating a vector of random integers with a given size
vector<int> generateVectorOfRandomNumbers(int size)
{
	vector<int> aVector;
	for (int i = 0; i < size; i++)
	{
		aVector.push_back(rand() % 1000 + 1);
	}
	return aVector;
}

// function to print a vector
void printVector(vector<int> sortedVector)
{
	for (int i = 0; i < sortedVector.size(); i++)
	{
		cout << sortedVector[i] << " ";
	}
	cout << endl << endl;
}

// function to run a bubble sort on a vector, includes option to print
void bubbleSort(vector<int> aVector, bool print = false)
{
	bool didSwap = false;
	do
	{
		didSwap = false;
		for (int i = 0; i < aVector.size() - 1; i++)
		{
			if (aVector[i] > aVector[i + 1])
			{
				swap(aVector[i], aVector[i + 1]);
				didSwap = true;
			}
		}
	} while (didSwap);
	if (print)
		printVector(aVector);
}

// function to run a selection sort on a vector, includes option to print
void selectionSort(vector<int> aVector, bool print = false)
{
	for (int i = 0; i < aVector.size(); i++)
	{
		int minIndex = i;
		int newMin = minIndex;
		bool foundMin = false;
		for (int j = i + 1; j < aVector.size(); j++)
		{

			if (aVector[j] < aVector[newMin])
			{
				foundMin = true;
				newMin = j;
			}
		}

		if (foundMin)
		{
			swap(aVector[minIndex], aVector[newMin]);
		}
	}
	if (print)
		printVector(aVector);
}

void timedSort(vector<int> aVector)
{
	chrono::time_point<chrono::high_resolution_clock> bubstart = chrono::high_resolution_clock::now();
	bubbleSort(aVector);
	chrono::time_point<chrono::high_resolution_clock> bubend = chrono::high_resolution_clock::now();
	chrono::duration<double> bubbleSortTime = bubend - bubstart;

	chrono::time_point<chrono::high_resolution_clock> selstart = chrono::high_resolution_clock::now();
	selectionSort(aVector);
	chrono::time_point<chrono::high_resolution_clock> selend = chrono::high_resolution_clock::now();
	chrono::duration<double> selectionSortTime = selend - selstart;

	cout << endl;
	cout << left << setw(30) << "Number of Items: " << aVector.size() << endl;
	cout << left << setw(30) << "Bubble Sort Time: " << bubbleSortTime.count() << " seconds" << endl;
	cout << left << setw(30) << "Selection Sort Time: " << selectionSortTime.count() << " seconds" << endl;
	cout << endl;
}

// main function tests the sorting times of the bubble and selection
// sort algorithms and prints the output the the console
int main()
{
	// seed the random number generator
	srand(static_cast<int>(time(0)));

	// test vector
	vector<int> vectorHector{ 1, 5, 4, 9, 10, 2, 3, 6, 7, 8 };

	// test the sorts and print the output to make sure they work
	bubbleSort(vectorHector, true);
	selectionSort(vectorHector, true);

	// test sorting times starting with vectors of size 100 to 1000
	// by increments of 100
	for (int i = 100; i < 1001; i += 100)
	{
		vector<int> aVector = generateVectorOfRandomNumbers(i);
		timedSort(aVector);
	}

	return 0;
}
