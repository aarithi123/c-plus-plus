#include "Cell.h"


Cell::Cell() = default;

// Constructor with parameters to initialize a Cell
Cell::Cell(sf::Texture &texture, const float &posX, const float &posY) {
    sprites.at("cell").setTexture(texture);
    sprites.at("cell").setPosition(posX, posY);
}

// Method to render the Cell on the window
void Cell::drawSprite(sf::RenderWindow &renderWindow, bool isPaused) {
    if (!isPaused) {
        map<string, sf::Sprite>::iterator iter;
        for (iter = sprites.begin(); iter != sprites.end(); iter++) {
            renderWindow.draw(iter->second);
        }
    }
    else {
        renderWindow.draw(sprites.at("cell"));
    }
}

// Checks if a coordinates(x,y) is within the Cell - game board
bool Cell::inBoard(const sf::Vector2f &coordinates) {
    if (sprites.find("cell") != sprites.end()) {
        return sprites.at("cell").getGlobalBounds().contains(coordinates);
    } else {
        return false;
    }
}

// Sets a specific sprite for the Cell
void Cell::setSprite(const string &identifier, sf::Texture &data) {
    sprites.at(identifier).setTexture(data);
}

// Adds a new sprite to the Cell
void Cell::addSprite(const sf::Texture &texture, const string &identifier, const float &posX, const float &posY) {

    sf::Sprite tmp;
    sprites.insert({identifier, tmp});
    sprites.at(identifier).setTexture(texture);
    sprites.at(identifier).setPosition(posX > 0 || posY > 0 ? sf::Vector2f(posX, posY) : sprites.at("cell").getPosition());

}

// Removes a sprite from the Cell
void Cell::deleteSprite(const string &name) {
    sprites.erase(name);
}


// Tile class constructor
Tile::Tile(sf::Texture &texture, const int &gridX, const int &gridY) {
    sprites.at("cell").setTexture(texture);
    sprites.at("cell").setPosition(gridX * 32, gridY * 32);
}

// Reveals the tile and updates the count of revealed tiles
void Tile::show(const std::map<string, sf::Texture> &textures, int &revCount, set<Tile*> &adjacentTiles) {
    if (adjacentTiles.empty()) {
        adjacentTiles.insert(this);
    }
    for (Tile *tile : adjacentTiles) {
        if (tile->isRevealed || tile->hasFlag) continue;
        tile->isRevealed = true;
        revCount++;
        tile->sprites.at("cell").setTexture(textures.at("tile_revealed"));

        if (tile->hasMine) break;
        if (tile->proximityMines > 0) {
            tile->addSprite(textures.at(std::to_string(tile->proximityMines)), "num");
        }
    }

    set<Tile*> newAdjacentTiles;
    for (Tile *tile : adjacentTiles) {
        tile->updateAdjacentSafeTiles();
        if (tile->proximityMines == 0) {
            for (size_t i = 0; i < tile->adjacentSafeTiles.size(); ++i) {
                newAdjacentTiles.emplace(tile->adjacentSafeTiles[i]);
            }

        }
    }
    if (!newAdjacentTiles.empty()) {
        show(textures, revCount, newAdjacentTiles);
    }
}

// Updates the list of safe adjacent tiles
void Tile::updateAdjacentSafeTiles() {
    adjacentSafeTiles.clear();
    for (size_t i = 0; i < tileList.size(); ++i) {
        Tile *ptr = tileList[i];
        if (!ptr->hasMine && !ptr->isRevealed && !ptr->hasFlag) {
            adjacentSafeTiles.push_back(ptr);
        }
    }
}

// Checks if the tile is already revealed
bool Tile::toReveal() {
    return isRevealed;
}

// Checks if the tile contains a mine and also check if flag is set or not
bool Tile::hasBomb() {
    return hasMine && !hasFlag;
}

// Sets a pointer to an adjacent tile
void Tile::linkAdjacentTile(Tile *ptr) {
    this->tileList.push_back(ptr);
    ptr->tileList.push_back(this);
}

// Places a mine on the tile and updates adjacent tiles
bool Tile::setMine() {
    if (hasMine) {
        return false;
    }
    hasMine = true;
    for (Tile* t : tileList) {
        if (t) {
            t->proximityMines += 1;
        }
    }
    return true;
}

// Resets the tile to safe
void Tile::safe(sf::Texture& data) {
    hasFlag = false;
    isRevealed = false;
    hasMine = false;
    proximityMines = 0;
    sprites = { {"cell", sprites.at("cell")} };
    sprites.at("cell").setTexture(data);
}

// Get the coordinates of the tile
sf::Vector2f Tile::getCoordinates() {
    return sprites.at("cell").getPosition();
}

// Set gameWon flag
bool Tile::setGameWon(sf::Texture &data, bool gameWon) {
    hasFlag = !hasFlag;
    if (hasFlag || gameWon) {
        addSprite(data, "flag");
    } else {
        sprites.erase("flag");
    }
    return hasFlag;
}


