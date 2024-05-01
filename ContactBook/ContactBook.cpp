//
// Created by aarit on 1/27/2024.
//

#include "ContactBook.h"

Contact::Contact(string _name, string _number) {
    name = _name;
    number = _number;
}

string Contact::getName() {
    return name;
}

string Contact::getNumber() {
    return number;
}

void Contact::Display() {
    cout << name << ", " << number << endl;
}


ContactBook::ContactBook() {
    curr_size = 0;
}

Contact* ContactBook::Find(string x) {
    for (int i = 0; i < curr_size; i++) {
        if (contact[i]->getName() == x) {
            return contact[i];
        } else if (contact[i]->getNumber() == x) {
            return contact[i];
        }
    }
    return nullptr;
}

void ContactBook::Add(Contact& contact1) {
    contact[curr_size] = &contact1;
    curr_size++;
}

void ContactBook::Display() {
    for (int i = 0; i < curr_size; i++) {
        cout << contact[i]->getName() << ", " << contact[i]->getNumber() << endl;
    }
}

void ContactBook::AddContacts(vector<Contact *> contacts) {
    int j = 0;
    for (int i = curr_size; i < contacts.size(); i++) {
        contact[i] = contacts[j];
        j++;
        curr_size++;
    }
}

void ContactBook::Remove(Contact contact2) {
    int j = 0;
    for (int i = 0; i < curr_size; i++) {
        if (contact[i]->getName() == contact2.getName()) {
            j = i;
            break;
        }
    }
    for (int i = j; i < curr_size; i++) {
        contact[i] = contact[i+1];
    }
    curr_size--;
}

void ContactBook::Alphabetize() {
    Contact *temp;
    for (int a = 0; a < curr_size; a++) {
        for (int b = a + 1; b < curr_size; b++) {

            for (int i = 0; i < contact[a]->getName().length(); i++) {
                contact[a]->getName().at(i) = toupper(contact[a]->getName().at(i));
            }
            for (int i = 0; i < contact[b]->getName().length(); i++) {
                contact[b]->getName().at(i) = toupper(contact[b]->getName().at(i));
            }

            if (contact[a]->getName().compare(contact[b]->getName()) > 0) {
                temp = contact[a];
                contact[a] = contact[b];
                contact[b] = temp;
            }
        }
    }
}

void ContactBook::operator+=(Contact &contact1) {
    this->Add(contact1);
}

void ContactBook::operator-=(Contact &contact3) {
    this->Remove(contact3);
}

void ContactBook::operator+=(ContactBook &myContacts) {
    vector<Contact*> book;
    for (int i = 0; i < myContacts.curr_size; i++) {
        book.push_back(myContacts.contact[i]);
    }
    this->AddContacts(book);
}

void ContactBook::operator-=(ContactBook &books) {
    for (int i = 0; i < this->curr_size; i++) {
            books.contact[i] = nullptr;
            books.curr_size = 0;
        }
}

bool ContactBook::operator==(ContactBook book) {
    bool var = true;
    for (int i = 0; i < book.curr_size; i++) {
        if (book.contact[i] == this->Find(book.contact[i]->getName())
        and book.contact[i] == this->Find(book.contact[i]->getNumber()))  {
            continue;
        } else {
            var = false;
            break;
        }
    }
    return var;
}

bool ContactBook::operator!=(ContactBook book) {
    bool var = false;
    for (int i = 0; i < book.curr_size; i++) {
        if (book.contact[i] == this->Find(book.contact[i]->getName())
        and book.contact[i] == this->Find(book.contact[i]->getNumber()))  {
            continue;
        } else {
            var = true;
            break;
        }
    }
    return var;
}

ContactBook ContactBook::operator+(ContactBook& book1) {
    ContactBook books;
    vector<Contact*> book;
    for (int i = 0; i < book1.curr_size; i++) {
        book.push_back(book1.contact[i]);
    }
    int j = 0;
    for (int i = 0; i < book.size(); i++) {
        this->contact[i + book.size()] = book[j];
        curr_size++;
        j++;
    }
    //curr_size = book.size() + this->curr_size;
    for (int i = 0; i < this->curr_size; i++) {
        books.contact[i] = this->contact[i];
    }
    books.curr_size = this->curr_size;
    return books;
}

ContactBook ContactBook::operator-(ContactBook &book) {
    ContactBook books;
    for (int i = 0; i < this->curr_size; i++) {
        books.contact[i] = nullptr;
        books.curr_size = 0;
    }
    return books;
}

/*void ContactBook::operator=(ContactBook book) {
    for (int i = 0; i < book.curr_size; i++) {
        this->Add(*book.contact[i]);
    }
}





/*Contact *temp[100];
int k = sizeof(book1.contact) + sizeof(this->contact);
int a = sizeof(book1.contact);
for (int i = 0; i < k; i++) {
    if (i < a) {
        temp[i] = book1.contact[i];
    } else {
        temp[i] = this->contact[i - a];
    }
}
for (int i = 0; i < k; i++) {
    this->contact[i] = temp[i];
}
}
*/




