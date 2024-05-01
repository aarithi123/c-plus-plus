#include "Leaderboard.h"

// Method to load leaderboard entries from a file
void LeaderBoard::loadLeaders(vector<string>& namesList) {
    ifstream leaderboardFile("files/leaderboard.txt");
    if (leaderboardFile.is_open()) {
        string entry;
        while (getline(leaderboardFile, entry)) {
            namesList.push_back(entry);
        }
    }
    sort(namesList.begin(), namesList.end());
    leaderboardFile.close();
}

// Method to save leaderboard entries to a file
void LeaderBoard::saveLeaders(vector<string>& namesList) {
    ofstream leaderboardFile;
    leaderboardFile.open("files/leaderboard.txt", ofstream::out | ofstream::trunc);
    if (leaderboardFile.is_open()) {
            for (const auto& name : namesList) {
            leaderboardFile << name;
            if (&name != &namesList.back())
                leaderboardFile << "\n";
        }
    }
    leaderboardFile.close();
    if (displayMarker) {
        *displayMarker += "*";
    }
}

// Method to add a new leader to the leaderboard
string* LeaderBoard::insertLeader(vector<string>& namesList, string& newEntry, int timeElapsed, string* asterisk) {
    playerName = newEntry;
    displayMarker = asterisk;
    int minutes = timeElapsed / 60;
    int seconds = timeElapsed % 60;
    string formattedTimePlayer = formatTime(minutes, seconds) + ", " + playerName;
    if (namesList.size() > 0) {
        for (int index = 0; index < namesList.size(); index++) {
            if (formattedTimePlayer < namesList.at(index)) {
                if (displayMarker != nullptr) {
                    displayMarker->pop_back();
                }
                namesList.insert(namesList.begin() + index, formattedTimePlayer);
                if (namesList.size() > 5) {
                    namesList.pop_back();
                }
                displayMarker = &namesList.at(index);
                saveLeaders(namesList);
                moreTime = false;
                return displayMarker;
            }
        }
        if (moreTime) {
            return displayMarker;
        }
        if (namesList.size() < 5) {
            if (displayMarker != nullptr) {
                displayMarker->pop_back();
            }
            namesList.push_back(formattedTimePlayer);
            displayMarker = &namesList.at(namesList.size() - 1);
            saveLeaders(namesList);
            return displayMarker;
        }
    }
    return displayMarker;
}

// Method to format the leaderboard for display
string LeaderBoard::formatLeaderList(vector<string>& namesList) {
    string formattedList;
    for (size_t i = 0; i < namesList.size(); ++i) {
        formattedList += to_string(i + 1) + ".\t" + namesList[i].substr(0, 5) + "\t" + namesList[i].substr(6);
        if (i < namesList.size() - 1) formattedList += "\n\n";
    }
    return formattedList;
}

// Helper method to format time as MM:SS
string LeaderBoard::formatTime(int minutes, int seconds) {
    string minTens = to_string(minutes / 10 % 10);
    string minOnes = to_string(minutes % 10);
    string secTens = to_string(seconds / 10 % 10);
    string secOnes = to_string(seconds % 10);
    return minTens + minOnes + ":" + secTens + secOnes;
}
