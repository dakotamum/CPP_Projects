// Dakota Mumford
// Word Ladder Project

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "WordLadderList.hpp"
using namespace std;

// main function instatiates the WordLadderList class and calls its member functions
// to output the shortest word ladder to the user
int main()
{
	string firstWord, secondWord;
	do {							// gather user input for the first word and second word
		cout << "First word: ";
		cin >> firstWord;
		cout << "Second word: ";
		cin >> secondWord;
		cout << endl;
		if(secondWord.size() != firstWord.size()) // checks to make sure the words are the same size
		{
			cout << "Words must be the same size. Try again." << endl;
		}
	} while (secondWord.size() != firstWord.size());

	
	WordLadderList newList(firstWord, secondWord); // make new WordLadderList object
	newList.findLadder(); // find the ladder of the words

	return 0;
}