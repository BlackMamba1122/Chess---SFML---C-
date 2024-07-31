#pragma once
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <stack>
using namespace std;
class Piece;
class Board
{
	Piece* Ps[8][8];
	Piece* temp;
	sf::Texture pieces;
	sf::Vector2u piece_size;
public:
	std::stack<info>undo;
	Board();
	void init();
	Piece* getpiece(position loc);
	void displayBoard(sf::RenderWindow& window);
	void movee(position select, position move, bool c, bool d = 0);
	void Undoo(sf::RenderWindow& window, bool replay, info tempinfo = { {0,0 } ,{0,0},nullptr }, Color c = Black, char piece = ' ');
	void UndooUpdate(info temp, bool replay, sf::RenderWindow& window);
	void displayTurnMsg(int p, sf::RenderWindow& window);
};
