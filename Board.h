#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include "TextureManager.h"

using std::string;
using std::unordered_map;
using std::vector;

class Board
{
	
	int numberOfRevealedTiles = 0;
	const float width = 32;
	const float height = 32;

	struct Tiles
	{
		bool hasMine = false;
		bool isExposed = false;
		int xCoor = 0;
		int yCoor = 0;
		bool hasNumber = false;
		
		


		Tiles()
		{
			xCoor = 0;
			yCoor = 0;
		}

		
	};

	struct HiddenTiles
	{
		int xCoor = 0;
		int yCoor = 0;
		bool hasFlag = false;
		bool toRemove = false;
		bool Test = false;


		HiddenTiles()
		{
			xCoor = 0;
			yCoor = 0;
		}
	};

	

	struct Mine
	{
		int x = 0;
		int y = 0;

		Mine()
		{
			x = 0;
			y = 0;
		}

	};

	struct Flag
	{
		float x, y = 0;
		bool remove = false;

		Flag()
		{
			x = 0;
			y = 0;
		}
	};

	

public:
	int flagCount = 0;
	vector<Tiles> expTiles;

	vector<HiddenTiles> hiddTileObjects;

	vector<Flag> flagObjects;

	vector <Mine> mineObjects;

	vector<sf::Sprite> exposedTiles; //this vector is making the board

	vector<sf::Sprite> hiddTiles;

	vector<sf::Sprite> mines;

	vector<sf::Sprite> flags;

	vector<sf::Sprite> numbers;

	vector<sf::Sprite> counterSprites;

	bool boom = false;
	bool win = false;

	

	void mainBoard();

	void hiddenBoard();

	void MineGenerator();

	void FlagPositioner(sf::Vector2i& position);

	void RemoveTile(sf::Vector2i& position);

	void SpawnNumbers();

	void Counter();

	void CustomBombs(std::vector<char>& onesNzeros);

	void ResetBoard();
	
	void YoureDeadHAHAHA(sf::Vector2i& position);

	void HiddenTileRevealer(sf::Vector2i& position);

	void GuessYouWin();
	
	
};

