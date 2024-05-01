#include<iostream>
#include<vector>
#include<iomanip>
#include "BankAccount.h"
using namespace std;

void testConstructorsAndGetters() {
    CheckingAccount check(5,1111,"Diego Aguilar");
    SavingsAccount save(999999,2222,"Prof. Cruz");
    InvestmentAccount invest(0.01f,3333,"Noles");
    cout << "Checking:" << endl;
    cout << "\tName of checking: " << check.getName() << endl;
    cout << "\tID of checking: " << check.getID() << endl;
    cout << "\tAmount in checking: " << check.getAmount() << endl << endl;

    cout << "Savings:" << endl;
    cout << "\tName of Savings: " << save.getName() << endl;
    cout << "\tID of Savings: " << save.getID() << endl;
    cout << "\tAmount in Savings: " << save.getAmount() << endl << endl;

    cout << "Investment:" << endl;
    cout << "\tName of Investment: " << invest.getName() << endl;
    cout << "\tID of Investment: " << invest.getID() << endl;
    cout << "\tAmount in Investment: " << invest.getAmount() << endl << endl;
}

int main_test1() {
    testConstructorsAndGetters();
    return 0;
}