// Dakota Mumford
// Word Ladder Project

#include "WordLadderList.hpp"
#include <iostream>
#include <stdio.h>

// Overloaded constructor takes the first word and second word specified by the user 
// and reads in a dictionary of words of the same length
WordLadderList::WordLadderList(string word1, string word2)
{
	// initialize pointers and first and second words
	head = nullptr;
	temp = nullptr;
	firstWord = word1;
	secondWord = word2;

	// read in dictionary
	ifstream fin("dictionary.txt");
	cout << "Reading in dictionary..." << endl;
	while (!fin.eof())
	{
		string word;
		fin >> word;
		if(word.size() == firstWord.size())
			dictionary.push_back(word);
	}
	fin.close();
}

// add method adds a new node to the end of a linked list
void WordLadderList::add(vector<string> aLadder)
{
	if (head == nullptr) // check if the list is empty
	{
		head = new Node(aLadder);
	}
	else
	{
		Node* tempNode = head;
		while (tempNode->next != nullptr)
		{
			tempNode = tempNode->next;
		}
		tempNode->next = new Node(aLadder);
	}
}

// findLadder method finds the shortest word ladder between
// the two words specified
void WordLadderList::findLadder()
{
	// TO DO: Validate the second word is in the dictionary
	cout << endl << "Processing..." << endl;
	vector<string> firstVector;
	vector<string> currentVector;
	firstVector.push_back(firstWord);
	currentVector = firstVector;
	add(currentVector);

	bool pathFound = false;		// flag for keeping track if the word ladder has been found
	temp = head;
	do
	{
		vector<string> currentVector = temp->data;    // initialize first vector of words to explore
		string wordOfInterest = currentVector[currentVector.size() - 1]; // initialize first word to compare with
		bool foundWordToDelete = false;	 // flag for keeping track of when a used word needs to be removed from the dictionary
		int indexToDelete;
		for (int i = 0; i < dictionary.size(); i++)
		{
			if (oneOff(wordOfInterest, dictionary[i]))	// check if the word in the dictionary is one
			{											// letter off from the current word of interest
				vector<string> vectorToAdd = currentVector;
				vectorToAdd.push_back(dictionary[i]);
				add(vectorToAdd);
				if (dictionary[i] == secondWord) // check if the next word is the second word, if so output the ladder
				{
					cout << endl << "Shortest ladder was found!" << endl; // end method if the ladder is found
					for (int i = 0; i < currentVector.size(); i++)
					{
						cout << currentVector[i] << "  ";
					}
					cout << dictionary[i] << endl;
					return;
				}
			}
			if (wordOfInterest == dictionary[i]) // remove used word from dictionary
			{
				foundWordToDelete = true;
				indexToDelete = i;
			}
		}
		if (foundWordToDelete)
		{
			// cout << "Erasing " << dictionary[(indexToDelete)] << endl;
			dictionary.erase(dictionary.begin() + indexToDelete);
		}
		temp = temp->next;
	} while (temp != nullptr);
	if (!pathFound) // check if the ladder was not found, outputting a message if not
	{
		cout << "Sorry, ladder not found!" << endl;
	}
}

// oneOff is a method to determine if two words differ by one letter
bool WordLadderList::oneOff(string word1, string word2)
{
	int diffCount = 0;
	for (int i = 0; i < word1.size(); i++)
	{
		if (word1[i] != word2[i])
		{
			diffCount++;
		}
	}
	if (diffCount == 1)
		return true;
	else
		return false;
}

// method for traversing the linked list and outputting its contents
void WordLadderList::display()
{
	Node* tempNode = head;
	while (tempNode != nullptr)
	{
		vector<string> vectorToPrint = tempNode->data;
		for (int i = 0; i < vectorToPrint.size(); i++)
		{
			cout << vectorToPrint[i] << "   ";
		}
		cout << endl;
		tempNode = tempNode->next;
	}
}

// destructor method
WordLadderList::~WordLadderList()
{
	Node* tempNode = head;
	while (tempNode != nullptr)
	{
		Node* junk = tempNode;
		tempNode = tempNode->next;
		delete junk;
	}
}