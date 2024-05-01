#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Weapon {
public:
    string name;
    int powerRating;
    float powerConsumption;

    Weapon(string weaponName, int powerR, float powerC) {
        name = weaponName;
        powerRating = powerR;
        powerConsumption = powerC;
    }

    void Display() {
        cout << name << ", " << powerRating << ", " << powerConsumption << endl;
    }

    int GetPower() {
        return powerRating;
    }
};

class Ship {
public:
    string shipName;
    string shipType;
    short length;
    int shieldCapacity;
    float maxWarp;
    int weaponNumber;
    vector<Weapon> weapon;
    int firepower = 0;
    vector<Ship> ships;

    Ship(string name, string type, short length1, int shieldCap, float warp, int weaponCount) {
        shipName = name;
        shipType = type;
        length = length1;
        shieldCapacity = shieldCap;
        maxWarp = warp;
        weaponNumber = weaponCount;
    }

    void AddWeapon(Weapon w) {
        weapon.push_back(w);
    }

    void Display() {
        cout << "Name: " << shipName << endl << "Class: " << shipType << endl << "Length: " << length << endl
             << "Shield capacity: " << shieldCapacity << endl << "Maximum Warp: " << maxWarp << endl << "Armaments: "
             << endl;
        for (int r = 0; r < weapon.size(); r++) {
            weapon[r].Display();
        }
    }

    vector<Weapon> GetWeapon() {
        return weapon;
    }

    int TotalFirepower() {
        firepower = 0;
        for (int i = 0; i < weapon.size(); i++) {
            firepower += weapon[i].GetPower();
        }
        return firepower;
    }
};

vector<Ship> openFile(string fileName) {
    int numberOfShips = 0;
    int lengthOfShipName = 0;
    int lengthOfClass = 0;
    int numberOfWeapons = 0;
    int lengthOfWeaponName = 0;
    int shieldCapacity = 0;
    int powerRating = 0;
    float powerConsumption;
    float maxWarp = 0;
    short shipLength = 0;
    string shipClass;
    string shipName;
    string weaponName;
    char* tempName;
    vector<Ship> ships;

    fstream myFile;
    myFile.open(fileName, ios::in | ios::binary);
    if (myFile.is_open()) {
        myFile.read((char *) (&numberOfShips), sizeof(numberOfShips));
        //cout << numberOfShips << endl;

        for (int x = 0; x < numberOfShips; x++) {

            myFile.read((char *) (&lengthOfShipName), sizeof(lengthOfShipName));

            tempName = new char[lengthOfShipName];
            myFile.read(tempName, lengthOfShipName);
            shipName = tempName;
            delete tempName;

            myFile.read((char *) (&lengthOfClass), sizeof(lengthOfClass));
            //cout << lengthOfClass << endl;

            tempName = new char[lengthOfClass];
            myFile.read(tempName, lengthOfClass);
            //cout << tempName << endl;
            shipClass = tempName;
            delete tempName;

            myFile.read((char *) (&shipLength), sizeof(shipLength));
            //cout << shipLength << endl;

            myFile.read((char *) (&shieldCapacity), sizeof(shieldCapacity));
            //cout << shieldCapacity << endl;

            myFile.read((char *) (&maxWarp), sizeof(maxWarp));
            //cout << maxWarp << endl;

            myFile.read((char *) (&numberOfWeapons), sizeof(numberOfWeapons));
            //cout << numberOfWeapons << endl;

            // create ship object
            Ship ship1(shipName, shipClass, shipLength, shieldCapacity, maxWarp, numberOfWeapons);

            for (int i = 0; i < numberOfWeapons; i++) {
                myFile.read((char *) (&lengthOfWeaponName), sizeof(lengthOfWeaponName));
                //cout << lengthOfWeaponName << endl;

                tempName = new char[lengthOfWeaponName];
                myFile.read(tempName, lengthOfWeaponName);
                //cout << tempName << endl;
                weaponName = tempName;
                delete tempName;

                myFile.read((char *) (&powerRating), sizeof(powerRating));
                //cout << powerRating << endl;

                myFile.read((char *) (&powerConsumption), sizeof(powerConsumption));
                //cout << powerConsumption << endl;

                // create weapon object
                Weapon w1(weaponName, powerRating, powerConsumption);
                ship1.AddWeapon(w1);
            }
            ships.push_back(ship1);
        }
    }
    return ships;
}


int main() {
    int x = 0;
    int previousNum = 0;
    int menuOption = 0;
    int options = 0;
    vector<Ship> ships;
    vector<Ship> ship1;
    string previousName;
    cout << "1. Friendly ships" << endl << "2. Enemy ships" << endl << "3. Friendly ships and Enemy ships" << endl << "Please enter a menu option: ";
    cin >> menuOption;

    if (menuOption == 1) {
        ships = openFile("friendlyships.shp");
        cout << "1. Print all the ships" << endl << "2. Print the starship with the most powerful weapon" << endl << "3. Print the most powerful ship" << endl << "4. Print the weakest ship" << endl << "5. Print the unarmed ship" << endl << "Please pick a menu option: ";
        cin >> options;
        if (options == 1) {
            // print ships
            for (int p = 0; p < ships.size(); p++) {
                // unarmed ships
                if (ships[p].GetWeapon().size() == 0) {
                    ships[p].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                    // armed ships
                } else {
                    ships[p].Display();
                    x = ships[p].TotalFirepower();
                    cout << "Total firepower: " << x << endl;
                    cout << "\n";
                }
            }
        }
        else if (options == 2) {
            // loop through ship and weapon vectors to find most powerful weapon
            for (int z = 0; z < ships.size(); z++) {
                for (int a = 0; a < ships[z].GetWeapon().size(); a++) {
                    if (ships[z].weapon[a].GetPower() < previousNum) {
                        continue;
                    } else {
                        previousNum = ships[z].weapon[a].GetPower();
                        previousName = ships[z].shipName;
                    }
                }
            }
            cout << "The starship that has the most powerful weapon is " << previousName << " and it's power is "
                 << previousNum << endl;
        }
        else if (options == 3) {
            // find the most powerful ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].TotalFirepower() < previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The most powerful starship is " << previousName << " and it's power rating is " << previousNum
                 << endl;
        }
        else if (options == 4) {
            // find the weakest ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    continue;
                } else if (i == 0) {
                    previousNum = ships[i].TotalFirepower();
                } else if (ships[i].TotalFirepower() > previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The weakest starship is " << previousName << " and it's power rating is " << previousNum << endl;
        }
        else if (options == 5) {
            // print the unarmed ships
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    ships[i].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                } else {
                    continue;
                }
            }
        }
    }
    else if (menuOption == 2) {
        ships = openFile("enemyships.shp");
        cout << "1. Print all the ships" << endl << "2. Print the starship with the most powerful weapon" << endl << "3. Print the most powerful ship" << endl << "4. Print the weakest ship" << endl << "5. Print the unarmed ship" << endl << "Please pick a menu option: ";
        cin >> options;
        if (options == 1) {
            // print ships
            for (int p = 0; p < ships.size(); p++) {
                // unarmed ships
                if (ships[p].GetWeapon().size() == 0) {
                    ships[p].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                    // armed ships
                } else {
                    ships[p].Display();
                    x = ships[p].TotalFirepower();
                    cout << "Total firepower: " << x << endl;
                    cout << "\n";
                }
            }
        }
        else if (options == 2) {
            // loop through ship and weapon vectors to find most powerful weapon
            for (int z = 0; z < ships.size(); z++) {
                for (int a = 0; a < ships[z].GetWeapon().size(); a++) {
                    if (ships[z].weapon[a].GetPower() < previousNum) {
                        continue;
                    } else {
                        previousNum = ships[z].weapon[a].GetPower();
                        previousName = ships[z].shipName;
                    }
                }
            }
            cout << "The starship that has the most powerful weapon is " << previousName << " and it's power is "
                 << previousNum << endl;
        }
        else if (options == 3) {
            // find the most powerful ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].TotalFirepower() < previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The most powerful starship is " << previousName << " and it's power rating is " << previousNum
                 << endl;
        }
        else if (options == 4) {
            // find the weakest ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    continue;
                } else if (i == 0) {
                    previousNum = ships[i].TotalFirepower();
                } else if (ships[i].TotalFirepower() > previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The weakest starship is " << previousName << " and it's power rating is " << previousNum << endl;
        }
        else if (options == 5) {
            // print the unarmed ships
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    ships[i].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                } else {
                    continue;
                }
            }
        }
        }
    else if (menuOption == 3) {
        ships = openFile("friendlyships.shp");
        ship1 = openFile("enemyships.shp");
        ships.insert(ships.end(), ship1.begin(), ship1.end());
        cout << "1. Print all the ships" << endl << "2. Print the starship with the most powerful weapon" << endl << "3. Print the most powerful ship" << endl << "4. Print the weakest ship" << endl << "5. Print the unarmed ship" << endl << "Please pick a menu option: ";
        cin >> options;
        if (options == 1) {
            // print ships
            for (int p = 0; p < ships.size(); p++) {
                // unarmed ships
                if (ships[p].GetWeapon().size() == 0) {
                    ships[p].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                    // armed ships
                } else {
                    ships[p].Display();
                    x = ships[p].TotalFirepower();
                    cout << "Total firepower: " << x << endl;
                    cout << "\n";
                }
            }
        }
        else if (options == 2) {
            // loop through ship and weapon vectors to find most powerful weapon
            for (int z = 0; z < ships.size(); z++) {
                for (int a = 0; a < ships[z].GetWeapon().size(); a++) {
                    if (ships[z].weapon[a].GetPower() < previousNum) {
                        continue;
                    } else {
                        previousNum = ships[z].weapon[a].GetPower();
                        previousName = ships[z].shipName;
                    }
                }
            }
            cout << "The starship that has the most powerful weapon is " << previousName << " and it's power is "
                 << previousNum << endl;
        }
        else if (options == 3) {
            // find the most powerful ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].TotalFirepower() < previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The most powerful starship is " << previousName << " and it's power rating is " << previousNum
                 << endl;
        }
        else if (options == 4) {
            // find the weakest ship
            previousNum = 0;
            previousName = "";
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    continue;
                } else if (i == 0) {
                    previousNum = ships[i].TotalFirepower();
                } else if (ships[i].TotalFirepower() > previousNum) {
                    continue;
                } else {
                    previousNum = ships[i].TotalFirepower();
                    previousName = ships[i].shipName;
                }
            }
            cout << "The weakest starship is " << previousName << " and it's power rating is " << previousNum << endl;
        }
        else if (options == 5) {
            // print the unarmed ships
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].GetWeapon().size() == 0) {
                    ships[i].Display();
                    cout << "Unarmed" << endl;
                    cout << "\n";
                } else {
                    continue;
                }
            }
        }
    }

    return 0;
}
