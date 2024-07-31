#include "Board.h"
#include "iostream"
using namespace std;
Board::Board()
{
	pieces.loadFromFile("pieces.png");
	piece_size = pieces.getSize();
	piece_size.x /= 6;
	piece_size.y /= 2;
	init();
}

void Board::init()
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (ri == 1)
				Ps[ri][ci] = new Pawn(position{ ri,ci }, Black, this, pieces, piece_size);
			else if (ri == 6)
				Ps[ri][ci] = new Pawn(position{ ri,ci }, White, this, pieces, piece_size);

			else if (ri == 0 && (ci == 0 || ci == 7))
				Ps[ri][ci] = new Rook(position{ ri,ci }, Black, this, pieces, piece_size);

			else if (ri == 7 && (ci == 0 || ci == 7))
				Ps[ri][ci] = new Rook(position{ ri,ci }, White, this, pieces, piece_size);

			else if (ri == 0 && (ci == 1 || ci == 6))
				Ps[ri][ci] = new Knight(position{ ri,ci }, Black, this, pieces, piece_size);
			else if (ri == 7 && (ci == 1 || ci == 6))
				Ps[ri][ci] = new Knight(position{ ri,ci }, White, this, pieces, piece_size);

			else if (ri == 0 && (ci == 2 || ci == 5))
				Ps[ri][ci] = new Bishop(position{ ri,ci }, Black, this, pieces, piece_size);
			else if (ri == 7 && (ci == 2 || ci == 5))
				Ps[ri][ci] = new Bishop(position{ ri,ci }, White, this, pieces, piece_size);

			else if (ri == 0 && ci == 3)
				Ps[ri][ci] = new Queen(position{ ri,ci }, Black, this, pieces, piece_size);

			else if (ri == 7 && ci == 3)
				Ps[ri][ci] = new Queen(position{ ri,ci }, White, this, pieces, piece_size);

			else if (ri == 0 && ci == 4)
				Ps[ri][ci] = new King(position{ ri,ci }, Black, this, pieces, piece_size);
			else if (ri == 7 && ci == 4)
				Ps[ri][ci] = new King(position{ ri,ci }, White, this, pieces, piece_size);

			else
				Ps[ri][ci] = nullptr;

		}
	}

}

Piece* Board::getpiece(position loc)
{
	return Ps[loc.ri][loc.ci];
}


void Board::displayBoard(sf::RenderWindow& window)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (Ps[ri][ci] == nullptr)
				continue;
			else
				Ps[ri][ci]->draw(ri, ci, window);
		}
	}
}
void Board::movee(position select, position move, bool c, bool d)
{
	if (!d)
		temp = Ps[move.ri][move.ci];
	if (c)
	{
		undo.push({ select, move, temp });
	}
	Ps[select.ri][select.ci]->Move(move);
	Ps[move.ri][move.ci] = Ps[select.ri][select.ci];
	if (c)
	{
		if (Ps[select.ri][select.ci]->getFirst() == false)
			Ps[select.ri][select.ci]->setFirst(true);
		Ps[select.ri][select.ci] = nullptr;
	}
	else
	{

		if (d)
			Ps[select.ri][select.ci] = temp;
		else
			Ps[select.ri][select.ci] = nullptr;
	}
}

void Board::Undoo(sf::RenderWindow& window, bool replay, info tempinfo, Color c, char piece)
{
	if (!replay)
		tempinfo = undo.top();
	if (Ps[tempinfo.end.ri][tempinfo.end.ci]->getSym() == 'k')
	{

		if (tempinfo.start.ci - tempinfo.end.ci == 2)
		{
			Ps[tempinfo.end.ri][3]->Move({ tempinfo.start.ri, 0 });
			Ps[tempinfo.start.ri][0] = Ps[tempinfo.end.ri][3];
			Ps[tempinfo.end.ri][3] = nullptr;
			UndooUpdate({ {tempinfo.start.ri,0},{tempinfo.end.ri,3},nullptr }, 0, window);
		}
		else if (tempinfo.start.ci - tempinfo.end.ci == -2)
		{
			Ps[tempinfo.end.ri][5]->Move({ tempinfo.start.ri, 7 });
			Ps[tempinfo.start.ri][7] = Ps[tempinfo.end.ri][5];
			Ps[tempinfo.end.ri][5] = nullptr;
			UndooUpdate({ {tempinfo.start.ri,7},{tempinfo.end.ri,5},nullptr }, 0, window);
		}

	}
	Ps[tempinfo.end.ri][tempinfo.end.ci]->Move(tempinfo.start);
	Ps[tempinfo.start.ri][tempinfo.start.ci] = Ps[tempinfo.end.ri][tempinfo.end.ci];
	if (!replay)
		Ps[tempinfo.end.ri][tempinfo.end.ci] = tempinfo.piece;
	else
	{
		switch (piece)
		{
		case'-':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = nullptr;
			break;
		case'p':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new Pawn(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;
		case'r':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new Rook(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;
		case'n':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new Knight(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;
		case'b':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new Bishop(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;
		case'q':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new Queen(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;
		case'k':
			Ps[tempinfo.end.ri][tempinfo.end.ci] = new King(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this, pieces, piece_size);
			break;

		}
	}
	if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getSym() == 'p')
	{
		if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getcolor() == Black && tempinfo.start.ri == 1)
			Ps[tempinfo.start.ri][tempinfo.start.ci]->setFirst(false);
		if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getcolor() == White && tempinfo.start.ri == 6)
			Ps[tempinfo.start.ri][tempinfo.start.ci]->setFirst(false);
	}
	if (piece != '-' && replay)
		UndooUpdate(tempinfo, 1, window);
	else
		UndooUpdate(tempinfo, 0, window);
	undo.pop();
}
void Board::UndooUpdate(info temp, bool replay, sf::RenderWindow& window)
{
	Ps[temp.start.ri][temp.start.ci]->draw(temp.start.ri, temp.start.ci, window);
	if (temp.piece != nullptr || replay)
		Ps[temp.end.ri][temp.end.ci]->draw(temp.end.ri, temp.end.ci, window);
}

void Board::displayTurnMsg(int p, sf::RenderWindow& window)
{
	sf::Sprite piece;
	piece.setTexture(pieces);
	piece.setScale(1.9f, 1.4f);

	piece.setTextureRect(sf::IntRect(piece_size.x * 0, piece_size.y * p, piece_size.x, piece_size.y));
	if (p == 0)
		piece.setPosition(150, 170);
	else
		piece.setPosition(1380, 170);

	sf::FloatRect bounds = piece.getLocalBounds();
	piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	window.draw(piece);
}