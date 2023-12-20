#include "TextureManager.h"

unordered_map<std::string, sf::Texture> TextureManager::textures;

unordered_map<char, sf::Sprite> digits;

void TextureManager::LoadTexture(const char* filename)
{
	string filepath = "images/";
	filepath += filename;
	filepath += ".png";
	
	textures[filename].loadFromFile(filepath);


}

sf::Texture& TextureManager::GetTexture(const char* textureKey)
{
	if (textures.find(textureKey) == textures.end()) //texture wasn not found... (key didnt exist)
		LoadTexture(textureKey); //made a new key.

	return textures[textureKey];
}

void TextureManager::LoadDigitsTexture(const char* filename)
{
	TextureManager obj;
	
	string filepath = "images/";
	filepath += filename;
	filepath += ".png";

	int j = 0;

	for (int i = 0; i < 11; i + 21)
	{
		sf::Texture digitsTexture;
		digitsTexture.loadFromFile(filepath, sf::IntRect(i, 0, 21, 32));

		obj.digits.emplace(j++, sf::Sprite(digitsTexture));
	}
}

sf::Sprite TextureManager::UpdateFlagCounter(int numberOfFlags)
{
	TextureManager obj;
	for (int i = 0; i < 11; i++)
	{
		
	}
}


