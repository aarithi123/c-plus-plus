#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Cell.h"
#include <chrono>
#include "Leaderboard.h"
#include "Textures.h"
using namespace std;

class Board {
public:
    int width = 25;
    int height = 16;
    vector<vector<Tile>> gameBoard;
    sf::Texture flag, mine, hide, show, happy, lose, win, ldr, pause, play, debug, digits;
    sf::Texture one, two, three, four, five, six, seven, eight;
    sf::Texture digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9, digit_negative;
    map<string, sf::Texture> jpgList = {
            {"flag", flag},{"mine", mine},{"tile_hidden", hide},{"tile_revealed", show},
            {"face_happy", happy}, {"face_lose", lose},{"face_win", win}, {"leaderboard", ldr},
            {"pause", pause}, {"play", play}, {"debug", debug}
    };

    vector<string> leaderNames;
    vector<sf::Sprite> mineField;
    int mineCount = 50;
    int timer = 0;
    int flagCount = 0;
    int showTiles = 0;
    int goodTiles = 0;
    map<string, Cell> buttons;
    vector<Tile*> mineTiles;
    sf::RenderWindow* leaderWindow;
    time_t initTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    sf::Text* windowText;
    bool showMines = false;
    bool gameOver = false;
    bool isPaused = false;
    bool neg = true;
    bool inDebug = false;
    string playerName = "";
    string* displayMarker = nullptr;

    void buildBoard();
    void addMines();
    void resetGame();
    void updateMinesCount();
    Board(const string &playerName, int boardWidth, int boardHeight, int totalMines, sf::RenderWindow &_leaderWindow, sf::Text &_scoreText);
    void clickFlag(const sf::Vector2f& xy_coordinates);
    void renderTiles(sf::RenderWindow& window);
    void ShowHideTile(bool hideTile = false);
    void updateClockTime();
    void setClockTime(const time_t& time);
    void initailizeCounterClockPNGImages(const vector<pair<string, pair<int, int>>>& baseButtons);
    void buttonClick(const sf::Vector2f& xy_coordinates);
};