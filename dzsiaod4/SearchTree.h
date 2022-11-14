#pragma once
#include "Node.h"
#include "BinFile.h"

class SearchTree
{
public:
	bool isEmpty();
	Node* getRoot();
	void insertValue(long long, int = -1);
	void printTree(int = 5);
	Node** searchValue(long long);
	void deleteValue(long long);
	void fill(std::string, int);
private:
	Node* root = nullptr;
	void insertValue(long long, Node**, int);
	void printTree(Node*, int, int);
	Node** searchValue(long long, Node**);
	void deleteValue(Node**);
};
