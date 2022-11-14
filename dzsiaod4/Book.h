#pragma once
#include <string>
#include <iostream>
#include<fstream>
using namespace std;
class Book
{
public:
	 long long getIsbn();
	 void setPosition(int);
	int getPosition();
	bool isClear();
	void setClear(bool);
	bool isDeleted();
	void setDeleted(bool);
	Book( long long, int);
	Book();

private:
	 long long isbn;
	int position;
	bool clear = true;
	bool deleted = false;
};

