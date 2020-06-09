// Dakota Mumford
// Binary Tree Project

#include <iostream>
#include "BinaryTree.hpp"
using namespace std;

// main function which shows the functionality of the BinaryTree class
int main()
{
	BinaryTree thisOldTree;	// new BinaryTreeObject
	// insert a bunch of values
	thisOldTree.insert(5);
	thisOldTree.insert(3);
	thisOldTree.insert(7);
	thisOldTree.insert(2);
	thisOldTree.insert(4);
	thisOldTree.insert(6);
	thisOldTree.insert(8);
	// display the tree
	thisOldTree.display();
	// remove a value
	thisOldTree.remove(7);
	// display the tree again
	thisOldTree.display();
	return 0;
}