// Dakota Mumford
// IP Address Sorting Stats Assignment

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "IPRecord.hpp"

using namespace std;

// searches a vector for a value using the binary search algorithm
bool binarySearch(int searchKey, vector<IPRecord*> myVector, int& position)
{
	int lower = 0;
	int upper = (static_cast<int>(myVector.size()) - 1);
	bool found = false;
	while (!found && (lower <= upper)) {
		int middle = (lower + upper) / 2;

		if (myVector[middle]->getIP() == searchKey)
		{
			found = true;
			position = middle;
		}
		else if (myVector[middle]->getIP() < searchKey)
		{
			lower = middle + 1;
		}
		else
		{
			upper = middle - 1;
		}
	}
	return found;
}

// sorts a vector of IPRecord objects by frequency
void selectionSortByFrequency(std::vector<IPRecord*>& myVector)
{
	for (unsigned int start = 0; start < myVector.size() - 1; start++)
	{
		int minPos = start;
		for (unsigned int scan = start + 1; scan < myVector.size(); scan++)
		{
			if (myVector[scan]->getFrequency() < myVector[minPos]->getFrequency())
			{
				minPos = scan;
			}
		}
		std::swap(myVector[start], myVector[minPos]);
	}
}

// prints a report of number of IPRecords of different frequencies
// also increments the totalFrequencies variable
void printReport(vector<IPRecord*> myVector, int& totalFrequencies)
{
	int frequency = myVector[0]->getFrequency();
	int frequencyCounter = 0;
	for (unsigned int count = 0; count < myVector.size(); count++)
	{
		if (myVector[count]->getFrequency() == frequency)
		{
			frequencyCounter++;
		}
		else
		{
			int numFrequencies = frequency * frequencyCounter;
			totalFrequencies += numFrequencies;
			cout << left << setw(10) << frequencyCounter << setw(30) << " IPs with a frequency of " << frequency << endl;
			frequency = myVector[count]->getFrequency();
			frequencyCounter = 1;
		}
	}
	int numFrequenciesLast = frequency * frequencyCounter;
	totalFrequencies += numFrequenciesLast;
	cout << left << setw(10) << frequencyCounter << setw(30) << " IPs with a frequency of " << frequency << endl;
}

// main function reads in IP addresses (just numbers really) and creates a vector of IPRecord object
// it also cleans up dynamic memory allocation when finished
int main()
{
	ifstream fin;
	fin.open("input.txt");
	if (!fin)
	{
		cout << "File open error. Shutting down...\n\n";
		return 0;
	}

	int numIP;
	fin >> numIP;
	vector<IPRecord*> IP_Vector;

	// read in IP addresses and either increment frequencies of existing IPRecords or create new ones
	for (int i = 0; i < numIP; i++)
	{
		bool found = false;
		int IPValue;
		fin >> IPValue;
		int position = 0;
		
		found = binarySearch(IPValue, IP_Vector, position);
		if (found == true)
		{
			IP_Vector[position]->incrementFrequency();
		}
		else
		{
			int newHome = 0;
			for (; newHome < IP_Vector.size() && IP_Vector[newHome]->getIP() < IPValue; newHome++) {}
			IP_Vector.insert(IP_Vector.begin() + newHome, new IPRecord(IPValue));
		}
	}
		selectionSortByFrequency(IP_Vector);

		// ititilize totalFrequencies variable and call printReport function. then print total number of IP Addresses processed
		int totalFrequencies = 0;
		printReport(IP_Vector, totalFrequencies);
		std::cout << "\nNumber of IP Addresses Processed: " << totalFrequencies << endl;

		// clean up dynamic memory allocation
		for (unsigned int count = 0; count < IP_Vector.size(); count++)
		{
			delete IP_Vector[count];
		}

	fin.close();
	return 0;
}
