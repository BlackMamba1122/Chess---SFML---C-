#include "Pawn.h"
#include "iostream"
#include "Board.h"
#include<SFML/Graphics.hpp>
Pawn::Pawn(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}


void Pawn::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(0.8f, 0.7f);
	int n;
	if (c == White)
		n = 1;
	else
		n = 0;
	piece.setTextureRect(sf::IntRect(piece_size.x * 5, piece_size.y * n, piece_size.x, piece_size.y));
	piece.setPosition(300 + 85 + (col * 114), 40 + (row * 112));

	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}

bool Pawn::isLegal(position move)
{
	if (c == Black && (move.ri - pos.ri) < 0)
		return false;
	else if (c == White && (move.ri - pos.ri) > 0)
		return false;
	int dr = abs(pos.ri - move.ri);
	int dc = abs(pos.ci - move.ci);

	if (b->getpiece(move) == nullptr)
	{
		if (!first)
			return ((dr < 3 && dr>0) && dc == 0);
		else
			return ((dr < 2 && dr>0) && dc == 0);
	}
	else
		return(dr == 1 && dc == 1);
}

char Pawn::getSym()
{
	return 'p';
}

sf::Sprite Pawn::getsprite()
{
	return piece;
}