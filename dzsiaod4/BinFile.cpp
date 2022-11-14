#include "BinFile.h"

void BinFile::write(ostream& os, string l)
{
	os.write((char*)l.data(), lineSize);
}

BinFile::BinFile(string filename) {
	this->filename = filename;
	this->recs = 0;
	ofstream file(filename);
	file.close();
}

void BinFile::fill(int n) {
	file.open(filename, ios::binary | ios::out);
	ifstream dataFile;
	string s;
	dataFile.open("dataFile.txt");
	if (dataFile.is_open()) {
		for (int i = 0; i < n; i++) {
			getline(dataFile, s);
			write(file, s);
			recs++;
		}
		dataFile.close();
		file.close();
		cout << "Filled: " << recs << endl;
	}
	else cout << "Error\n";
}

int BinFile::size() { return recs; }
string BinFile::name() { return filename; }

void BinFile::print() {
	file.open(filename, ios::in);
	string s;
	while (getline(file, s)) {
		cout << s << endl;
	}
}

long long BinFile::readKey(int p) {
	file.open(filename, ios::in);
	file.seekg(lineSize * p, ios::beg);
	long long tmp;
	file >> tmp;
	return tmp;
}
