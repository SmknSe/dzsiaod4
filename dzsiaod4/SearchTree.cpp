#include "SearchTree.h"
using namespace std;

bool SearchTree::isEmpty(){	return !root; }

Node* SearchTree::getRoot(){return root;}

void SearchTree::insertValue(long long key, Node** ptr, int filePos)
{
	if (!*ptr) *ptr = new Node(key, filePos);
	else if (key < (*ptr)->key) insertValue(key, &(*ptr)->ltree, filePos);
	else if (key > (*ptr)->key) insertValue(key, &(*ptr)->rtree, filePos);
}

void SearchTree::insertValue(long long key, int filePos)
{
	insertValue(key, &root, filePos);
}

void SearchTree::printTree(Node* ptr, int level, int indent)
{
	if (!ptr) return;
	printTree(ptr->rtree, level + 1, indent);
	for (int i = 1; i <= level * indent; i++)
		cout << ' ';
	cout << ptr->key << "\n";
	printTree(ptr->ltree, level + 1, indent);
}

void SearchTree::printTree(int indent)
{
	if (isEmpty())
	{
		cout << "Tree is empty\n";
		return;
	}
	cout << "Tree:\n";
	printTree(root, 0, indent);
}

Node** SearchTree::searchValue(long long key)
{
	return searchValue(key, &root);
}

Node** SearchTree::searchValue(long long key, Node** ptr)
{
	if (!*ptr) return nullptr;
	if (key < (*ptr)->key) searchValue(key, &(*ptr)->ltree);
	else if (key > (*ptr)->key) searchValue(key, &(*ptr)->rtree);
	else return ptr;
}

void SearchTree::fill(string filename, int lines)
{
	ifstream in;
	long long key;
	in.open(filename, ios::binary | ios::in);
	for (int i = 0; i < lines; i++)
	{
		in.seekg(i * lineSize, ios::beg);
		in >> key;
		insertValue(key, i);
	}
}

void SearchTree::deleteValue(long long key)
{
	Node** ptr = searchValue(key);
	if (ptr) {
		deleteValue(ptr);
		cout << "Value was deleted\n";
	}
	else cout << "Value to be deleted not found\n";
}

void SearchTree::deleteValue(Node** ptr)
{
	if ((*ptr)->ltree == nullptr && (*ptr)->rtree == nullptr)
	{
		delete* ptr;
		*ptr = nullptr;
	}
	else if ((*ptr)->ltree == nullptr)
	{
		Node* temp = *ptr;
		*ptr = (*ptr)->rtree;
		delete temp;
	}
	else if ((*ptr)->rtree == nullptr)
	{
		Node* temp = *ptr;
		*ptr = (*ptr)->ltree;
		delete temp;
	}
	else
	{
		Node* min = (*ptr)->rtree;
		while (min->ltree != nullptr)
			min = min->ltree;
		long long tempkey = min->key;
		deleteValue(min->key);
		(*ptr)->key = tempkey;
	}
}