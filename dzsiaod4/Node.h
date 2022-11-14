#pragma once
#include <iostream>
class Node
{
public:
	long long key;
	int filePos;
	Node* ltree, * rtree;
	Node(long long, int);
};

