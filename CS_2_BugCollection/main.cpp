// Dakota Mumford
// Bug class assignment

// *** NOTE: Code was provided as part of the assignment except for the TODO sections ***

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Bug.hpp"

using namespace std;

//TODO:write a function that prints all the contents of the 
//     bug array.  Use Bug::print() for each bug. 
void printBugs(vector<Bug> bugs)
{
	for (int i = 0; i < bugs.size(); i++)
	{
		bugs[i].print();
	}
}
//end of TODO

//TODO:write a function to bubble sort the contents of a
//     bug array based on the mass
void sortMass(vector<Bug>& bugs)
{
	bool didSwap = false;
	do
	{
		didSwap = false;
		for (int i = 0; i < bugs.size() - 1; i++)
		{
			if (bugs[i].getMass() > bugs[i + 1].getMass())
			{
				swap(bugs[i], bugs[i + 1]);
				didSwap = true;
			}
		}
	} while (didSwap);
}
//end of TODO

int main()
{
	const int NUMBUGS = 5;
	//TODO: make a vector of NUMBUGS bugs
	vector<Bug> bugs(NUMBUGS);
	//end of TODO

	cout << endl << "-- Initial Bugs --" << endl << endl;
	printBugs(bugs);

	//TODO: add three more bugs to the vector
	for (int i = 0; i < 3; i++)
	{
		Bug newBug;
		bugs.push_back(newBug);
	}
	//end of TODO

	cout << endl << "-- Three More Bugs --" << endl << endl;
	printBugs(bugs);

	sortMass(bugs);

	cout << endl << "-- Sorted By Mass --" << endl << endl;
	printBugs(bugs);

	//TODO: get rid of the 5 bugs with the greatest mass
	for (int i = 0; i < 5; i++)
	{
		bugs.pop_back();
	}
	//end of TODO

	cout << endl << "-- Removed Five Biggest --" << endl << endl;
	printBugs(bugs);

	return 0;
}
