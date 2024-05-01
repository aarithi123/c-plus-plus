#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Cell.h"
#include "Leaderboard.h"
using namespace std;

class Textures {
public:
    void loadNumberTextures(map<int, sf::Texture> &numTextures, map<string, sf::Texture> &jpgList);
    void loadNamedTextures(map<string, sf::Texture> &jpgList);
    void loadDigitTextures(vector<pair<string, sf::Texture>> &digitTextures, map<string, sf::Texture> &jpgList);
};
