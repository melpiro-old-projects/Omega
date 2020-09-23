#include "TextureManager.hpp"

TextureManager::TextureManager() {
    m_defaultDir = ".";
}

void TextureManager::setDefaultTextureDir(std::string local)
{
    m_defaultDir = local;
}

void TextureManager::addTexture(std::string local, std::string name)
{
    m_allTextures[name] = std::make_pair(local, sf::Texture());
}
void TextureManager::loadAllTextures()
{
    auto it = m_allTextures.begin();
    for (it; it != m_allTextures.end(); it++)
    {
        it->second.second.loadFromFile(m_defaultDir+"/"+it->second.first);
    }
}

sf::Texture& TextureManager::get(std::string name)
{
    return m_allTextures[name].second;
}

TextureManager textureManager;