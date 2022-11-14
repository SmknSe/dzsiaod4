#include <conio.h>
#include <chrono>
#include "BinFile.h"
#include "SearchTree.h"
#include "SplayTree.h"
#include "HashTable.h"
using namespace std;


void skip() {
	cout << "\nPress any key to continue ";
	_getch();
}
void testSearch(SearchTree& tree) {
	system("cls");
	long long key;
	char ch;
	Node** node;
	while (1) {
		cout << "\nBinary search tree\n";
		cout <<
			"1. File 10\n"
			"2. File 1000\n" <<
			"3. File 1000000\n" <<
			"4. Find value\n" <<
			"5. Delete value\n" <<
			"6. Print tree\n" <<
			"Enter command: ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			if (tree.isEmpty()) {
				BinFile file("Search10");
				file.fill(10);
				tree.fill(file.name(), 10);
				tree.printTree();
			}
			else cout << "Tree isn't empty\n";
			break;
		case '2':
			if (tree.isEmpty()) {
				BinFile file("Search1000");
				file.fill(1000);
				tree.fill(file.name(), 1000);
			}
			else cout << "Tree isn't empty\n";
			break;
		case '3':
			if (tree.isEmpty()) {
				BinFile file("Search1000000");
				file.fill(1000000);
				tree.fill(file.name(), 1000000);
			}
			else cout << "Tree isn't empty\n";
			break;
		case '4':
			cout << "\nEnter value: ";
			cin >> key;
			node = tree.searchValue(key);
			cout << key << " ";
			if (node != nullptr)
				cout << "was found\n";
			else
				cout << "was not found\n";

			break;
		case '5':
			cout << "\nEnter the value to be deleted: ";
			cin >> key;
			tree.deleteValue(key);
			tree.printTree();
			break;
		case '6':
			tree.printTree();
			break;
		}
	}
}
void testSplay(SplayTree& tree) {
	system("cls");
	long long key;
	char ch;
	Node* node;
	while (1) {
		cout << "\nSplay tree\n";
		cout <<
			"1. File 10\n"
			"2. File 1000\n" <<
			"3. File 1000000\n" <<
			"4. Find value\n" <<
			"5. Delete value\n" <<
			"6. Print tree\n" <<
			"Enter command: ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			if (tree.isEmpty()) {
				BinFile file("Search10");
				file.fill(10);
				tree.fill(file.name(), 10);
				tree.printTree();
			}
			else cout << "Tree isn't empty\n";
			break;
		case '2':
			if (tree.isEmpty()) {
				BinFile file("Search1000");
				file.fill(1000);
				tree.fill(file.name(), 1000);
			}
			else cout << "Tree isn't empty\n";
			break;
		case '3':
			if (tree.isEmpty()) {
				BinFile file("Search1000000");
				file.fill(1000000);
				tree.fill(file.name(), 1000000);
			}
			else cout << "Tree isn't empty\n";
			break;
		case '4':
			cout << "\nEnter value: ";
			cin >> key;
			node = tree.searchValue(key);
			cout << key << " ";
			if (node != nullptr)
				cout << "was found\n";
			else
				cout << "was not found\n";

			break;
		case '5':
			cout << "\nEnter the value to be deleted: ";
			cin >> key;
			tree.deleteValue(key);
			tree.printTree();
			break;
		case '6':
			tree.printTree();
			break;
		}
	}
}
void Searching(int size, BinFile& file, SearchTree& tree1, SplayTree& tree2, HashTable& table) {
	Node** node1;
	Node* node2;
	int pos;
	long long key;
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
	chrono::duration<double> elapsed1;
	chrono::duration<double> elapsed2;
	chrono::duration<double> elapsed3;
	string filename = file.name();
	file.fill(size);
	tree1.fill(filename, size);
	tree2.fill(filename, size);
	table.fill(filename, size);

	cout << "\nEnter the value to search for: ";
	cin >> key;

	start = chrono::steady_clock::now();
	node1 = tree1.searchValue(key);
	end = chrono::steady_clock::now();
	elapsed1 = chrono::duration_cast<chrono::duration<double>>(end - start) * 1000.0;

	cout << "key = " << key << " ";
	if (node1 != nullptr)
		cout << "is found";
	else
		cout << "was not found";
	cout << " (Binary search)\n";

	start = chrono::steady_clock::now();
	node2 = tree2.searchValue(key);
	end = chrono::steady_clock::now();
	elapsed2 = chrono::duration_cast<chrono::duration<double>>(end - start) * 1000.0;

	cout << "key = " << key << " ";
	if (node2 != nullptr)
		cout << "is found";
	else
		cout << "was not found";
	cout << " (Splay)\n";

	start = chrono::steady_clock::now();
	pos = table.findBook(key);
	end = chrono::steady_clock::now();
	elapsed3 = chrono::duration_cast<chrono::duration<double>>(end - start) * 1000.0;

	cout << "key = " << key << " ";
	if (pos != -1)
		cout << "is found";
	else
		cout << "was not found";
	cout << " (Hashtable)\n" <<
		"\n\nTime comparing: \nBinary search tree: " <<
		elapsed1.count() << " ms\nSplay tree: " << elapsed2.count() <<
		" ms\nHash table: " << elapsed3.count() << " ms\n";
}
void comparing(BinFile& file, SearchTree& tree1, SplayTree& tree2, HashTable& table) {
	system("cls");
	char ch;
	while (1)
	{
		cout << "\nAnalizing algorithms\n";
		cout <<
			"1. 1 000 file\n" <<
			"2. 1 000 000 file\n" <<
			"3. 10 file + print\n"
			"Enter command: ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			Searching(1000, file,tree1, tree2, table);
			break;
		case '2':
			Searching(1000000, file, tree1, tree2, table);
			break;
		case '3':
			Searching(10, file, tree1, tree2, table);
			tree1.printTree();
			tree2.printTree();
			table.print();
			break;
		default:
			cout << "Error command\n";
			break;
		}
	}
}

void main() {
	BinFile file("comparingFile.txt");
	SearchTree searchTree, fileSearchTree;
	SplayTree splayTree, fileSplayTree;
	HashTable table(10);
	char c;
	while (1) {
		system("cls");
		cout <<
			"1.Test SearchTree\n" <<
			"2.Test SplayTree\n" <<
			"3.Analyze search algorithms\n" <<
			"0.Exit programm\n ";
		cin >> c;
		switch (c)
		{
		case '1':
			testSearch(searchTree);
			skip();
			break;
		case '2':
			testSplay(splayTree);
			skip();
			break;
		case '3':
			comparing(file, searchTree, splayTree, table);
			break;
		case '4':
			cout << "\nProgram has been shut down\n";
			exit(0);
		default:
			cout << "\nError comand";
			skip();
			break;
		}
	}
}
