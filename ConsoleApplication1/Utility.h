#pragma once
class Piece;
struct position
{
	int ri;
	int ci;
};

struct info
{
	position start;
	position end;
	Piece* piece;
};
enum Color { Black, White };
#include<SFML/Graphics.hpp>
void box(float x, float y, sf::Color c, sf::RenderWindow& window);
void framedraw(float x, float y, sf::Sprite c, sf::RenderWindow& window);