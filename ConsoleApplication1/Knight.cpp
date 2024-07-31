#include "Knight.h"
#include "iostream"

Knight::Knight(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}

void Knight::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(0.85f, 0.58f);


	int n;
	if (c == White)
		n = 1;
	else
		n = 0;
	piece.setTextureRect(sf::IntRect(piece_size.x * 3, piece_size.y * n, piece_size.x, piece_size.y));
	piece.setPosition(300 + 85 + (col * 113), 60 + (row * 112));


	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}

bool Knight::isLegal(position move)
{
	return abs((pos.ri - move.ri) * (pos.ci - move.ci)) == 2;
}

char Knight::getSym()
{
	return 'n';
}

sf::Sprite Knight::getsprite()
{
	return piece;
}