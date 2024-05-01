#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include <cctype>
#include"BankAccount.h"
using namespace std;

struct AccountReader{
    // your two maps here as member variables
    map<int, BankAccount*> idMap;
    map<string, BankAccount*> nameMap;

    void operator()(string filePath) {
        // Load all accounts into the two maps!
        ////////////////////////////////////
        string line;
        string cell;
        string type;
        string name;
        string amount;
        float famount = 0;
        string id;
        int iid = 0;

        ifstream inputFile(filePath); // Open the file
        // Read the header
        getline(inputFile, line);

        if (!inputFile.is_open()) {
            cerr << "Error opening file!" << endl;
            exit(-1);
        }

        // Read the header
        //getline(inputFile, line);

        // Read and process the CSV data here
        while (getline(inputFile, line)) {
            // Process each line (e.g., split into tokens)
            istringstream lineStream(line);
            int i = 1;
            while (getline(lineStream, cell, ',')) {
                if (i == 1) {
                    type = cell;
                    i++;
                } else if (i == 2) {
                    name = cell;
                    i++;
                } else if (i == 3) {
                    amount = cell;
                    i++;
                } else if (i == 4) {
                    id = cell;
                    i++;
                }
            }
            //cout << "type: " << type << " name: " << name << " amount: " << amount << " id: " << id << endl;
            famount = stof(amount);
            iid = stoi(id);

            if (type == "1") {
                CheckingAccount* check = new CheckingAccount(famount, iid,name);
                idMap[stoi(id)] = check;
                nameMap[name] = check;
            } else if (type == "2") {
                SavingsAccount* save = new SavingsAccount(famount, iid, name);
                idMap[stoi(id)] = save;
                nameMap[name] = save;
            } else if (type == "3") {
                InvestmentAccount *invest = new InvestmentAccount(famount, iid, name);
                idMap[stoi(id)] = invest;
                nameMap[name] = invest;
            }
        }


        ////////////////////////////////////

        cout << "1. Display all accounts" << endl;
        cout << "2. Display all of account type" << endl;
        cout << "3. Find account" << endl;
        string optionS;
        int option;
        getline(cin, optionS);
        option = stoi(optionS);

        // Work with maps to complete tasks above!
        ///////////////////////////////////////////////////

        // Iterate over the map and display the pointer values
        if (option == 1) {
            for (const auto& pair : idMap) {
                int accountId = pair.first;
                BankAccount* accountPtr = pair.second;

                if (typeid(*accountPtr) == typeid(CheckingAccount)) {
                    accountPtr->Display();
                } else if (typeid(*accountPtr) == typeid(SavingsAccount)) {
                    accountPtr->Display();
                } else if (typeid(*accountPtr) == typeid(InvestmentAccount)) {
                    accountPtr->Display();
                }

                //std::cout << "Account ID: " << accountId << ", Pointer Value: " << accountPtr << std::endl;
            }

        } else if (option == 2) {
            // Checking Accounts
            for (const auto& pair : idMap) {
                int accountId = pair.first;
                BankAccount *accountPtr = pair.second;

                if (typeid(*accountPtr) == typeid(CheckingAccount)) {
                    accountPtr->Display();
                }
            }


            // Savings Accounts
            for (const auto& pair : idMap) {
                int accountId = pair.first;
                BankAccount *accountPtr = pair.second;

                if (typeid(*accountPtr) == typeid(SavingsAccount)) {
                    accountPtr->Display();
                }
            }

            // Investment Accounts
            for (const auto& pair : idMap) {
                int accountId = pair.first;
                BankAccount *accountPtr = pair.second;

                if (typeid(*accountPtr) == typeid(InvestmentAccount)) {
                    accountPtr->Display();
                }
            }

        } else if (option == 3) {
            //string input = "1021";
            string input = "Everly Merritt";
            bool isInteger = true;

            for (char c : input) {
                if (!std::isdigit(c)) {
                    isInteger = false;
                }
            }

            if (isInteger) {
                // id search
                auto idfound = idMap.find(stoi(input));
                if (idfound != idMap.end()) {
                    BankAccount *accountPtr = idfound->second;

                    if (typeid(*accountPtr) == typeid(CheckingAccount)) {
                        accountPtr->Display();
                    } else if (typeid(*accountPtr) == typeid(SavingsAccount)) {
                        accountPtr->Display();
                    } else if (typeid(*accountPtr) == typeid(InvestmentAccount)) {
                        accountPtr->Display();
                    }
                } else {
                    cout << "Not Found" << std::endl;
                }
            } else {
                auto namefound = nameMap.find(input);
                if (namefound != nameMap.end()) {
                    BankAccount *accountPtr = namefound->second;

                    if (typeid(*accountPtr) == typeid(CheckingAccount)) {
                        accountPtr->Display();
                    } else if (typeid(*accountPtr) == typeid(SavingsAccount)) {
                        accountPtr->Display();
                    } else if (typeid(*accountPtr) == typeid(InvestmentAccount)) {
                        accountPtr->Display();
                    }
                } else {
                    cout << "Not Found" << std::endl;
                }
            }

        }

        // Clean up memory (delete dynamically allocated objects)
        //for (const auto& pair : idMap) {
        //    delete pair.second;
        //}
        //////////////////////////////////////////////////
    }
};

int main(int argc, char** argv) {
    // Use your functor here
    string inputFile = argv[1];

    // Create an instance of idMap
    AccountReader accountReader;
    accountReader(inputFile);

}