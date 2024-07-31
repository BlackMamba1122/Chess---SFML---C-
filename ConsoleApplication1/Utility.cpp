#include"Utility.h"
#include<iostream>
void box(float x, float y, sf::Color c, sf::RenderWindow& window)
{
	x = 300 + (x * 113) + 33;
	y = (y * 112) + 12.5;
	sf::RectangleShape rectangle(sf::Vector2f(114 - 5, 114 - 5));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(c);
	sf::Color borderColor = c;
	borderColor.r = std::max(0, int(borderColor.r) - 50);
	borderColor.g = std::max(0, int(borderColor.g) - 50);
	borderColor.b = std::max(0, int(borderColor.b) - 50);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(borderColor);
	window.draw(rectangle);
}

void framedraw(float x, float y, sf::Sprite c, sf::RenderWindow& window)
{
	x = 300 + (x * 113) + 33;
	y = (y * 112) + 12.5;
	c.setPosition(x, y);
	window.draw(c);
}