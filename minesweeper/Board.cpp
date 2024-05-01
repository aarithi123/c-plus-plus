#include "Board.h"
#include "Leaderboard.h"

// build the board
void Board::buildBoard() {
    gameBoard.clear();
    for (int i = 0; i < height; i++) {
        vector<Tile> row;
        for (int j = 0; j < width; j++) {
            Tile newTile(jpgList.at("tile_hidden"), j, i);
            row.push_back(newTile);
        }
        gameBoard.push_back(row);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j + 1 != width) gameBoard.at(i).at(j).linkAdjacentTile(&gameBoard.at(i).at(j + 1));
            if (i > 0) {
                gameBoard.at(i).at(j).linkAdjacentTile(&gameBoard.at(i - 1).at(j)); //Below
                if (j + 1 != width) gameBoard.at(i).at(j).linkAdjacentTile(&gameBoard.at(i - 1).at(j + 1));
                if (j > 0) gameBoard.at(i).at(j).linkAdjacentTile(&gameBoard.at(i - 1).at(j - 1));
            }
        }
    }
    addMines();
}

// Add mines across the game board
void Board::addMines() {
    int minesPlaced = 0;
    int row = 0;
    int col = 0;

    while (minesPlaced < mineCount) {
        row = rand() % gameBoard.size();
        col = rand() % gameBoard[0].size();
        if (gameBoard.at(row).at(col).setMine()) {
            ++minesPlaced;
            sf::Sprite mineSprite;
            mineField.push_back(mineSprite);
            mineField.back().setTexture(jpgList.at("mine"));
            mineField.back().setPosition(gameBoard[row][col].getCoordinates());
            mineTiles.push_back(&gameBoard[row][col]);
        }
    }
    for (int i = 0; i < gameBoard.size(); i++) {
        for (int j = 0; j < gameBoard[i].size(); j++) {
            gameBoard[i][j].updateAdjacentSafeTiles();
        }
    }
}


// reset the game board
void Board::resetGame() {
    mineTiles.clear();
    mineField.clear();
    if (!inDebug) showMines = false;
    gameOver = false;
    isPaused = false;
    flagCount = 0;
    showTiles = 0;
    timer = 0;
    setClockTime(chrono::system_clock::to_time_t(chrono::system_clock::now()));
    buttons.at("clock").setSprite("MinuteLeftDigit", jpgList.at("digit_0"));
    buttons.at("clock").setSprite("MinuteRightDigit", jpgList.at("digit_0"));
    buttons.at("clock").setSprite("SecondLeftDigit", jpgList.at("digit_0"));
    buttons.at("clock").setSprite("SecondRightDigit", jpgList.at("digit_0"));
    buttons.at("face_happy").setSprite("cell", jpgList.at("face_happy"));

    for (size_t i = 0; i < gameBoard.size(); i++) {
        for (size_t j = 0; j < gameBoard[i].size(); j++) {
            gameBoard[i][j].safe(jpgList.at("tile_hidden"));
        }
    }

    updateMinesCount();
    addMines();
}

// update the mine counter based on flag count set
void Board::updateMinesCount() {
    int count = mineCount - flagCount;
    if (count >= 0 && neg) { buttons.at("mineCounter").deleteSprite("cell"); neg = false; }
    else if (count < 0 && !neg) { buttons.at("mineCounter").addSprite(jpgList.at("digit_negative"), "cell", 12, 32 * (height + 0.5f) + 16); neg = true; }
    count = abs(count);
    buttons.at("mineCounter").setSprite("hundreds", jpgList.at("digit_" + to_string(count / 100 % 10)));
    buttons.at("mineCounter").setSprite("tens", jpgList.at("digit_" + to_string(count / 10 % 10)));
    buttons.at("mineCounter").setSprite("ones", jpgList.at("digit_" + to_string(count % 10)));
}

// Constructor for the GameBoard class
Board::Board(const string &name, int boardWidth, int boardHeight, int totalMines, sf::RenderWindow &leaderBoardWindow, sf::Text &textScore) {
    Textures texture;
    LeaderBoard leaderBoard;
    width = boardWidth;
    height = boardHeight;
    mineCount = totalMines;
    goodTiles = boardWidth * boardHeight - totalMines;
    playerName = name;
    flagCount = 0;
    leaderWindow = &leaderBoardWindow;
    windowText = &textScore;
    srand((unsigned)(time(nullptr)) + width + height + mineCount + playerName.size());
    string leaderboardEntries;
    texture.loadNamedTextures(jpgList);

    map<int, sf::Texture> numeralTextures = {{1, one}, {2, two}, {3, three}, {4, four}, {5, five}, {6, six}, {7, seven}, {8, eight}};
    vector<std::pair<std::string, sf::Texture>> digitTextures = { {"digit_0", digit_0},{"digit_1", digit_1},{"digit_2", digit_2},{"digit_3", digit_3},{"digit_4", digit_4},{"digit_5", digit_5},{"digit_6", digit_6},{"digit_7", digit_7},{"digit_8", digit_8},{"digit_9", digit_9},{"digit_negative", digit_negative} };
    texture.loadNumberTextures(numeralTextures, jpgList);
    texture.loadDigitTextures(digitTextures, jpgList);

    buildBoard();
    initailizeCounterClockPNGImages({
                              {"face_happy", {(boardWidth / 2.0f) * 32 - 32, 32 * (boardHeight + 0.5f)}},
                              {"debug", {boardWidth * 32 - 304, 32 * (boardHeight + 0.5f)}},
                              {"pause", {boardWidth * 32 - 240, 32 * (boardHeight + 0.5f)}},
                              {"leaderboard", {boardWidth * 32 - 176, 32 * (boardHeight + 0.5f)}}
                      });

    leaderBoard.loadLeaders(leaderNames);
    leaderboardEntries = leaderBoard.formatLeaderList(leaderNames);
    windowText->setString(leaderboardEntries);
    sf::FloatRect textBounds = windowText->getLocalBounds();
    windowText->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    windowText->setPosition(16 * boardWidth / 2.0f, 16 * boardHeight / 2.0f + 20);
    updateMinesCount();
}

// set the flag and adjust flagCount based on rightClick
void Board::clickFlag(const sf::Vector2f &xy_coordinates) {
    if (!isPaused && !gameOver) {
        for (size_t i = 0; i < gameBoard.size(); i++) {
            for (size_t j = 0; j < gameBoard[i].size(); j++) {
                if (gameBoard[i][j].inBoard(xy_coordinates)) {
                    if (!gameBoard[i][j].toReveal()) {
                        if (gameBoard[i][j].setGameWon(jpgList.at("flag"))) {
                            flagCount += 1;
                        } else {
                            flagCount -= 1;
                        }
                        updateMinesCount();
                    }
                }
            }
        }
    }
}

// Renders the windows and buttons/images on the game window
void Board::renderTiles(sf::RenderWindow &renderWindow) {
    bool hideTiles = false;
    hideTiles = isPaused || (leaderWindow->isOpen() && !gameOver);

    for (size_t i = 0; i < gameBoard.size(); i++) {
        for (size_t j = 0; j < gameBoard[i].size(); j++) {
            gameBoard[i][j].drawSprite(renderWindow, hideTiles);
        }
    }
    for (auto &buttonPair : buttons) {
        buttonPair.second.drawSprite(renderWindow);
    }
    if (showMines && !hideTiles) {
        for (size_t i = 0; i < mineField.size(); i++) {
            renderWindow.draw(mineField[i]);
        }
    }
}

//toggle reveal and hide tile based pause/play
void Board::ShowHideTile(bool hideTile) {
    for (size_t i = 0; i < gameBoard.size(); i++) {
        for (size_t j = 0; j < gameBoard[i].size(); j++) {
            if (isPaused || hideTile) {
                gameBoard[i][j].setSprite("cell", jpgList.at("tile_revealed"));
            }
            else if (!gameBoard[i][j].toReveal()) {
                gameBoard[i][j].setSprite("cell", jpgList.at("tile_hidden"));
            }
        }
    }

}

//update the clock when the game is ON
void Board::updateClockTime() {
    if (!leaderWindow->isOpen() && !isPaused && !gameOver) {
        time_t timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        double time = difftime(timeNow, initTime);
        if (time >= 1) {
            initTime = timeNow;
            timer += 1;
            if (timer >= 6000) timer = 0;

            int minutes = timer / 60;
            int seconds = timer - (minutes * 60);
            buttons.at("clock").setSprite("MinuteLeftDigit", jpgList.at("digit_" + to_string(minutes / 10 % 10)));
            buttons.at("clock").setSprite("MinuteRightDigit", jpgList.at("digit_" + to_string(minutes % 10)));
            buttons.at("clock").setSprite("SecondLeftDigit", jpgList.at("digit_" + to_string(seconds / 10 % 10)));
            buttons.at("clock").setSprite("SecondRightDigit", jpgList.at("digit_" + to_string(seconds % 10)));
        }
    }
}

// Set initial time_t from system clock
void Board::setClockTime(const time_t &time) {
    initTime = time;
}

// Function to handle click button on the game board
void Board::buttonClick(const sf::Vector2f &xy_coordinates) {
    LeaderBoard leaderBoard;
    string names = "";
    for (auto &buttonPair : buttons) {
        if (buttonPair.second.inBoard(xy_coordinates)) {
            const string &buttonKey = buttonPair.first;
            if (buttonKey == "face_happy") {
                resetGame();
            } else if (buttonKey == "pause" && !gameOver) {
                isPaused = !isPaused;
                buttonPair.second.setSprite("cell", jpgList.at("play"));
                ShowHideTile();
                if (!isPaused) {
                    buttonPair.second.setSprite("cell", jpgList.at("pause"));
                    ShowHideTile();
                    setClockTime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
                }
            } else if (buttonKey == "debug" && !isPaused && !gameOver) {
                inDebug = !inDebug;
                showMines = !showMines;
            } else if (buttonKey == "leaderboard") {
                leaderWindow->create(sf::VideoMode(16 * width, 16 * height + 50), "Aarithi Rajendren");
                if (!gameOver) {
                    ShowHideTile(true);
                }
            }
        }
    }

    if (!gameOver && !isPaused) {
        for (size_t row = 0; row < gameBoard.size(); row++) {
            for (size_t col = 0; col < gameBoard[row].size(); col++) {
                Tile &currentTile = gameBoard[row][col];
                if (!currentTile.toReveal() && currentTile.inBoard(xy_coordinates)) {
                    if (currentTile.hasBomb()) {
                        gameOver = true;
                        showMines = true;
                        for (size_t k = 0; k < mineTiles.size(); k++) {
                            mineTiles[k]->setSprite("cell", jpgList.at("tile_revealed"));
                        }
                        buttons.at("face_happy").setSprite("cell", jpgList.at("face_lose"));
                    } else {
                        std::set<Tile*> adjacentTiles;
                        currentTile.show(jpgList, showTiles, adjacentTiles);
                        if (showTiles == goodTiles) {
                            gameOver = true;
                            buttons.at("face_happy").setSprite("cell", jpgList.at("face_win"));
                            flagCount = mineCount;
                            updateMinesCount();
                            displayMarker = leaderBoard.insertLeader(leaderNames, playerName, timer, displayMarker);
                            names = leaderBoard.formatLeaderList(leaderNames);
                            windowText->setString(names);
                            sf::FloatRect cell = windowText->getLocalBounds();
                            windowText->setOrigin(cell.left + cell.width / 2.0f, cell.top + cell.height / 2.0f);
                            windowText->setPosition(16 * width / 2.0f, 16 * height / 2.0f + 20);

                            for (size_t m = 0; m < mineTiles.size(); m++) {
                                mineTiles[m]->setGameWon(jpgList.at("flag"), true);
                            }

                            leaderWindow->create(sf::VideoMode(16 * width, 16 * height + 50), "Aarithi Rajendren");
                        }
                    }
                }
            }
        }
    }
}

// Initializes counter, clock and other images at the bottom of the window
void Board::initailizeCounterClockPNGImages(const vector<pair<string, pair<int, int>>> &baseButtons) {
    for (size_t i = 0; i < baseButtons.size(); i++) {
        const auto& definition = baseButtons[i];
        Cell cell(jpgList.at(definition.first), definition.second.first, definition.second.second);
        buttons.emplace(definition.first, cell);
    }

    Cell mineCounter(jpgList.at("digit_negative"), 12, 32 * (height + 0.5f) + 16);
    buttons.emplace("mineCounter", mineCounter);
    buttons.at("mineCounter").addSprite(jpgList.at("digit_0"), "hundreds", 33, 32 * (height + 0.5f) + 16);
    buttons.at("mineCounter").addSprite(jpgList.at("digit_0"), "tens", 54, 32 * (height + 0.5f) + 16);
    buttons.at("mineCounter").addSprite(jpgList.at("digit_0"), "ones", 75, 32 * (height + 0.5f) + 16);

    Cell clock(jpgList.at("digit_0"), 0, 0);
    buttons.emplace("clock", clock);
    buttons.at("clock").deleteSprite("cell");
    buttons.at("clock").addSprite(jpgList.at("digit_0"), "MinuteLeftDigit", width * 32 - 97, 32 * (height + 0.5f) + 16);
    buttons.at("clock").addSprite(jpgList.at("digit_0"), "MinuteRightDigit", width * 32 - 76, 32 * (height + 0.5f) + 16);
    buttons.at("clock").addSprite(jpgList.at("digit_0"), "SecondLeftDigit", width * 32 - 54, 32 * (height + 0.5f) + 16);
    buttons.at("clock").addSprite(jpgList.at("digit_0"), "SecondRightDigit", width * 32 - 33, 32 * (height + 0.5f) + 16);
}
