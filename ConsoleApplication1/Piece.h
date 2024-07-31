#pragma once
#include"Utility.h"
#include<SFML/Graphics.hpp>
class Board;
class Piece
{
protected:
	position pos;
	Color c;
	Board* b;
	bool first;
public:
	Piece(position _p, Color _c, Board* _b);
	virtual void draw(float row, float col, sf::RenderWindow& window) = 0;
	void Move(position _p);
	Color getcolor();
	virtual bool isLegal(position move) = 0;
	bool getFirst();
	void setFirst(bool a);
	virtual char getSym() = 0;
	virtual sf::Sprite getsprite() = 0;

protected:
	bool isHorizontalmove(position move);
	bool isVerticalmove(position move);
	bool isDiagnolmove(position move);
	bool isHorizontalClear(position move);
	bool isVerticalClear(position move);
	bool isDiagnolClear(position move);
};
