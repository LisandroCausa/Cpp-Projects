// Using SFML 2.5.1
#include "block.h"
#include "piece.h"
#include "functions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include <cstdlib>
#include <ctime>


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500, 640), "Tetris");
    window.setFramerateLimit(30);
    const int blockSize{ block().getSize() };
    constexpr int pixelsBetweenBlocks{ 2 };

    sf::Music music;
    music.openFromFile("Resources/Audio/music.ogg");
    music.setLoop(true);
    music.play();

    sf::RectangleShape verticalLimit(sf::Vector2f(5, 645));
    verticalLimit.setPosition(320, 0);
    verticalLimit.setFillColor(sf::Color(50, 50, 50));
    sf::RectangleShape horizontalLimit(sf::Vector2f(325, 5));
    horizontalLimit.setPosition(0, 640);
    horizontalLimit.setFillColor(sf::Color(50, 50, 50));

    sf::Font font;
    font.loadFromFile("Resources/Fonts/aansa.ttf");
    sf::Text scoreTitleText("SCORE", font, 36);
    scoreTitleText.setPosition(370, 300);
    sf::Text scoreValueText("0000", font, 53);
    scoreValueText.setPosition(370, 350);
    scoreValueText.setFillColor(sf::Color::Red);
    sf::String scoreString{ "" };

    sf::Text GameOver_TitleText("GAME OVER", font, 54);
    GameOver_TitleText.setPosition(40, 280);
    sf::Text GameOver_PressKeyText("Press Any Key", font, 38);
    GameOver_PressKeyText.setPosition(60, 350);
    GameOver_PressKeyText.setFillColor(sf::Color(200, 200, 200, 220));
    bool showPressKeyText{ false };

    bool GAME_OVER{ false };

    block grid[10][20];
    bool activeBlocks[10][20]{};

    piece playerPiece(get_randomPieceNumber(), blockSize + pixelsBetweenBlocks);

    bool TURN_isPressed{ false };
    bool MUTE_isPressed{ false };

    bool entireRow{ false };// Say whether there is an entire row or not.
    sf::Clock gameClock;    // Measures the total elapsed time of execution.
    sf::Clock updateClock;  // Wait for update (piece goes down).
    sf::Clock inputClock;   // Wait to receive a new input from player.
    int updateTime{ 250 };// Time (milliseconds) between updates.

    const sf::Vector2i staticPiece_position{ sf::Vector2i(11, 2) };
    int nextPieceNumber{ get_randomPieceNumber() };

    piece staticPiece(nextPieceNumber, 32);
    staticPiece.position = staticPiece_position;

    long long score{ 0 };           // Real score.   
    long long screen_score{ score };// Score displayed on screen.

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            if (!MUTE_isPressed)
            {
                MUTE_isPressed = true;
                if (music.getStatus() == sf::SoundSource::Status::Playing)
                    music.pause();
                else
                    music.play();
            }
        }
        else
        {
            MUTE_isPressed = false;
        }


        if (!GAME_OVER)
        {
            for (int x{ 0 }; x < 10; ++x)
                for (int y{ 0 }; y < 20; ++y)
                    activeBlocks[x][y] = grid[x][y].getActive();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                if (!TURN_isPressed)
                {
                    TURN_isPressed = true;
                    playerPiece.turn(activeBlocks);
                }
            }
            else
            {
                TURN_isPressed = false;
            }


            if (inputClock.getElapsedTime().asMilliseconds() > 100)
            {
                inputClock.restart();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    playerPiece.move(false, activeBlocks);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    playerPiece.move(true, activeBlocks);
            }

            if (updateClock.getElapsedTime().asMilliseconds() > updateTime || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                updateClock.restart();
                updateTime = get_updateTime(gameClock.getElapsedTime().asSeconds());
                if (playerPiece.update(activeBlocks) == false)
                {
                    for (int i{ 0 }; i < 4; ++i)
                        grid[playerPiece.position.x + playerPiece.block_offset[i].x][playerPiece.position.y + playerPiece.block_offset[i].y] = playerPiece.blocks[i];

                    getNewPiece(playerPiece, staticPiece, nextPieceNumber, staticPiece_position, blockSize, pixelsBetweenBlocks);

                    for (int i{ 0 }; i < 4; ++i)
                    {
                        int x{ playerPiece.block_offset[i].x + playerPiece.position.x };
                        int y{ playerPiece.block_offset[i].y + playerPiece.position.y };
                        if (y < 0)
                            continue;
                        if (activeBlocks[x][y] == true)
                        {   //GAME OVER
                            //window.close();
                            inputClock.restart();
                            GAME_OVER = true;
                            break;
                        }
                    }
                }
                for (int y{ 0 }; y < 20; ++y)
                {
                    entireRow = true;
                    for (int x{ 0 }; x < 10; ++x)
                    {
                        if (activeBlocks[x][y] == false)
                        {
                            entireRow = false;
                            break;
                        }
                    }
                    if (entireRow)
                    {   // DELETE ROW
                        for (int _y{ y }; _y > 0; --_y)
                            for (int i{ 0 }; i < 10; ++i)
                                grid[i][_y] = grid[i][_y - 1];

                        for (int i{ 0 }; i < 10; ++i)
                            grid[i][0] = block();
                        score += increaseScore(gameClock.getElapsedTime().asSeconds());
                    }
                }
            }

            if (screen_score < score)
            {
                ++screen_score;
                if (screen_score < 10)
                    scoreString = "000";
                else if (screen_score < 100)
                    scoreString = "00";
                else if (screen_score < 1000)
                    scoreString = "0";
                else
                    scoreString = "";

                scoreString += toString(screen_score);
                scoreValueText.setString(scoreString);
            }
        }
        else
        {
            if (score < 10)
                scoreString = "000";
            else if (score < 100)
                scoreString = "00";
            else if (score < 1000)
                scoreString = "0";
            else
                scoreString = "";
            scoreString += toString(score);
            scoreValueText.setString(scoreString);
        }

        window.clear();

        drawGrid(grid, blockSize, pixelsBetweenBlocks, window);
        playerPiece.draw(window);
        window.draw(horizontalLimit);
        window.draw(verticalLimit);
        staticPiece.draw(window);
        window.draw(scoreTitleText);
        window.draw(scoreValueText);

        if (GAME_OVER)
        {
            window.draw(GameOver_TitleText);
            if (inputClock.getElapsedTime().asMilliseconds() > 1000)
            {
                if (isAnyKeyPressed())
                {   // RESTART GAME
                    GAME_OVER = false;
                    getNewPiece(playerPiece, staticPiece, nextPieceNumber, staticPiece_position, blockSize, pixelsBetweenBlocks);
                    for (int x{ 0 }; x < 10; ++x)
                        for (int y{ 0 }; y < 20; ++y)
                            grid[x][y] = block();

                    gameClock.restart();
                    updateClock.restart();
                    inputClock.restart();
                    score = 0;
                    screen_score = -1;
                }
                if (updateClock.getElapsedTime().asMilliseconds() > 500)
                {
                    showPressKeyText = !showPressKeyText;
                    updateClock.restart();
                }
                if(showPressKeyText)
                    window.draw(GameOver_PressKeyText);
            }
        }

        window.display();
    }
    return 0;
}