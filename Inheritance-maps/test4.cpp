#include<iostream>
#include<vector>
#include<iomanip>
#include "BankAccount.h"
using namespace std;

void testCompoundEarnings() {
    SavingsAccount save(999999,2222,"Prof. Cruz");
    InvestmentAccount invest(0.01f,3333,"Noles");

    float temp = save.CompoundEarnings(0.5f);
    cout << "Earned $" << fixed << setprecision(2) << temp << endl;
    save.Display();
    cout << endl;
    temp = invest.CompoundEarnings(1);
    cout << "Earned $" << fixed << setprecision(2) << temp << endl;
    invest.Display();
}

int main() {
    testCompoundEarnings();
    return 0;
}