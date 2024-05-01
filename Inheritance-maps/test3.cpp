#include<iostream>
#include<vector>
#include<iomanip>
#include "BankAccount.h"
using namespace std;

void testWithdrawTransfer() {
    CheckingAccount check(5,1111,"Diego Aguilar");
    SavingsAccount save(999999,2222,"Prof. Cruz");
    if (check.Withdraw(100)) {
        cout << "Withdrew more than possible!" << endl;
    } else {
        cout << "Withdraw failure check: Successful!" << endl;
    }
    if (check.Withdraw(1)) {
        cout << "Withdraw passing check: Successful!" << endl;
    } else {
        cout << "Withdraw passing check: Unsuccessful!" << endl;
    }
    check.Display();
    cout << endl;

    if (save.Transfer(check,1000000)) {
        cout << "Transfered more than possible!" << endl;
    } else {
        cout << "Transfer failure check: Successful!" << endl;
    }
    if (save.Transfer(check,100)) {
        cout << "Transfer passing check: Successful!" << endl;
    } else {
        cout << "Transfer passing check: Unsuccessful!" << endl;
    }
    check.Display();
    save.Display();
}

int main_test3() {
    testWithdrawTransfer();
    return 0;
}