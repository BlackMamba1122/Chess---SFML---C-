#include "Rook.h"
#include "iostream"

Rook::Rook(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}

void Rook::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(1.f, 0.65f);
	int n;
	if (c == White)
		n = 1;
	else
		n = 0;

	piece.setTextureRect(sf::IntRect(piece_size.x * 4, piece_size.y * n, piece_size.x, piece_size.y));
	piece.setPosition(300 + 85 + (col * 114), 50 + (row * 112));

	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}



bool Rook::isLegal(position move)
{
	return ((isHorizontalmove(move) && isHorizontalClear(move)) || (isVerticalmove(move) && isVerticalClear(move)));
}

char Rook::getSym()
{
	return 'r';
}

sf::Sprite Rook::getsprite()
{
	return piece;
}