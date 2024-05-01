#include<iostream>
#include<vector>
#include<iomanip>
#include "BankAccount.h"
using namespace std;

void testDisplayDeposit() {
    CheckingAccount check(5,1111,"Diego Aguilar");
    SavingsAccount save(999999,2222,"Prof. Cruz");
    InvestmentAccount invest(0.01f,3333,"Noles");
    check.Deposit(95);
    check.Display();
    cout << endl;

    save.Deposit(1);
    save.Display();
    cout << endl;

    invest.Deposit(0.01f);
    invest.Display();
}


int main_test2() {
    testDisplayDeposit();
    return 0;
}