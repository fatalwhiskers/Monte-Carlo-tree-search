#include "textureLoader.h"
#include <iostream>
textureLoader::textureLoader()
{
	if (!loadTexture("error", "images/error.png"))
	{
		std::cout << "error file background 1 not loaded";
	}
}


bool textureLoader::loadTexture(const std::string& name, const std::string &filename)
{
	sf::Texture tex;

	if (tex.loadFromFile(filename))
	{
		this->m_Textures[name] = tex;
		return true;
	}
	return false;
}

/** gets a pionter to the texture*/
sf::Texture& textureLoader::getRef(const std::string& texture)
{
	if (m_Textures.count(texture) != 0)
	{
		return this->m_Textures.at(texture);
	}
	else
	{
		return this->m_Textures.at("error");
	}
}