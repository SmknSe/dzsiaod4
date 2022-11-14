#include "SplayTree.h"
using namespace std;

bool SplayTree::isEmpty(){return !root;}
Node* SplayTree::getRoot(){ return root;}
int SplayTree::getRotationsAmount(){return rotations;}

Node** SplayTree::leftRotate(Node** ptr)
{
	rotations++;
	Node* newRoot = (*ptr)->rtree;
	(*ptr)->rtree = newRoot->ltree;
	newRoot->ltree = (*ptr);
	return &newRoot;
}

Node** SplayTree::rightRotate(Node** ptr)
{
	rotations++;
	Node* newRoot = (*ptr)->ltree;
	(*ptr)->ltree = newRoot->rtree;
	newRoot->rtree = (*ptr);
	return &newRoot;
}

Node* SplayTree::splay(Node** ptr, long long key)
{
	if ((*ptr) == nullptr || (*ptr)->key == key)
		return *ptr;
	if (key < (*ptr)->key)
	{
		if ((*ptr)->ltree == nullptr) return *ptr;

		if (key < (*ptr)->ltree->key) // LL
		{
			(*ptr)->ltree->ltree = splay(&(*ptr)->ltree->ltree, key);
			(*ptr) = *rightRotate(ptr);
		}
		else if (key > (*ptr)->ltree->key) // LR
		{
			if ((*ptr)->ltree->rtree != nullptr) {
				(*ptr)->ltree->rtree = splay(&(*ptr)->ltree->rtree, key);
				(*ptr)->ltree = *leftRotate(&(*ptr)->ltree);
			}
		}
		if ((*ptr)->ltree == nullptr)
			return (*ptr);
		else
			return *rightRotate(ptr);
	}
	else {
		if ((*ptr)->rtree == nullptr) return *ptr;

		if (key > (*ptr)->rtree->key) // RR
		{
			(*ptr)->rtree->rtree = splay(&(*ptr)->rtree->rtree, key);
			(*ptr) = *leftRotate(ptr);
		}
		else if (key < (*ptr)->rtree->key) // RL
		{
			if ((*ptr)->rtree->ltree != nullptr) {
				(*ptr)->rtree->ltree = splay(&(*ptr)->rtree->ltree, key);
				(*ptr)->rtree = *rightRotate(&(*ptr)->rtree);
			}
		}
		if ((*ptr)->rtree == nullptr)
			return (*ptr);
		else
			return *leftRotate(ptr);
	}
}

void SplayTree::insertValue(long long key, int filePos)
{
	if (isEmpty()) root = new Node(key, filePos);

	else
	{
		root = splay(&root, key);
		if (root->key == key) return;

		Node* newRoot = new Node(key, filePos);
		if (key < root->key)
		{
			newRoot->ltree = root->ltree;
			newRoot->rtree = root;
			root->ltree = nullptr;
			root = newRoot;
		}
		else
		{
			newRoot->ltree = root;
			newRoot->rtree = root->rtree;
			root->rtree = nullptr;
			root = newRoot;
		}
	}
}

void SplayTree::printTree(Node* ptr, int level, int indent = 3)
{
	if (!ptr) return;
	printTree(ptr->rtree, level + 1, indent);
	for (int i = 1; i <= level * indent; i++)
		cout << ' ';
	cout << ptr->key << "\n";
	printTree(ptr->ltree, level + 1, indent);
}

void SplayTree::printTree(int indent)
{
	if (isEmpty())
	{
		cout << "Tree is empty\n";
		return;
	}
	cout << "Tree:\n";
	printTree(root, 0, indent);
}

Node* SplayTree::searchValue(long long key)
{
	root = splay(&root, key);
	if (root) return root->key == key ? root : nullptr;
	return nullptr;
}

void SplayTree::deleteValue(long long key)
{
	if (isEmpty()) return;
	root = splay(&root, key);
	if (root->key != key) {
		cout << "Value to be deleted not found\n";
		return;
	}
	Node* temp = root;

	if (root->ltree == nullptr)
		root = temp->rtree;
	else
	{
		root = splay(&root->ltree, key);
		root->rtree = temp->rtree;
	}
	delete temp;
	cout << "Value was deleted\n";

}

void SplayTree::fill(string filename, int lines) {
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