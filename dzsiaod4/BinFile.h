#pragma once
#include <fstream>
#include "SearchTree.h"
#include "Defines.h"
#include <string>
using namespace std;

class BinFile
{
public:
	BinFile(string);
	void fill(int n);
	void write(ostream&, string);
	void print();
	int size();
	string name();
	long long readKey(int);
private:
	fstream file;
	string filename;
	int recs;
};

