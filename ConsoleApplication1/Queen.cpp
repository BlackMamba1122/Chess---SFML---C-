#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Piece.h"

Queen::Queen(position _p, Color _c, Board* _b, sf::Texture _pieces, sf::Vector2u _piece_size)
	:Piece(_p, _c, _b)
{
	pieces = _pieces;
	piece_size = _piece_size;
}

void Queen::draw(float row, float col, sf::RenderWindow& window)
{
	piece.setTexture(pieces);
	piece.setScale(0.80f, 0.51f);

	int n;
	if (c == White)
		n = 1;
	else
		n = 0;
	piece.setTextureRect(sf::IntRect(piece_size.x * 1, piece_size.y * n, piece_size.x, piece_size.y));
	piece.setPosition(300 + 85 + (col * 113), 66 + (row * 112));

	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}


bool Queen::isLegal(position move)
{
	return (Rook(pos, c, b, pieces, piece_size).isLegal(move) || Bishop(pos, c, b, pieces, piece_size).isLegal(move));
}

char Queen::getSym()
{
	return 'q';
}

sf::Sprite Queen::getsprite()
{
	return piece;
}