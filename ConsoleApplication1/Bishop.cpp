#include "Bishop.h"
#include "iostream"

Bishop::Bishop(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}

void Bishop::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(0.75f, 0.6f);


	int n;
	if (c == White)
		n = 1;
	else
		n = 0;
	piece.setTextureRect(sf::IntRect(piece_size.x * 2, piece_size.y * n, piece_size.x, piece_size.y));

	piece.setPosition(300 + 85 + (col * 114), 60 + (row * 112));


	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}
bool Bishop::isLegal(position move)
{
	return (isDiagnolmove(move) && isDiagnolClear(move));
}

char Bishop::getSym()
{
	return 'b';
}

sf::Sprite Bishop::getsprite()
{
	return piece;
}