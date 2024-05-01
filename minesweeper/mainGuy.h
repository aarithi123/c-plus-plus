#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Cell.h"
#include "Leaderboard.h"
#include "Textures.h"
#include "Board.h"
#include <iostream>
using namespace std;

class mainGuy {
public:

    void pollEvents(sf::RenderWindow &gameWindow, Board &board) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.buttonClick(gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow)));
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    board.clickFlag(gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow)));
                }
            }
        }
    }

    void renderGameWindow(sf::RenderWindow &gameWindow, Board &board) {
        gameWindow.clear(sf::Color(255, 255, 255));
        board.updateClockTime();
        board.renderTiles(gameWindow);
        gameWindow.display();
    }

    void pollLeaderboard(sf::RenderWindow &leaderW, Board &board) {
        sf::Event event;
        while (leaderW.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                board.setClockTime(chrono::system_clock::to_time_t(chrono::system_clock::now()));
                board.ShowHideTile();
                leaderW.close();
            }
        }
    }

    void renderLeaderboardWindow(sf::RenderWindow &leaderW, sf::Text &leaderText, sf::Text &txt) {
        leaderW.clear(sf::Color(0, 0, 255));
        leaderW.draw(leaderText);
        leaderW.draw(txt);
        leaderW.display();
    }

    void playGame(const string &playerName, const int &width, const int &height, const int &mineCount) {
        sf::RenderWindow gameWindow(sf::VideoMode(32 * width, 32 * height + 100), "Aarithi Rajendren");
        gameWindow.setFramerateLimit(60);
        sf::RenderWindow leaderW;
        leaderW.setFramerateLimit(60);
        sf::Font font;
        if (!font.loadFromFile("files/font.ttf")) {
            cout << "No such font exists" << endl;
        }
        sf::Text leaderText = alignText("LEADERBOARD", 20, 16 * width, 16 * height / 2.0f - 120, font);
        sf::Text txt = alignText("", 18, 16 * width, 16 * height / 2.0f + 20, font);
        Board board(playerName, width, height, mineCount, leaderW, txt);

        while (gameWindow.isOpen()) {
            if (!leaderW.isOpen()) {
                pollEvents(gameWindow, board);
            }
            renderGameWindow(gameWindow, board);

            if (leaderW.isOpen()) {
                pollLeaderboard(leaderW, board);
                renderLeaderboardWindow(leaderW, leaderText, txt);
            }
        }
    }


    sf::Text alignText(const string &txt, const int &size, const float &x, const float &y, const sf::Font &font) {
        sf::Text input;
        string str = txt;
        input.setFont(font);
        input.setString(txt);
        input.setCharacterSize(size);
        if (str != "" && str != "Enter your name:") {
            input.setStyle(sf::Text::Bold | sf::Text::Underlined);
        } else {
            input.setStyle(sf::Text::Bold);
        }
        input.setOrigin(input.getLocalBounds().width / 2, input.getLocalBounds().height / 2);
        input.setPosition(x / 2.0f, y);

        return input;
    }
};

