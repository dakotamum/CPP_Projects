#include "BinaryTree.hpp"
#include <iostream>
using namespace std;

// method for inserting a specified value into the tree
void BinaryTree::insert(int value)
{
	if (root == nullptr) // check if the tree is empty
	{
		root = new Node(value);
	}
	else
	{
		// traverse the tree to find a place to insert
		Node* tempNode = root;
		bool placeFound = false;
		while (!placeFound)
		{
			if (value >= tempNode->data)
			{
				if (tempNode->rightChild == nullptr)
				{
					// insert new Node
					tempNode->rightChild = new Node(value);
					placeFound = true;
				}
				else
				{
					tempNode = tempNode->rightChild;
				}
			}
			else
			{
				if (tempNode->leftChild == nullptr)
				{
					// insert new Node
					tempNode->leftChild = new Node(value);
					placeFound = true;
				}
				else
				{
					tempNode = tempNode->leftChild;
				}
			}
		}
	}
}

// method which traverses the binary tree, keeping track of the levels of the nodes, and displays the tree accordingly
void BinaryTree::traverseDisplay(Node* tempNode, int level)
{
	if (tempNode->rightChild != nullptr)
	{
		int newLevel = level + 1;
		traverseDisplay(tempNode->rightChild, newLevel);
	}
	for (int i = 0; i < level; i++) { cout << "  "; }
	cout << tempNode->data << endl;
	if (tempNode->leftChild != nullptr)
	{
		int newLevel = level + 1;
		traverseDisplay(tempNode->leftChild, newLevel);
	}
}

// method for finding the node to delete based on the user-specified integer value
void BinaryTree::findNodeToDelete(Node* &tempNode, int value)
{
	if (tempNode == nullptr)
	{
		return;
	}
	if (value > tempNode->data)
	{
		findNodeToDelete(tempNode->rightChild, value);
	}
	else if (value < tempNode->data)
	{
		findNodeToDelete(tempNode->leftChild, value);
	}
	else if (value == tempNode->data)
	{
		deleteNode(tempNode);
	}
}

// method for removing the node sent from the findNodeToDelete method and rearranging the tree as necessary
void BinaryTree::deleteNode(Node* &tempNode)
{
	Node* toDelete = tempNode;	// keep track of the node to delete
	if (tempNode->rightChild == nullptr) // if there's no right child, simply make the left child the replacement
	{
		tempNode = tempNode->leftChild;
	}
	else if (tempNode->leftChild == nullptr) // if there's no left child, simply make the right child the replacement
	{
		tempNode = tempNode->rightChild;
	}
	else
	{
		Node* newParent = tempNode->rightChild;	// node for keeping track of the lowest left-most node that will be the new parent for the left sub-tree
		while (newParent->leftChild != nullptr)
		{
			newParent = newParent->leftChild;
		}
		newParent->leftChild = tempNode->leftChild;
		tempNode = tempNode->rightChild;
	}
	delete toDelete;	// delete the node
}

// method for deleting an entire tree
void BinaryTree::killTree(Node* tempNode)
{
	if (tempNode == nullptr)
	{
		return;
	}
	killTree(tempNode->leftChild);
	killTree(tempNode->rightChild);
	delete tempNode;
}