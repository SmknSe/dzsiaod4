#include "HashTable.h"

void HashTable::resize(int n)
{
    books.resize(n);
    this->m = n;
}

HashTable::HashTable(int m)
{
    this->resize(m);
    n = 0;
}

int HashTable::getInd( long long key)
{
    return key % m;
}

 long long HashTable::getNewInd( long long key)
{
    return key / m;
}

void HashTable::insBook(Book* b)
{
    int ind = this->getInd(b->getIsbn());
     long long sm = this->getNewInd(b->getIsbn());
    while (!books[ind].isClear()) {
        if (sm != 0 && sm % m != 0) ind = (ind + sm) % m;
        else ind = (ind++) % m;
    }
    books[ind] = *b;
    n++;
    books[ind].setClear(false);
    if ((float)n / (float)m >= 0.75) reHash();
}

int HashTable::findBook( long long key)
{
    int i = this->getInd(key);
     long long sm = this->getNewInd(key);
    while ((!books[i].isClear() || books[i].isDeleted()) && key != books[i].getIsbn()) {
        if (sm != 0) i = (i + sm) % m;
        else i = (i++) % m;
    }
    if (books[i].isClear() || books[i].isDeleted()) return NULL;
    else return books[i].getPosition();
}

int HashTable::size()
{
    return books.size();
}

void HashTable::reHash() {
    vector<Book> tmp = books;
    books.clear();
    m *= 2;
    books.resize(m);
    for (int i = 0; i < tmp.size(); i++) {
        if (!tmp[i].isClear()) this->insBook(&tmp[i]);
    }
}

void HashTable::print()
{
    for (int i = 0; i < this->size(); i++) {
        if (!this->books[i].isClear()) {
            cout << i << " " << books[i].getIsbn() << endl;
        }
    }
}

void HashTable::fileSearch(string filename, long long k)
{
    int p = this->findBook(k);
    ifstream in;
    in.open(filename, ios::binary | ios::in);
    in.seekg(lineSize * p, ios::beg);
    string isbn, name, label;
    in >> isbn; in >> name; in >> label;
    cout << isbn << " " << name << " " << label << endl;
}

void HashTable::fill(string filename, int t) {
    ifstream in;
    in.open(filename, ios::binary | ios::in);
    for (int i = 0; i < t; i++) {
        in.seekg(i * lineSize, ios::beg);
        long long key;
        in >> key;
        insBook(new Book(key,i));
    }
}

