
#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
    sf::Sprite piece;
    sf::Texture pieces;
    sf::Vector2u piece_size;
public:
    Pawn(position _p, Color _c, Board* _b, sf::Texture pieces, sf::Vector2u piece_size);
    void draw(float row, float col, sf::RenderWindow& window);
    bool isLegal(position move);
    char getSym();
    sf::Sprite getsprite();
};

