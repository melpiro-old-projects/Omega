#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <algorithm>

class TextureManager {

public:
    TextureManager();

    void setDefaultTextureDir(std::string local);

    void addTexture(std::string local, std::string name);
    void loadAllTextures();

    sf::Texture& get(std::string name);


private:

    std::map<std::string,std::pair<std::string,sf::Texture>> m_allTextures;
    std::string m_defaultDir;
};

extern TextureManager textureManager;