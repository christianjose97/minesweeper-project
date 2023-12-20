#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "Board.h"

using std::string;
using std::fstream;
using std::unordered_map;
using std::vector;

class Button
{
	
	bool DebugON = false;
	bool test1Bool = false;
	bool test2Bool = false;
	bool test3Bool = false;
	

public:

	bool resetTrigger = false;

	
	

	void DebugButtonActivator(sf::Vector2i& position, sf::Sprite& button);

	bool GetBoolForDebug();

	void Smiley(sf::Vector2i& position, sf::Sprite& button, Board board);
	
	void Test1(sf::Vector2i& position, sf::Sprite& button, Board& board);

	void Test2(sf::Vector2i& position, sf::Sprite& button, Board& board);
	
	void Test3(sf::Vector2i& position, sf::Sprite& button, Board& board);

	bool GetBoolForTest1();
	
	bool GetBoolForTest2();
	
	bool GetBoolForTest3();

	bool GetTrigger();

	bool GetStateOfSmiley();
	

};

