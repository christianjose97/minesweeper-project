#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;

class TextureManager
{

	static std::unordered_map<std::string, sf::Texture> textures;

	std::map<char, sf::Sprite> digits;

public:


	static void LoadTexture(const char* filename);

	static sf::Texture& GetTexture(const char* textureKey);

	static void LoadDigitsTexture(const char* filename);

	static sf::Sprite UpdateFlagCounter(int numberOfFlags);

};

