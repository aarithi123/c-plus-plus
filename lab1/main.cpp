#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace  std;

int main() {
    // initialize variables
    char delimiter = ',';
    int i = 0;
    int x = 0;
    string ast;
    string input;
    string para1;
    string para2;
    string para3;
    vector<string> result;
    vector<string> cond1;
    vector<int> cond2;
    bool loop = true;

    cout << "Enter a title for the data:";
    cout << endl;
    string title;
    getline(cin, title);
    cout << "You entered: " << title << endl;
    cout << "Enter the column 1 header:";
    cout << endl;
    string col1;
    getline(cin, col1);
    cout << "You entered: " << col1 << endl;
    cout << "Enter the column 2 header:";
    cout << endl;
    string col2;
    getline(cin, col2);
    cout << "You entered: " << col2 << endl;
    // loop until user enters -1
    while (true) {
        cout << "Enter a data point (-1 to stop input):";
        getline(cin, input);
        if (input == "-1") {
            break;
        } else {
            int res = 0;
            for (int j = 0; j < input.size(); j++) {

                // checking character in string
                if (input.at(j) == ',')
                    res++;
            }
            // store user input in one variable
            result.erase(result.begin(), result.end());
            stringstream original(input);
            while (getline(original, para1, delimiter)) {
                result.push_back(para1);
            }
            while (getline(original, para1, delimiter)) {
                result.push_back(para1);
            }
            if (res == 0) {
                cout << endl;
                cout << "Error: No comma in string." << endl;
            } else if (res > 1) {
                cout << endl;
                cout << "Error: Too many commas in input." << endl;
            }
                // catch errors
            else {
                para2 = result[0];
                para3 = result[1];
                try {
                    i = stoi(para3);
                    cout << endl;
                    cout << "Data string: " << para2 << endl;
                    cout << "Data integer: " << i << endl;
                    cond1.push_back(para2);
                    cond2.push_back(i);
                } catch (exception &e) {
                    cout << endl;
                    cout << "Error: Comma not followed by an integer." << endl;
                }
            }
        }
    }
    // print data in chart format
    cout << endl;
    cout << endl;
    cout << setw(33) << title << endl;
    cout << setw(20) << left << col1 << "|" << setw(23) << right << col2 << endl;
    cout << setw(20)  <<  "--------------------------------------------" << endl;
    for (int k = 0; k < cond1.size(); k++) {
        cout << setw(20) << left << cond1[k] << "|" << setw(23) << right << cond2[k] << endl;
    }
    cout << endl;
    // print data with *
    for (int k = 0; k < cond1.size(); k++) {
        x = cond2[k];
        cout << setw(20) << right << cond1[k] << " " << string(x, '*') << endl;
    }

    cout << "=========================";

    return 0;
}