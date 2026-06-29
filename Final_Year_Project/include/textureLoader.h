/** \file textureLoader.h
* Header file for the textureLoader class.
*/

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <memory>
#include <SFML/Graphics.hpp>

//! The textureLoader Class
/*!
This class builds stores textures and returns them later
*/
class textureLoader

{
private:
	
	/** a map of textures so you only have to load once
	\param m_Textures the texture loaded.
	*/
	 std::map<std::string, sf::Texture> m_Textures;

public:

	textureLoader();

	/** The load Texture function loads the textures to a map to allow access
	\param name The name of the texture used to get access to it.
	\param filename The path to the file and to be loaded.
	*/
	bool loadTexture(const std::string& name, const std::string &filename);

	/** gets a pionter to the texture*/
	sf::Texture& getRef(const std::string& texture);

};

#endif TEXTURELOADER_H