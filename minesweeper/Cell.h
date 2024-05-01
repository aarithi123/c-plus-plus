#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;


class Cell {
public:
    sf::Sprite cell;
    map<string, sf::Sprite> sprites = {{"cell", cell}};

public:
    Cell();
    Cell(sf::Texture& data, const float& x, const float& y);
    void drawSprite(sf::RenderWindow& window, bool paused = false);
    bool inBoard(const sf::Vector2f& coordinates);
    void setSprite(const string& name, sf::Texture& data);
    void addSprite(const sf::Texture& data, const string& name, const float& x = 0, const float& y = 0);
    void deleteSprite(const string& name);

};

class Tile: public Cell {
public:
    bool hasMine = false;
    bool hasFlag = false;
    bool isRevealed = false;
    int proximityMines = 0;
    vector<Tile*> tileList;
    vector<Tile*> adjacentSafeTiles;
public:

    Tile(sf::Texture& data, const int& x, const int& y);
    void show(const std::map<string, sf::Texture> &textures, int &revCount, set<Tile*> &adjacentTiles);
    void updateAdjacentSafeTiles();
    bool toReveal();
    bool hasBomb();
    void linkAdjacentTile(Tile* adj);
    sf::Vector2f getCoordinates();
    bool setMine();
    void safe(sf::Texture& data);
    bool setGameWon(sf::Texture& data, bool gameWon = false);
};