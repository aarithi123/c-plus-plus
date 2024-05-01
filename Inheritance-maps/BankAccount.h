#pragma
#include <iostream>

using namespace std;


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

class CheckingAccount : virtual public BankAccount {
private:
    float amount;
protected:
    void setAmount(float amount);
public:
    CheckingAccount(float amount, int id, string name);
    bool Withdraw(float amount);
    void Display();
    float getAmount();
    void Deposit(float amount);
};

class SavingsAccount : virtual public BankAccount {
private:
    float amount;
protected:
    void setAmount(float amount);
public:
    SavingsAccount(float amount, int id,  string name);
    bool Withdraw(float amount);
    float CompoundEarnings(float PERCENT);
    bool Transfer(CheckingAccount &checkingAccount, float amount);
    void Display();
    float getAmount();
    void Deposit(float amount);
};

class InvestmentAccount : public CheckingAccount, public virtual SavingsAccount {
private:

protected:

public:
    InvestmentAccount(float amount, int id, string name);
    void Deposit(float amount);
    void Display();
    float getAmount();
    bool Transfer(float percent);
    float CompoundEarnings(float PERCENT);
    int getID();
    string getName();
};

