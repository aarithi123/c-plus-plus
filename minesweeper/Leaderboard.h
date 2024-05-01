#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include <fstream>

class LeaderBoard {
public:
private:
    string playerName;
    string* displayMarker;
    bool moreTime = true;


public:

    void loadLeaders(vector<string>& namesList);
    void saveLeaders(vector<string>& namesList);
    string* insertLeader(vector<string>& namesList, string& newEntry, int timeElapsed, string* asterisk);
    string formatLeaderList(vector<string>& namesList);
    string formatTime(int minutes, int seconds);

};
