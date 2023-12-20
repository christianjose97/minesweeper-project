#include "Board.h"
#include "Randomizer.h"
#include "TextureManager.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;


void Board::mainBoard()
{
    Tiles tileObj;
    float x = 0;
    float y = 0;

    for (int j = 0; j < 16; j++)
    {
        sf::Sprite exposedTile(TextureManager::GetTexture("tile_revealed"));

        for (int i = 0; i < 25; i++ ) {


            exposedTile.setPosition(x, y);

            tileObj.xCoor = x;
            tileObj.yCoor = y;
           
            exposedTiles.push_back(exposedTile);
            expTiles.push_back(tileObj);

            x = 32 + x;

            
           
        }

        
        y = 32 + y;
        x = 0;

        tileObj.yCoor = y;

        
        
    }

    

   
   }

void Board::hiddenBoard()
{
    HiddenTiles hiddTileObj;
    float x = 0;
    float y = 0;

    for (int j = 0; j < 16; j++)
    {
        sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));

        for (int i = 0; i < 25; i++) {


            hiddenTile.setPosition(x, y);

            hiddTileObj.xCoor = x;
            hiddTileObj.yCoor = y;

            hiddTiles.push_back(hiddenTile);
            hiddTileObjects.push_back(hiddTileObj);

            x = 32 + x;




        }

       

        y = 32 + y;
        x = 0;

        hiddTileObj.yCoor = y;

    }
}

void Board::MineGenerator()
{
    int randomIndex = 0;
    int counter = 0;
    Mine mineBois;
    for (int i = 0; i < expTiles.size(); i++)
    {
        if (counter == 50)
        {
            break;
        }
        randomIndex = Randomizer::Int(0, expTiles.size() - 1);

         

        if (expTiles.at(randomIndex).hasMine == true)
        {
            continue;
        }

        sf::Sprite mine(TextureManager::GetTexture("mine"));


        mine.setPosition(expTiles.at(randomIndex).xCoor, expTiles.at(randomIndex).yCoor);

        mineBois.x = expTiles.at(randomIndex).xCoor;



        mineBois.y = expTiles.at(randomIndex).yCoor;



        expTiles.at(randomIndex).hasMine = true;

        mines.push_back(mine);

        mineObjects.push_back(mineBois);
    
        counter++;
    }
}

void Board::FlagPositioner(sf::Vector2i& position)
{
    Flag flaggers;

    bool bailOut = false;
    

    sf::Sprite flagSprite(TextureManager::GetTexture("flag"));

    for (int i = 0; i < hiddTileObjects.size(); i++)
    {
        sf::FloatRect rectangle = hiddTiles.at(i).getGlobalBounds();
        
        if (hiddTileObjects.at(i).hasFlag == false && expTiles.at(i).isExposed != true) {

            if (rectangle.contains(sf::Vector2f(position.x, position.y)))
            {
               
                flagSprite.setPosition(hiddTileObjects.at(i).xCoor, hiddTileObjects.at(i).yCoor);

                flaggers.x = hiddTiles.at(i).getPosition().x;
                flaggers.y = hiddTiles.at(i).getPosition().y;

                flags.push_back(flagSprite);
                flagObjects.push_back(flaggers);

                hiddTileObjects.at(i).hasFlag = true;
                
                flagCount++;
            }
        }
        else 
        {
            int count = 0;
            for (int j = 0; j < flags.size(); j++)
            {
                sf::FloatRect flag = flags.at(j).getGlobalBounds();

                if (flag.contains(sf::Vector2f(position.x, position.y)) && rectangle.contains(sf::Vector2f(position.x, position.y)))
                {
                    
                    flagObjects.at(j).remove = true;

                    hiddTileObjects.at(i).hasFlag = false;

                    flagCount--;

                    bailOut = true;
                    
                   
                }
                
            }
            
        }

        if (bailOut)
        {
            break;
        }
       
    }
    


}

void Board::RemoveTile(sf::Vector2i& position)
{
    sf::Sprite flagSprite(TextureManager::GetTexture("flag"));
    for (int i = 0; i < hiddTileObjects.size(); i++)
    {
        sf::FloatRect rectangle = hiddTiles.at(i).getGlobalBounds();

        if (hiddTileObjects.at(i).hasFlag == false) {

            if (rectangle.contains(sf::Vector2f(position.x, position.y)))
            {
                
                hiddTileObjects.at(i).toRemove = true;
                expTiles.at(i).isExposed = true;
                
                //test
               
            }
        }
    }
}

void Board::SpawnNumbers()
{
    int count = 0;
    sf::Sprite tileNumber1(TextureManager::GetTexture("number_1"));
    sf::Sprite tileNumber2(TextureManager::GetTexture("number_2"));
    sf::Sprite tileNumber3(TextureManager::GetTexture("number_3"));
    sf::Sprite tileNumber4(TextureManager::GetTexture("number_4"));
    sf::Sprite tileNumber5(TextureManager::GetTexture("number_5"));
    sf::Sprite tileNumber6(TextureManager::GetTexture("number_6"));
    sf::Sprite tileNumber7(TextureManager::GetTexture("number_7"));
    sf::Sprite tileNumber8(TextureManager::GetTexture("number_8"));

    

    for (int i = 0; i < expTiles.size(); i++)
    {
       //SPECIAL CASES

        //left corner
        if (expTiles.at(i).yCoor == 0 && expTiles.at(i).xCoor == 0 && expTiles.at(i).hasMine == false)
        {
            if ((i + 1) < expTiles.size() && expTiles.at(i + 1).hasMine == true)
            {
               
                count++;
            }
            if ((i + 25) < expTiles.size() && expTiles.at(i + 25).hasMine == true)
            {
                
                count++;
            }
            if ((i + 26) < expTiles.size() && expTiles.at(i + 26).hasMine == true)
            {
               
                count++;
            }
        }
        //right corner
        else if(expTiles.at(i).yCoor == 0 && expTiles.at(i).xCoor == 768 && expTiles.at(i).hasMine == false)
        {
            if ((i - 1) >= 0 && (expTiles.at(i - 1).hasMine == true))
            {
               
                count++;
            }
            if ((i + 24) >= 0 && expTiles.at(i + 24).hasMine == true)
            {
               
                count++;
            }
            if ((i + 25) >= 0 && expTiles.at(i + 25).hasMine == true)
            {
               
                count++;
            }
        }
        //bottom left
        else if ((expTiles.at(i).yCoor == 480 && expTiles.at(i).xCoor == 0 && expTiles.at(i).hasMine == false))
        {
            if ((i + 1) < expTiles.size() && expTiles.at(i + 1).hasMine == true)
            {
                
                count++;
            }
            if ((i - 24) >= 0 && expTiles.at(i - 24).hasMine == true)
            {
                
                count++;
            }
            if ((i - 25) >= 0 && expTiles.at(i - 25).hasMine == true)
            {
                
                count++;
            }
        }

        //bottom right
        else if ((expTiles.at(i).yCoor == 480 && expTiles.at(i).xCoor == 768 && expTiles.at(i).hasMine == false))
        {
            if ((i - 1) < expTiles.size() && expTiles.at(i - 1).hasMine == true)
            {
               
                count++;
            }
            if ((i - 25) >= 0 && expTiles.at(i - 25).hasMine == true)
            {
               
                count++;
            }
            if ((i - 26) >= 0 && expTiles.at(i - 26).hasMine == true)
            {
               
                count++;
            }
        }

        //THE REST
        else if (expTiles.at(i).hasMine == false)
        {
            //++++++++++++++++++++++++++++++++++++TODO MOFO++++++++++++++++++++++++++++++++++
            //CHECK WHY BOTTOM ROW ISNT GETTING NUMBERS ALSO CHECK WHY SOME OF THE EDGE NUMBERS ARE WRONG???
            //768 for rightmost and 0 for leftmost
            //DONE++++++++++++++++++++++++++++++++++++

          
                if (expTiles.at(i).xCoor != 768 && (i + 1) < expTiles.size() && expTiles.at(i + 1).hasMine == true)
                {
                    
                    count++;
                }
                if (expTiles.at(i).xCoor != 0 && (i + 24) < expTiles.size() && expTiles.at(i + 24).hasMine == true)
                {
                   
                    count++;
                }
                if ((i + 25) < expTiles.size() && expTiles.at(i + 25).hasMine == true)
                {
                   
                    count++;
                }
                if (expTiles.at(i).xCoor != 768 && (i + 26) < expTiles.size() && expTiles.at(i + 26).hasMine == true)
                {
                   
                    count++;
                }
            
            
            

            //acts as the null ptr
               
                    if (expTiles.at(i).xCoor != 0 && (i - 1) >= 0 && (expTiles.at(i - 1).hasMine == true))
                    {
                       
                        count++;
                    }
                    if (expTiles.at(i).xCoor != 768 && (i - 24) >= 0 && expTiles.at(i - 24).hasMine == true)
                    {
                        
                        count++;
                    }
                    if ((i - 25) >= 0 && expTiles.at(i - 25).hasMine == true)
                    {
                       
                        count++;
                    }
                    if (expTiles.at(i).xCoor != 0 && (i - 26) >= 0 && expTiles.at(i - 26).hasMine == true)
                    {
                        
                        count++;
                    }

                    
                
                
                    
        }
        else
        {
       
            continue;
        }

            switch (count)
            {
            case 1:
                tileNumber1.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber1);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 2:
                tileNumber2.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber2);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 3:
                tileNumber3.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber3);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 4:
                tileNumber4.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber4);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 5:
                tileNumber5.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber5);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 6:
                tileNumber6.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber6);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 7:
                tileNumber7.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber7);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;
            case 8:
                tileNumber8.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);
                numbers.push_back(tileNumber8);
                count = 0;
                expTiles.at(i).hasNumber = true;
                break;

            default:
                
                count = 0;
                break;
            }
            
    
    }
    


}

void Board::Counter()
 {
    sf::Sprite numbers(TextureManager::GetTexture("digits"));
    numbers.setPosition(0, 512);
    counterSprites.clear();

    //int numFlags = (mines.size()-1) - flags.size();

    int numFlags = (mines.size()) - flagCount;
    int positioner = 0;
    

    string numFlagsString = "0" + to_string(numFlags);

    for (int i = 0; i < numFlagsString.length(); i++)
    {
        
        if (numFlagsString.length() < 3 || (numFlags < 0 && numFlagsString.length() < 4))
        {
            numFlagsString = "0" + numFlagsString;
        }

        if (numFlagsString.at(i) == '-')
        {
            
            numbers.setTextureRect(sf::IntRect(210, 0, 21, 32));
            numbers.setPosition(0, 512);
            counterSprites.push_back(numbers);
            
        }
        if (numFlagsString.at(i) == '0' || numFlagsString.at(i) != '0')
        {
           
            numbers.setTextureRect(sf::IntRect(0, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
        }
            
        if (numFlagsString.at(i) == '1')
        {
          
            numbers.setTextureRect(sf::IntRect(21, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '2')
        {
            
            numbers.setTextureRect(sf::IntRect(42, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '3')
        {
            
            numbers.setTextureRect(sf::IntRect(63, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '4')
        {
           
            numbers.setTextureRect(sf::IntRect(84, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '5')
        {
                
                numbers.setTextureRect(sf::IntRect(105, 0, 21, 32));
                numbers.setPosition(positioner, 512);
                counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '6')
        {
                
                numbers.setTextureRect(sf::IntRect(126, 0, 21, 32));
                numbers.setPosition(positioner, 512);
                counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '7')
        {
               
                numbers.setTextureRect(sf::IntRect(147, 0, 21, 32));
                numbers.setPosition(positioner, 512);
                counterSprites.push_back(numbers);
        }
        if (numFlagsString.at(i) == '8')
        {
               
                numbers.setTextureRect(sf::IntRect(168, 0, 21, 32));
                numbers.setPosition(positioner, 512);
                counterSprites.push_back(numbers);
            }
        if (numFlagsString.at(i) == '9')
        {
           
            numbers.setTextureRect(sf::IntRect(189, 0, 21, 32));
            numbers.setPosition(positioner, 512);
            counterSprites.push_back(numbers);
          
        }
       
        positioner += 21;
    }
        


 
}

void Board::CustomBombs(std::vector<char>& onesNzeros)
{
    mineObjects.clear();
    mines.clear();
    

    Mine mineDudes;
    for (int i = 0; i < onesNzeros.size(); i++)
    {

        sf::Sprite mine(TextureManager::GetTexture("mine"));

        if (onesNzeros.at(i) == '1') {

            mine.setPosition(expTiles.at(i).xCoor, expTiles.at(i).yCoor);

            mineDudes.x = expTiles.at(i).xCoor;

            mineDudes.y = expTiles.at(i).yCoor;

            expTiles.at(i).hasMine = true;

            mines.push_back(mine);

            mineObjects.push_back(mineDudes);

        }
    }

   
}

void Board::ResetBoard()
{
    expTiles.clear();

    hiddTileObjects.clear();

    flagObjects.clear();

    mineObjects.clear();

    exposedTiles.clear(); //this vector is making the board

    hiddTiles.clear();

    mines.clear();

    flags.clear();

    numbers.clear();

    counterSprites.clear();

    mainBoard();

    MineGenerator();

    SpawnNumbers();

    hiddenBoard();

    flagCount = 0;

    Counter();
    
    boom = false;

    win = false;
    
    numberOfRevealedTiles = 0;
}

void Board::YoureDeadHAHAHA(sf::Vector2i& position)
{
    for (int i = 0; i < expTiles.size(); i++)
    {
        sf::FloatRect tiles = exposedTiles.at(i).getGlobalBounds();

        if (expTiles.at(i).hasMine == true && hiddTileObjects.at(i).hasFlag == false) {

            if (tiles.contains(sf::Vector2f(position.x, position.y)))
            {
                boom = true;
                break;
            }
        }

    }
}

void Board::HiddenTileRevealer(sf::Vector2i& position)
{
    int j = 0;
    int k = 0;
    int p = 0;
    int count = 0;

    for (int i = 0; i < expTiles.size(); i++)
    {
        sf::FloatRect tiles = exposedTiles.at(i).getGlobalBounds();

        if (tiles.contains(sf::Vector2f(position.x, position.y)))
        {
            j = i;
            break;
        }
    }

    //check bottom loop
    for (int bottom = j; bottom < expTiles.size(); bottom++)
    {
        if (expTiles.at(bottom).hasNumber == false)
        {
            hiddTileObjects.at(bottom).toRemove = true;
            expTiles.at(bottom).isExposed = true;
            count++;
        }
        else if ((bottom + 25) < expTiles.size())
        {
            bottom = bottom + 25 - count;
        }
    }
    //check top
    for (int top = j; top < expTiles.size(); top++)
    {
        if (expTiles.at(top).hasNumber == false)
        {
            hiddTileObjects.at(top).toRemove = true;
            expTiles.at(top).isExposed = true;
            count++;
        }
        else if ((top + 25) < expTiles.size())
        {
            top = (top - 25) - count;
        }
    }

    //for (int i = j; i >= 0; i++)
    //{
      //  if (expTiles.at(i).hasNumber == false)
      //  {
      //      hiddTileObjects.at(i).toRemove = true;
      //      expTiles.at(i).isExposed = true;
      //      count++;
      //  }
     //   else if ((i + 25) < expTiles.size())
      //  {
     //       i = (i - 25) - count;
    //    }
 //   }

    
}

void Board::GuessYouWin()
{
    int count = 0;

    for (int i = 0; i < expTiles.size(); i++)
    {
        if (expTiles.at(i).isExposed)
        {
            count++;
        }
    }
    if (count == (expTiles.size() - mines.size()))
    {
        win = true;
    }
}



/*int j = 0;
int k = 0;
int p = 0;
int count = 0;

for (int i = 0; i < expTiles.size(); i++)
{
    sf::FloatRect tiles = exposedTiles.at(i).getGlobalBounds();

    if(tiles.contains(sf::Vector2f(position.x, position.y)))
    {
        j = i;
        break;
    }
}

//check bottom loop
for (int i = j; i < expTiles.size(); i++)
{
    if (expTiles.at(i).hasNumber == false)
    {
        hiddTileObjects.at(i).toRemove = true;
        expTiles.at(i).isExposed = true;
        count++;
    }
    else if ((i + 25) < expTiles.size())
    {
        i = i + 25 - count;
    }
}
//check top
for (int i = j; i < expTiles.size(); i++)
{
    if (expTiles.at(i).hasNumber == false)
    {
        hiddTileObjects.at(i).toRemove = true;
        expTiles.at(i).isExposed = true;
        count++;
    }
    else if ((i + 25) < expTiles.size())
    {
        i = (i - 25) - count;
    }
}

for (int i = j; i >= 0; i++)
{
    if (expTiles.at(i).hasNumber == false)
    {
        hiddTileObjects.at(i).toRemove = true;
        expTiles.at(i).isExposed = true;
        count++;
    }
    else if ((i + 25) < expTiles.size())
    {
        i = (i - 25) - count;
    }
}*/

