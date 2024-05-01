#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
//                        BankAccount
//  Abstract Base Class
//////////////////////////////////////////////////////////////////////
class BankAccount {
protected:
    int id;
    string name;
public:
    BankAccount(int id, string name);

    int getID();
    string getName();
    virtual void Display() = 0;
    virtual void Deposit(float) = 0;
    virtual float getAmount() = 0;
};

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
class CheckingAccount : public BankAccount {
private:
    float amount;
protected:
    void setAmount(float amount);
public:
    CheckingAccount(int id, string name, float amount);
    void Withdraw(float amount);
    void Display();
    float getAmount();
    void Deposit(float amount);
};

// constructor
CheckingAccount::CheckingAccount(int ID, string NAME, float AMOUNT) : BankAccount(ID, NAME) {
    id = ID;
    name = NAME;
    amount = AMOUNT;
}

// setAmount
void CheckingAccount::setAmount(float AMOUNT) {
    amount = AMOUNT;
}

// Withdraw
void CheckingAccount::Withdraw(float AMOUNT) {
    amount = amount - AMOUNT;
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
    cout << "Checking Account: " << id << endl;
    cout << "\tName: " << name << endl;
    cout << "\tAmount: " << amount << endl;
}

//////////////////////////////////////////////////////////////////////
//                        class SavingsAccount
//  Derived from BankAccount ABC
//////////////////////////////////////////////////////////////////////
class SavingsAccount : public BankAccount {
private:
    float amount;
protected:
    void setAmount(float amount);
public:
    SavingsAccount(int id, string name, float amount);
    void Withdraw(float amount);
    float CompoundEarnings(float PERCENT);
    bool Transfer(float amount, CheckingAccount &checkingAccount);
    void Display();
    float getAmount();
    void Deposit(float amount);
};

// constructor
SavingsAccount::SavingsAccount(int ID, string NAME, float AMOUNT) : BankAccount(ID, NAME) {
    id = ID;
    name = NAME;
    amount = AMOUNT;
}

// setAmount
void SavingsAccount::setAmount(float AMOUNT) {
    amount = AMOUNT;
}

// Withdraw
void SavingsAccount::Withdraw(float AMOUNT) {
    amount = amount - AMOUNT;
}

// Withdraw
float SavingsAccount::CompoundEarnings(float PERCENT) {
    amount = amount * (1 + PERCENT);
    return amount;
}

// Transfer
bool SavingsAccount::Transfer(float AMOUNT, CheckingAccount &checkingAccount) {
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
    cout << "Checking Account: " << id << endl;
    cout << "\tName: " << name << endl;
    cout << "\tAmount: " << amount << endl;
}

//////////////////////////////////////////////////////////////////////
//                        class InvestmentAccount
//  Derived from CheckingAccount and SavingsAccount
//////////////////////////////////////////////////////////////////////
class InvestmentAccount : public CheckingAccount, public SavingsAccount {
private:

protected:

public:
    InvestmentAccount(int id, string name, float amount);
    void Deposit(float amount);
    void Display();
    float getAmount();
    bool Transfer(float percent);
};

InvestmentAccount::InvestmentAccount(int id, string name, float amount)
        : CheckingAccount(id, name,amount), SavingsAccount(id, name, amount) {
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

// Display override
void InvestmentAccount::Display()
{
    cout << "Checking Account: " << CheckingAccount::id << endl;
    cout << "\tName: " << CheckingAccount::name << endl;
    cout << "\tAmount: " << InvestmentAccount::getAmount() << endl;
}

int main() {
    BankAccount * accounts[0];

    cout << "***********************************" <<endl;
    cout << "CheckingAccount" << endl;
    CheckingAccount check0(1001,string("raj"),float(100.0));
    accounts[0] = &check0;
    check0.Deposit(100);
    cout << "getAmount: " << check0.getAmount() << endl;
    cout << "Display: " << endl;
    check0.Display();
    check0.Withdraw(50);
    cout << "after withdraw: " << endl;
    check0.Display();

    cout << "***********************************" <<endl;
    cout << "SavingsAccount" << endl;
    SavingsAccount save0(1002,string("aarithi"),float(1000.0));
    accounts[0] = &save0;
    float intrest;
    intrest = save0.CompoundEarnings(0.20);
    cout << "CompoundEarnings: " << intrest << endl;
    cout << "Transfer" << endl;
    save0.Transfer(30, check0);
    cout << "Checking Amount: " << check0.getAmount() << endl;

    cout << "***********************************" <<endl;
    cout << "InvestmentAccount" << endl;
    //InvestmentAccount *invPtr = nullptr;
    //float amount = invPtr -> CheckingAccount::getAmount();
    InvestmentAccount inv0(1003,string("shyam"),float(1000.0));
    inv0.Deposit(500);
    float amount = inv0.getAmount();
    inv0.Transfer(50);

    for (int i = 0 ; i < 1 ; i++)
        accounts[i]->Display();


    cout << "id: " << "Hello" << endl;
    return 0;
};
