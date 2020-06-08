#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

// Dakota Mumford
// Word Ladder Project

#include <vector>
#include <string>
#include <fstream>
using namespace std;

// WordLadderList class defines the properties and methods for maintaining a linked
// list of word ladder possibilities.
class WordLadderList
{
protected:
	struct Node		// Node definition
	{
		vector<string> data;
		Node* next = nullptr;
		Node(vector<string> wordLadder) { data = wordLadder, next = nullptr; }
	};
	Node* head = nullptr;
	Node* temp = nullptr;
	vector<string> dictionary;
	string firstWord;
	string secondWord;

public:
	WordLadderList(string firstWord, string secondWord);
	void add(vector<string> aLadder);
	void display();
	void findLadder();
	static bool oneOff(string word1, string word2);
	~WordLadderList();
};

#endif 