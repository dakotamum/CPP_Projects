// Dakota Mumford
// Binary Tree Project

#ifndef _BINARY_TREE_
#define _BINARY_TREE_

#include <iostream>
using namespace std;

// BinaryTree class definition which contains Node root pointer and various methods
class BinaryTree
{
protected:
	// Node struct definition which stores a data integer and pointers to left and right children
	struct Node
	{
		int data;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;
		Node(int value) { data = value, leftChild = nullptr, rightChild = nullptr; }
	};
	Node* root = nullptr;
public:
	BinaryTree() { root = nullptr; }
	void insert(int value);
	void display() { traverseDisplay(root, 0), cout << endl; } // calls traverseDisplay with the root pointer as an argument
	void traverseDisplay(Node* tempNode, int level);
	void remove(int value) { findNodeToDelete(root, value); } // calls findNodeToDelete with root pointer as an argument
	void findNodeToDelete(Node* &tempNode, int value);
	void deleteNode(Node* &tempNode);
	void killTree(Node* tempNode);
	~BinaryTree() { killTree(root); } // destructor
};

#endif