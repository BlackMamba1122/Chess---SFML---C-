#include "Piece.h"
#include<cmath>
#include"Board.h"
#include<iostream>
using namespace std;
Piece::Piece(position _p, Color _c, Board* _b)
{
	pos = _p;
	c = _c;
	b = _b;
	first = false;
}

void Piece::Move(position _p)
{
	pos = _p;
}

Color Piece::getcolor()
{
	return c;
}

bool Piece::getFirst()
{
	return first;
}

void Piece::setFirst(bool a)
{
	first = a;
}

bool Piece::isHorizontalmove(position move)
{
	return pos.ri == move.ri;
}

bool Piece::isVerticalmove(position move)
{
	return pos.ci == move.ci;

}

bool Piece::isDiagnolmove(position move)
{
	return (abs(pos.ri - move.ri) == abs(pos.ci - move.ci));
}

bool Piece::isHorizontalClear(position move)
{
	if (pos.ci < move.ci)
	{
		for (int i = pos.ci + 1; i < move.ci; i++)
			if (b->getpiece(position{ pos.ri, i }) != nullptr)
				return false;
	}
	else
	{
		for (int i = move.ci + 1; i < pos.ci; i++)
			if (b->getpiece(position{ pos.ri, i }) != nullptr)
				return false;
	}
	return true;
}

bool Piece::isVerticalClear(position move)
{
	if (pos.ri < move.ri)
	{
		for (int i = pos.ri + 1; i < move.ri; i++)
			if (b->getpiece(position{ i, pos.ci }) != nullptr)
				return false;
	}
	else
	{
		for (int i = move.ri + 1; i < pos.ri; i++)
			if (b->getpiece(position{ i, pos.ci }) != nullptr)
				return false;
	}
	return true;
}


bool Piece::isDiagnolClear(position move)
{
	int dr = move.ri - pos.ri;
	int dc = move.ci - pos.ci;

	for (int i = 1; i < abs(dr); i++)
	{
		if (dr > -1 && dc > -1)
		{
			if (b->getpiece(position{ pos.ri + i, pos.ci + i }) != nullptr)
				return false;
		}
		else if (dr<0 && dc>-1)
		{
			if (b->getpiece(position{ pos.ri - i, pos.ci + i }) != nullptr)
				return false;
		}
		else if (dr > -1 && dc < 0)
		{
			if (b->getpiece(position{ pos.ri + i, pos.ci - i }) != nullptr)
				return false;
		}
		else
		{
			if (b->getpiece(position{ pos.ri - i, pos.ci - i }) != nullptr)
				return false;
		}

	}
	return true;
}