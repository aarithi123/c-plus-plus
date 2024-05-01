#pragma
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
//                        BankAccount
//  Abstract Base Class
//////////////////////////////////////////////////////////////////////

//  constructor
BankAccount::BankAccount(int ID, string NAME) {
    id = ID;
    name = NAME;
}

//getID
int BankAccount::getID() {
    return id;
}

// getName
string BankAccount::getName() {
    return name;
}

//////////////////////////////////////////////////////////////////////
//                        class CheckingAccount
//  Derived from BankAccount ABC
//////////////////////////////////////////////////////////////////////


// constructor
CheckingAccount::CheckingAccount(float AMOUNT, int ID, string NAME) : BankAccount(ID, NAME) {
    id = ID;
    name = NAME;
    amount = AMOUNT;
}

// setAmount
void CheckingAccount::setAmount(float AMOUNT) {
    amount = AMOUNT;
}

// Withdraw
bool CheckingAccount::Withdraw(float AMOUNT) {
    if (AMOUNT > amount) {
        return false;
    } else {
        amount = amount - AMOUNT;
        return true;
    }
}

// getAmount override
float CheckingAccount::getAmount() {
    return amount;
}

// Deposit override
void CheckingAccount::Deposit(float AMOUNT) {
    amount = amount + AMOUNT;
}

// Display override
void CheckingAccount::Display()
{
    cout << setprecision(2) << fixed;
    cout << name << "(" << id << "):" << endl;
    cout << "\tChecking Account: $" << amount << endl;
}

//////////////////////////////////////////////////////////////////////
//                        class SavingsAccount
//  Derived from BankAccount ABC
//////////////////////////////////////////////////////////////////////

// constructor
SavingsAccount::SavingsAccount(float AMOUNT, int ID, string NAME) : BankAccount(ID, NAME) {
    id = ID;
    name = NAME;
    amount = AMOUNT;
}

// setAmount
void SavingsAccount::setAmount(float AMOUNT) {
    amount = AMOUNT;
}

// Withdraw
bool SavingsAccount::Withdraw(float AMOUNT) {
    if (AMOUNT > amount) {
        return false;
    } else {
        amount = amount - AMOUNT;
        return true;
    }
}

// Withdraw
float SavingsAccount::CompoundEarnings(float PERCENT) {
    float earnings = 0;
    float interest = 0;
    earnings = amount * (1 + PERCENT);
    interest = earnings - amount;
    amount = earnings;
    return interest;
}

// Transfer
bool SavingsAccount::Transfer(CheckingAccount &checkingAccount, float AMOUNT) {
    if (AMOUNT > amount) {
        return false;
    } else {
        amount = amount - AMOUNT;
        checkingAccount.Deposit(AMOUNT);
        return true;
    }
}

// getAmount override
float SavingsAccount::getAmount() {
    return amount;
}

// Deposit override
void SavingsAccount::Deposit(float AMOUNT) {
    amount = amount + AMOUNT;
}

// Display override
void SavingsAccount::Display()
{
    cout << setprecision(2) << fixed;
    cout << name << "(" << id << "):" << endl;
    cout << "\tSavings Account: $" << amount << endl;
}

//////////////////////////////////////////////////////////////////////
//                        class InvestmentAccount
//  Derived from CheckingAccount and SavingsAccount
//////////////////////////////////////////////////////////////////////

InvestmentAccount::InvestmentAccount(float amount, int id, string name)
        : BankAccount(id, name), CheckingAccount(amount, id, name), SavingsAccount(amount,id,name) {
    CheckingAccount::id = id;
    CheckingAccount::name = name;
    CheckingAccount::setAmount(0);

    SavingsAccount::id = id;
    SavingsAccount::name = name;
    SavingsAccount::setAmount(amount);
}

// Deposit override
void InvestmentAccount::Deposit(float AMOUNT) {
    float balance = SavingsAccount::getAmount();
    balance = balance + AMOUNT;
    SavingsAccount::setAmount(balance);
}

// getAmount override
float InvestmentAccount::getAmount() {
    return (CheckingAccount::getAmount() + SavingsAccount::getAmount());
}

// Transfer override
bool InvestmentAccount::Transfer(float PERCENT) {
    float balance = SavingsAccount::getAmount();
    if (PERCENT > 100) {
        return false;
    } else {
        balance = balance * (PERCENT / 100);
        CheckingAccount::setAmount(balance);
        SavingsAccount::setAmount(SavingsAccount::getAmount() - balance);
        return true;
    }
}

float InvestmentAccount::CompoundEarnings(float PERCENT) {
    float earnings = 0;
    float interest = 0;
    earnings = SavingsAccount::getAmount() * (1 + PERCENT);
    interest = earnings - SavingsAccount::getAmount();
    CheckingAccount::setAmount(interest);
    return interest;
}

// Display override
void InvestmentAccount::Display()
{
    cout << setprecision(2) << fixed;
    cout << CheckingAccount::name << "(" << CheckingAccount::id << "):" << endl;
    cout << "\tTotal: $" << CheckingAccount::getAmount() + SavingsAccount::getAmount() << endl;
    cout << "\t\tImmediate Funds: $" << CheckingAccount::getAmount() << endl;
    cout << "\t\tInvestment: $" << SavingsAccount::getAmount() << endl;
}

//getID
int InvestmentAccount::getID() {
    return CheckingAccount::id;
}

// getName
string InvestmentAccount::getName() {
    return CheckingAccount::name;
}
