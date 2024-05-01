#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <string.h>
using namespace std;


class Contact {
    string name;
    string number;
public:
    Contact(string _name, string _number);
    string getName();
    string getNumber();
    void Display();

};


class ContactBook {
    static const int MAX_SIZE = 100;
    Contact* contact[MAX_SIZE];
    unsigned int curr_size = 0;

public:
    ContactBook();
    Contact* Find(string x);
    void Add(Contact& contact1);
    void Display();
    void AddContacts(vector<Contact*> contacts);
    void Remove(Contact contact2);
    void Alphabetize();
    void operator+=(Contact& contact1);
    void operator+=(ContactBook& myContacts);
    ContactBook operator+(ContactBook& book1);
    void operator-=(Contact& contact3);
    void operator-=(ContactBook& books);
    bool operator==(ContactBook book);
    bool operator!=(ContactBook book);
    ContactBook operator-(ContactBook& book);
    //void operator=(ContactBook book);
};