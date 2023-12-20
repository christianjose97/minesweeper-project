#include "Button.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "Board.h"
using std::string;
using std::fstream;
using std::unordered_map;
using std::vector;

using namespace std;







void Button::DebugButtonActivator(sf::Vector2i& position, sf::Sprite& button)
{
    button.setPosition(496, 512);
    
    sf::FloatRect debugPressed = button.getGlobalBounds();

    if (debugPressed.contains(sf::Vector2f(position.x, position.y)) && DebugON == false)
    {
       DebugON =  true;
    }
    else if(debugPressed.contains(sf::Vector2f(position.x, position.y)) && DebugON == true)
    {
        DebugON = false;
    }

    
    

        
	
}

void Button::Smiley(sf::Vector2i& position, sf::Sprite& button, Board board)
{
    

       button.setPosition(368, 512);
       sf::FloatRect smiley = button.getGlobalBounds();

       if (smiley.contains(sf::Vector2f(position.x, position.y)))
       {
           resetTrigger = true;
           test1Bool = false;
           test2Bool = false;
           test3Bool = false;
       }
}

void Button::Test1(sf::Vector2i& position, sf::Sprite& button, Board& board)
{

    button.setPosition(560.5, 512);

    sf::FloatRect test1Pressed = button.getGlobalBounds();

    if (test1Pressed.contains(sf::Vector2f(position.x, position.y)) && test1Bool == false)
    {
       board.flagCount = 0;
       board.boom = false; 
       board.win = false;
       board.expTiles.clear();

       board.hiddTileObjects.clear();

       board.flagObjects.clear();

       board.mineObjects.clear();

       board.exposedTiles.clear(); //this vector is making the board

       board.hiddTiles.clear();

       board.mines.clear();

       board.flags.clear();

       board.numbers.clear();

       board.counterSprites.clear();

       board.mainBoard();
        


        

        std::ifstream infile("boards/testboard1.brd");

        std::vector<char> onesNzeros;

        char input;

        while (infile >> input)
        {
            
            onesNzeros.push_back(input);
        }

        board.CustomBombs(onesNzeros);
        board.SpawnNumbers();
        board.hiddenBoard();
        board.Counter();
        
        
       

         test1Bool = true;
         test2Bool = false;
         test3Bool = false;
    }
    

    
}

void Button::Test2(sf::Vector2i& position, sf::Sprite& button, Board& board)
{
    //change
    button.setPosition(624.5, 512);

    sf::FloatRect test2Pressed = button.getGlobalBounds();

    if (test2Pressed.contains(sf::Vector2f(position.x, position.y)) && test2Bool == false)
    {
        board.flagCount = 0;
        board.boom = false;
        board.expTiles.clear();
        board.win = false;
        board.hiddTileObjects.clear();

        board.flagObjects.clear();

        board.mineObjects.clear();

        board.exposedTiles.clear(); //this vector is making the board

        board.hiddTiles.clear();

        board.mines.clear();

        board.flags.clear();

        board.numbers.clear();

        board.counterSprites.clear();
        board.mainBoard();

        std::ifstream infile("boards/testboard2.brd");

        std::vector<char> onesNzeros;

        char input;

        while (infile >> input)
        {

            onesNzeros.push_back(input);
        }

        board.CustomBombs(onesNzeros);
        board.SpawnNumbers();
        board.hiddenBoard();
        board.Counter();


        

        
        
        test1Bool = false;
        test2Bool = true;
        test3Bool = false;
        
    }
    

}

void Button::Test3(sf::Vector2i& position, sf::Sprite& button, Board& board)
{
    
    //change
    button.setPosition(686, 512);

    sf::FloatRect test3Pressed = button.getGlobalBounds();

    if (test3Pressed.contains(sf::Vector2f(position.x, position.y)) && test3Bool == false)
    {
        board.flagCount = 0;
        board.boom = false;
        board.expTiles.clear();
        board.win = false;
        board.hiddTileObjects.clear();

        board.flagObjects.clear();

        board.mineObjects.clear();

        board.exposedTiles.clear(); //this vector is making the board

        board.hiddTiles.clear();

        board.mines.clear();

        board.flags.clear();

        board.numbers.clear();

        board.counterSprites.clear();
        board.mainBoard();

        std::ifstream infile("boards/testboard3.brd");

        std::vector<char> onesNzeros;

        char input;

        while (infile >> input)
        {

            onesNzeros.push_back(input);
        }

        board.CustomBombs(onesNzeros);
        board.SpawnNumbers();
        board.hiddenBoard();
        board.Counter();


      
       
        test1Bool = false;
        test2Bool = false;
        test3Bool = true;
    }
    

}

bool Button::GetBoolForDebug()
{
    return DebugON;
}


bool Button::GetBoolForTest1()
{
    return test1Bool;
}
bool Button::GetBoolForTest2()
{
    return test2Bool;
}
bool Button::GetBoolForTest3()
{
    return test3Bool;
}

bool Button::GetTrigger()
{
    return resetTrigger;
}

bool Button::GetStateOfSmiley()
{
    return false;
}
