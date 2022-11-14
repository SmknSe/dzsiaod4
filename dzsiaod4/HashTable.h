#pragma once
#include"Book.h"
#include<vector>
#include "Defines.h"
using namespace std;
class HashTable
{
public:
	int m;
	int n;
	void resize(int);
	HashTable(int m);
	int getInd(long long);
	long long getNewInd(long long);
	void insBook(Book*);
	int findBook(long long);
	void removeBook(Book*);
	int size();
	void reHash();
	void print();
	void remove(int);
	void fill(string, int);
	void fileSearch(string,long long);

private:
	vector<Book> books;
};
