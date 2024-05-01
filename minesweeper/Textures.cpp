#include "Textures.h"

    // Loads number textures and adds them to the texture registry
    void Textures::loadNumberTextures(map<int, sf::Texture> &numTextures, map<string, sf::Texture> &jpgList) {
        string path;
        for (auto &numTexture : numTextures) {
            path = "files/images/number_" + to_string(numTexture.first) + ".png";
            numTexture.second.loadFromFile(path);
            jpgList.insert({ to_string(numTexture.first), numTexture.second });
        }
    }

    // Loads textures with string identifiers from files
    void Textures::loadNamedTextures(map<string, sf::Texture> &namedTextures) {
        string path;
        for (auto &namedTexture : namedTextures) {
            path = "files/images/" + namedTexture.first + ".png";
            namedTexture.second.loadFromFile(path);
        }
    }

    // Loads digit textures from a sprite sheet and adds them to the texture registry
    void Textures::loadDigitTextures(vector<pair<string, sf::Texture>> &digitTextures, map<string, sf::Texture> &jpgList) {
        for (size_t index = 0; index < digitTextures.size(); ++index) {
            digitTextures[index].second.loadFromFile("files/images/digits.png", sf::IntRect(21 * index, 0, 21, 32));
            jpgList.insert({ digitTextures[index].first, digitTextures[index].second });
        }
    }
