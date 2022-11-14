#include "Node.h"

Node::Node(long long key, int filePos)
{
	this->key = key;
	this->filePos = filePos;
	ltree = rtree = nullptr;
}
