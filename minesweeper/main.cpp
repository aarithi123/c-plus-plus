using namespace std;
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Cell.h"
#include "Leaderboard.h"
#include "Textures.h"
#include "mainGuy.h"
#include <iostream>

int main() {

// Load game settings from a configuration file
    int gridWidth = 25;
    int gridHeight = 16;
    int totalMines = 50;
    ifstream configFile("files/config.cfg");
    if (configFile.is_open()) {
            string numberStr;
            getline(configFile, numberStr);
            gridWidth = stoi(numberStr);
            gridWidth = max(22, min(gridWidth, 255));
            getline(configFile, numberStr);
            gridHeight = stoi(numberStr);
            gridHeight = max(16, min(gridHeight, 250));
            getline(configFile, numberStr);
            totalMines = stoi(numberStr);
            totalMines = min(totalMines, gridWidth * gridHeight);
        }
    configFile.close();

// Initialize the welcome screen for the game
    sf::RenderWindow introWindow(sf::VideoMode(32 * gridWidth, (32 * gridHeight) + 100), "Aarithi Rajendren");
    introWindow.setFramerateLimit(60);
    sf::Font gameFont;
    if (!gameFont.loadFromFile("files/font.ttf")) {
        cout << "Missing font file: files/font.ttf" << endl;
    }
    mainGuy playerObject;

// Create text elements for the welcome screen
    sf::Text titleText = playerObject.alignText("MINESWEEPER GAME START", 24, 32 * gridWidth,
                                                32 * gridHeight / 2.0f - 150, gameFont);
    sf::Text promptText = playerObject.alignText("Enter your name:", 20, 32 * gridWidth, 32 * gridHeight / 2.0f - 75,
                                                 gameFont);
    sf::Text nameText = playerObject.alignText("", 18, 32 * gridWidth, 32 * gridHeight / 2.0f - 45, gameFont);
    nameText.setFillColor(sf::Color::Yellow);
    string playerName;

// Main loop for the welcome screen
    while (introWindow.isOpen()) {
        sf::Event userEvent;
        while (introWindow.pollEvent(userEvent)) {
            if (userEvent.type == sf::Event::Closed) {
                introWindow.close();
            } else if (userEvent.type == sf::Event::TextEntered && playerName.length() < 10) {
                char enteredChar = '\0';
                if (userEvent.text.unicode < 128) {
                    enteredChar = static_cast<char>(userEvent.text.unicode);
                }
                if (isalpha(enteredChar)) {
                    playerName += (playerName.empty() ? toupper(enteredChar) : tolower(enteredChar));
                }
            } else if (userEvent.type == sf::Event::KeyPressed && !playerName.empty()) {
                if (userEvent.key.code == sf::Keyboard::Backspace) {
                    playerName.pop_back();
                } else if (userEvent.key.code == sf::Keyboard::Enter) {
                    introWindow.close();
                    playerObject.playGame(playerName, gridWidth, gridHeight, totalMines);
                }
            }
        }

        introWindow.clear(sf::Color::Blue);
        introWindow.draw(titleText);
        introWindow.draw(promptText);
        nameText.setString(playerName + "|");
        nameText.setOrigin(nameText.getLocalBounds().width / 2, nameText.getLocalBounds().height / 2);
        nameText.setPosition((32 * gridWidth) / 2.0f, (32 * gridHeight / 2.0f - 45));
        introWindow.draw(nameText);
        introWindow.display();
    }
};