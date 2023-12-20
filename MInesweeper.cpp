#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include "Randomizer.h"
#include "TextureManager.h"
#include "Board.h"
#include "Button.h"

using namespace std;



int main()
{
    //Set up initialization
    sf::RenderWindow window(sf::VideoMode(800, 600), "MineSweeper");

    //Load textures
   TextureManager::LoadTexture("face_happy");
   TextureManager::LoadTexture("face_lose");
   TextureManager::LoadTexture("face_win");
   //TextureManager::LoadTexture("digits");
   TextureManager::LoadTexture("debug");
   TextureManager::LoadTexture("flag");
   TextureManager::LoadTexture("number_1");
   TextureManager::LoadTexture("number_2");
   TextureManager::LoadTexture("number_3");
   TextureManager::LoadTexture("number_4");
   TextureManager::LoadTexture("number_5");
   TextureManager::LoadTexture("number_6");
   TextureManager::LoadTexture("number_7");
   TextureManager::LoadTexture("number_8");
   TextureManager::LoadTexture("test_1");
   TextureManager::LoadTexture("test_2");
   TextureManager::LoadTexture("test_3");
   TextureManager::LoadTexture("tile_hidden");
   TextureManager::LoadTexture("tile_revealed");
   TextureManager::LoadTexture("mine");


     //Create the sprites
    sf::Sprite smileyhappy(TextureManager::GetTexture("face_happy"));
    sf::Sprite smileyLose(TextureManager::GetTexture("face_lose"));
    sf::Sprite smileyWin(TextureManager::GetTexture("face_win"));
    //sf::Sprite numbers(TextureManager::GetTexture("digits"));
    sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    sf::Sprite flagSprite(TextureManager::GetTexture("flag"));
    sf::Sprite tileNumber1(TextureManager::GetTexture("number_1"));
    sf::Sprite tileNumber2(TextureManager::GetTexture("number_2"));
    sf::Sprite tileNumber3(TextureManager::GetTexture("number_3"));
    sf::Sprite tileNumber4(TextureManager::GetTexture("number_4"));
    sf::Sprite tileNumber5(TextureManager::GetTexture("number_5"));
    sf::Sprite tileNumber6(TextureManager::GetTexture("number_6"));
    sf::Sprite tileNumber7(TextureManager::GetTexture("number_7"));
    sf::Sprite tileNumber8(TextureManager::GetTexture("number_8"));
    sf::Sprite testButton1(TextureManager::GetTexture("test_1"));
    sf::Sprite testButton2(TextureManager::GetTexture("test_2"));
    sf::Sprite testButton3(TextureManager::GetTexture("test_3"));
    //sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
    //sf::Sprite exposedTile(TextureManager::GetTexture("tile_revealed"));



    

    


    Board createBoard;
    Board test1;

    Button press;
    createBoard.mainBoard();

    createBoard.MineGenerator();

    createBoard.SpawnNumbers();

    createBoard.hiddenBoard();

    //second conditional for reset function
   

    //Runs forever until user closes out of window
    while (window.isOpen())
    {
 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    //we'll do something here
                    if (createBoard.boom == false)
                    {
                        if (createBoard.win == false)
                        {
                            createBoard.RemoveTile(position);
                        }
                    }
                    press.DebugButtonActivator(position, debugButton);

                    press.Test1(position, testButton1, createBoard);

                    press.Test2(position, testButton2, createBoard);

                    press.Test3(position, testButton3, createBoard);

                    press.Smiley(position, smileyhappy, createBoard);

                    if (createBoard.boom == false)
                    {
                        if (createBoard.win == false)
                        {
                            createBoard.YoureDeadHAHAHA(position);
                        }
                    }
                    
                    //createBoard.GuessYouWin;
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //right click is for flags...
                    
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    if (createBoard.boom == false)
                    {
                        if (createBoard.win == false)
                        {
                            createBoard.FlagPositioner(position); //here is where the function gets called
                        }
                    }
                    
                }
            }
        }

        

        
        window.clear(); 

        createBoard.GuessYouWin();

        if (createBoard.win == true)
        {
            createBoard.flagCount = createBoard.mines.size();

            sf::Sprite smileyWin(TextureManager::GetTexture("face_win"));

            smileyWin.setPosition(368, 512);
            window.draw(smileyWin);

        }

        if (createBoard.boom == true)
        {
            sf::Sprite smileyLose(TextureManager::GetTexture("face_lose"));

            smileyLose.setPosition(368, 512);

            for (unsigned int i = 0; i < createBoard.exposedTiles.size(); i++)
            {
                if ((createBoard.expTiles[i].hasMine == true))
                {
                    createBoard.hiddTileObjects.at(i).toRemove = true;
                }
                //draws the tiles


            }

            window.draw(smileyLose);
        }


        if (createBoard.win == true)
        {
            for (unsigned int i = 0; i < createBoard.mines.size(); i++)
            {

                flagSprite.setPosition(createBoard.mines.at(i).getPosition().x, createBoard.mines.at(i).getPosition().y);

                window.draw(flagSprite);


            }
        }
        
            
       
            for (unsigned int i = 0; i < createBoard.exposedTiles.size(); i++)
            {

                window.draw(createBoard.exposedTiles[i]); //draws the tiles


            }

            if (press.GetBoolForDebug() == false || createBoard.boom == false)
            {
                for (unsigned int i = 0; i < createBoard.mines.size(); i++)
                {


                    window.draw(createBoard.mines[i]);
                }
            }

            for (unsigned int p = 0; p < createBoard.numbers.size(); p++)
            {
                window.draw(createBoard.numbers.at(p));
            }

            for (unsigned int i = 0; i < createBoard.hiddTiles.size(); i++)
            {

                if (createBoard.hiddTileObjects.at(i).toRemove == false)
                {
                    window.draw(createBoard.hiddTiles[i]); //draws the HIDDEN tiles
                }


            }

            for (unsigned int j = 0; j < createBoard.flagObjects.size(); j++)
            {

                if (createBoard.flagObjects.at(j).remove == false)
                {
                    window.draw(createBoard.flags.at(j));
                }//draws the flags


            }

            createBoard.Counter();


            for (unsigned int j = 0; j < createBoard.counterSprites.size(); j++)
            {
                window.draw(createBoard.counterSprites.at(j));

            }

            if (press.GetBoolForDebug() == true || createBoard.boom == true)
            {
                for (unsigned int i = 0; i < createBoard.mines.size(); i++)
                {

                    window.draw(createBoard.mines[i]);
                }
            }
        
        

        //TEST1
        if(press.GetBoolForTest1() == true )
        {
           
            for (unsigned int i = 0; i < createBoard.exposedTiles.size(); i++)
            {

                window.draw(createBoard.exposedTiles[i]); //draws the tiles


            }
            
            

            for (unsigned int p = 0; p < createBoard.numbers.size(); p++)
            {
                window.draw(createBoard.numbers.at(p));
            }

            for (unsigned int i = 0; i < createBoard.hiddTiles.size(); i++)
            {
                if (createBoard.hiddTileObjects.at(i).toRemove == false)
                {
                    window.draw(createBoard.hiddTiles[i]); //draws the HIDDEN tiles
                }


            }

            for (unsigned int j = 0; j < createBoard.flagObjects.size(); j++)
            {

                if (createBoard.flagObjects.at(j).remove == false)
                {
                    window.draw(createBoard.flags.at(j));
                }//draws the flags


            }

            
            for (unsigned int j = 0; j < createBoard.counterSprites.size(); j++)
            {
                window.draw(createBoard.counterSprites.at(j));

            }

            for (unsigned int i = 0; i < createBoard.mines.size(); i++)
            {


                window.draw(createBoard.mines[i]);
            }
            //createBoard.ResetBoard();
        }


        //TEST2
        if (press.GetBoolForTest2() == true)
        {
            for (unsigned int i = 0; i < createBoard.exposedTiles.size(); i++)
            {

                window.draw(createBoard.exposedTiles[i]); //draws the tiles


            }


            createBoard.SpawnNumbers();

            for (unsigned int p = 0; p < createBoard.numbers.size(); p++)
            {
                window.draw(createBoard.numbers.at(p));
            }

            for (unsigned int i = 0; i < createBoard.hiddTiles.size(); i++)
            {
                if (createBoard.hiddTileObjects.at(i).toRemove == false)
                {
                    window.draw(createBoard.hiddTiles[i]); //draws the HIDDEN tiles
                }


            }

            for (unsigned int j = 0; j < createBoard.flagObjects.size(); j++)
            {

                if (createBoard.flagObjects.at(j).remove == false)
                {
                    window.draw(createBoard.flags.at(j));
                }//draws the flags


            }


            for (unsigned int j = 0; j < createBoard.counterSprites.size(); j++)
            {
                window.draw(createBoard.counterSprites.at(j));

            }

            for (unsigned int i = 0; i < createBoard.mines.size(); i++)
            {


                window.draw(createBoard.mines[i]);
            }
            
        }

        //TEST 3
        if (press.GetBoolForTest3() == true)
        {
            for (unsigned int i = 0; i < createBoard.exposedTiles.size(); i++)
            {

                window.draw(createBoard.exposedTiles[i]); //draws the tiles


            }


            createBoard.SpawnNumbers();

            for (unsigned int p = 0; p < createBoard.numbers.size(); p++)
            {
                window.draw(createBoard.numbers.at(p));
            }

           for (unsigned int i = 0; i < createBoard.hiddTiles.size(); i++)
            {
                if (createBoard.hiddTileObjects.at(i).toRemove == false)
                {
                    window.draw(createBoard.hiddTiles[i]); //draws the HIDDEN tiles
            }


            }

            for (unsigned int j = 0; j < createBoard.flagObjects.size(); j++)
            {

                if (createBoard.flagObjects.at(j).remove == false)
                {
                    window.draw(createBoard.flags.at(j));
                }//draws the flags


            }


            for (unsigned int j = 0; j < createBoard.counterSprites.size(); j++)
            {
                window.draw(createBoard.counterSprites.at(j));

            }

            for (unsigned int i = 0; i < createBoard.mines.size(); i++)
            {


                window.draw(createBoard.mines[i]);
            }
            //createBoard.ResetBoard();
        }
        


       //+++++++++++++++TODO MAKE A RESET FUNCTION FOR TEST BOARDS+++++++++++++

        if (press.resetTrigger == true)
        {
            createBoard.ResetBoard();

            press.resetTrigger = false;
            
        }

        if (createBoard.boom == false)
        {
            if (createBoard.win == false)
            {
                sf::Sprite smileyhappy(TextureManager::GetTexture("face_happy"));

                smileyhappy.setPosition(368, 512);

                //implement somesort of smiley face state that shcecks the status of the game.
                window.draw(smileyhappy);
            }
        }

       sf::Sprite debugButton(TextureManager::GetTexture("debug"));

       debugButton.setPosition(496, 512);

       //implement somesort of smiley face state that shcecks the status of the game.
       window.draw(debugButton);

       sf::Sprite testButton1(TextureManager::GetTexture("test_1"));
       testButton1.setPosition(560.5, 512);

       //implement somesort of smiley face state that shcecks the status of the game.
       window.draw(testButton1);



       sf::Sprite testButton2(TextureManager::GetTexture("test_2"));
       
       testButton2.setPosition(624.5, 512);
       //implement somesort of smiley face state that shcecks the status of the game.
       window.draw(testButton2);



       sf::Sprite testButton3(TextureManager::GetTexture("test_3"));
       testButton3.setPosition(686, 512);
       //implement somesort of smiley face state that shcecks the status of the game.
       window.draw(testButton3);

       if (createBoard.win == true)
       {
           for (unsigned int i = 0; i < createBoard.mines.size(); i++)
           {

               flagSprite.setPosition(createBoard.mines.at(i).getPosition().x, createBoard.mines.at(i).getPosition().y);

               window.draw(flagSprite);


           }
       }
       

        window.display();
    }


    return 0;
} 