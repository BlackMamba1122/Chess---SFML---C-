#pragma once
#include "Board.h"
#include "Utility.h"
#include "Player.h"
class Chess
{
	position select, move;
	Player* ply[2];
	Board* b;
	int turn;
public:
	Chess();
	void start(sf::RenderWindow& window, bool& rep);
	void play();
	void replay(sf::RenderWindow& window, sf::RectangleShape background, bool& Ischeck, bool& game, int& kr, int& kc);
private:
	bool validSelect(position _select);
	bool validmove(position _move);
	void turnChange();
	void highlight(bool H[][8], position _select);
	void highlightBox(bool H[][8], sf::Color c, sf::RenderWindow& window);
	bool check(int& kr, int& kc);
	void findKing(int& kr, int& kc);
	void legality(bool H[][8], position _select, int kr = 0, int kc = 0);
	void selfcheck(bool H[][8], position _select, int ri, int ci, int kr = 0, int kc = 0);
	void castling(bool H[][8], position _select);
	bool moveAvaliable(bool H[][8]);
	bool gameEnd();
};
