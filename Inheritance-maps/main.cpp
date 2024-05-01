#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "BankAccount.h"

using namespace std;

class IdMap {
public:
    // Overload the call operator
    //void operator()(const map<int, const string>& idMap) const {
    void operator()(map<int, BankAccount*>& idMap) const {
        int i = 0;
        for (const auto& pair : idMap) {
            BankAccount* account = idMap[pair.first];

            if (typeid(*account) == typeid(CheckingAccount)) {
                cout << "Checking Account" << endl;
            } else if (typeid(*account) == typeid(SavingsAccount)) {
                cout << "Savings Account" << endl;
            } else if (typeid(*account) == typeid(InvestmentAccount)) {
                cout << "Investment Account" << endl;
            }

            cout << "id: " << account->getID() << endl;
            cout << "name: " << account->getName() << endl;
            i++;
        }

        /*
        for (const auto& pair : idMap) {
            cout << "id: " << pair.first << ", name: " << pair.second << endl;
        }
         */
    }
};

int main(int argc, char *argv[]) {

    cout << argv[1] << endl;

    //ifstream inputFile("accounts.csv");
    ifstream inputFile(argv[1]);
    vector<string> tokens;
    string line;
    string cell;
    string type;
    string name;
    string amount;
    float famount = 0;
    string id;
    int iid = 0;

    map<int, BankAccount*> idMap;


    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Read the header
    getline(inputFile, line);

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
        } else if (type == "2") {
            SavingsAccount* save = new SavingsAccount(famount, iid, name);
            idMap[stoi(id)] = save;
        } else if (type == "3") {
            InvestmentAccount *invest = new InvestmentAccount(famount, iid, name);
            idMap[stoi(id)] = invest;
        }
    }

    // Create an instance of idMap
    IdMap displayMap;

    // Call the operator to display the map elements
    displayMap(idMap);

    inputFile.close();

    // Iterate over the map and delete the pointers
    for (auto it = idMap.begin(); it != idMap.end(); ++it) {
        //delete it->second; // Delete the dynamically allocated memory
        it->second = nullptr;
    }

    // Clear the map (optional)
    idMap.clear();

    return 0;
}