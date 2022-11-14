#pragma once
#include "Node.h"
#include "BinFile.h"

class SplayTree
{
public:
	bool isEmpty();
	Node* getRoot();
	void insertValue(long long, int = -1);
	void printTree(int = 5);
	Node* searchValue(long long);
	void deleteValue(long long);
	int getRotationsAmount();
	void fill(std::string, int);
private:
	Node* root = nullptr;
	int rotations = 0;
	Node** rightRotate(Node**);
	Node** leftRotate(Node**);
	Node* splay(Node**, long long);
	void printTree(Node*, int, int);
};
