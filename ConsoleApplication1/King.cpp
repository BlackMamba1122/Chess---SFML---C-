#include "King.h"
#include "iostream"
#include "Queen.h"
King::King(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}

void King::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(0.85f, 0.51f);

	int n;
	if (c == White)
		n = 1;
	else
		n = 0;
	piece.setTextureRect(sf::IntRect(piece_size.x * 0, piece_size.y * n, piece_size.x, piece_size.y));
	piece.setPosition(300 + 85 + (col * 114), 65 + (row * 112));

	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}

bool King::isLegal(position move)
{
	int dr = pos.ri - move.ri;
	int dc = pos.ci - move.ci;
	return ((dr<2 && dr>-2) && (dc<2 && dc>-2) && Queen(pos, c, b, pieces, piece_size).isLegal(move));
}

char King::getSym()
{
	return 'k';
}

sf::Sprite King::getsprite()
{
	return piece;
}