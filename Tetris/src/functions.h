#pragma once
#include "block.h"
#include "piece.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <cstdlib>
#include <sstream>
#include <ctime>

int get_randomPieceNumber(const int maxPossibleNumber = 7);
int get_updateTime(const float seconds);
int increaseScore(const float seconds);
sf::String toString(const long long input);
void drawGrid(block (&grid)[10][20], const int blockSize, const int pixelsBetweenBlocks, sf::RenderWindow& window);
bool isAnyKeyPressed();
void getNewPiece(piece& player, piece& staticPiece, int& nextPieceNumber, const sf::Vector2i staticPiece_position, const int blockSize, const int pixelsBetweenBlocks);