#include <iostream>
#include "ContactBook.h"
using namespace std;

int main() {
    /*ContactBook myContacts;
    Contact Albert("Andres", "234-567-8901");
    myContacts.Add(Albert);
    Contact John("Justin", "234-567-8901");
    myContacts.Add(John);
    Contact Daivd("Roland", "234-567-8901");
    myContacts.Add(Daivd);
    Contact Jane("Lily", "234-567-8901");
    myContacts.Add(Jane);
    Contact Mary("George", "234-567-8901");
    myContacts.Add(Mary);
    cout << "previous" << endl;
    myContacts.Display();
    cout << "after" << endl;
    myContacts.Alphabetize();
    myContacts.Display();

    /*
    //Albert, 234-567-8901
    Alberta, 345-678-9012
    Bill, 789-012-3456
    //David, 678-901-2345
    Fredrickson, 456-789-0123
    Goose, 567-890-1234
    //Jane, 987-654-3210
    John, 123-456-7890
    //Johnathon, 890-123-4567
    Johnfart, 901-234-5678
    Johnny, 789-012-3456
    Johnson, 123-456-7890
    Linda, 456-789-0123
    //Mary, 234-567-8901
    Peter, 345-678-9012
    Ronald, 678-901-2345
    Simpleton, 901-234-5678
    Susan, 567-890-1234
    Theodore, 890-123-4567
    Xander, 012-345-6789
    /*
    string name = "Jenna";
    string number = "9049104858";
    string _name = "Aarithi";
    string _number = "9049109824";
    string names = "Raj";
    string numbers = "9043055032";
    vector<Contact*> contacts;

    Contact Jenna(name, number);
    Contact Raj(names, numbers);
    Contact Aarithi(_name, _number);


    //Jenna.Display();
    ContactBook myContacts;
    myContacts.Add(Jenna);
    myContacts.Add(Raj);
    myContacts.Add(Aarithi);
    cout << "before" << endl;
    myContacts.Display();
    cout << "after" << endl;
    myContacts.Remove(Raj);
    myContacts.Display();
    myContacts.Add(Raj);
    cout << "after addition" << endl;
    myContacts.Display();


   // myContacts.Display();
   // Contact* nameptr;
    //nameptr = myContacts.Find(names);

    Contact* jazz = &Raj;
    Contact* bass = &Aarithi;
    contacts.push_back(bass);
    contacts.push_back(jazz);
    myContacts.AddContacts(contacts);
    cout << "previous" << endl;
    myContacts.Display();
    cout << "after" << endl;
    myContacts.Alphabetize();
    myContacts.Display();

    /*if (nameptr == nullptr) {
        cout << "name not found" << endl;
    } else {
        cout << nameptr->getName() << endl;
    }
*/
    ContactBook myContacts;
    Contact Albert("Andres", "234-567-8901");
    Contact John("Justin", "234-567-8901");
    myContacts += Albert;
    myContacts += John;
    //cout << "before" << endl;
    myContacts.Display();
    //myContacts -= myContacts;
    //cout << "after" << endl;
    //myContacts.Display();


    ContactBook aarithi;
    Contact Daivd("Roland", "234-567-8901");
    Contact Jane("Lily", "234-567-8901");
    aarithi += Daivd;
    aarithi += Jane;
    //aarithi.Display();

    ContactBook raj;
    raj += John;
    raj += Albert;
    //raj.Display();

    ContactBook book;
    aarithi += myContacts;
    aarithi.Display();
    if (raj != aarithi) {
        cout << "not the same" << endl;
    } else {
        cout << "is the same" << endl;
    }
    //book.Display();

    return 0;
}
