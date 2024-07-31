#include <SFML/Graphics.hpp>
#include "Chess.h"
#include "iostream"
#include <Windows.h>
#include <fstream>
#include <SFML/Audio.hpp>

using namespace std;
Chess::Chess()
{
	move.ri = 0, move.ci = 0, select.ri = 0, select.ci = 0;
	ply[0] = new Player("Ahmad1", Black);
	ply[1] = new Player("Ahmad2", White);
	b = new Board();
	turn = 0;
}

void Chess::start(sf::RenderWindow& window, bool& rep)
{
	sf::RectangleShape bck(sf::Vector2f(1550, 950));
	sf::Texture bckk;
	bckk.loadFromFile("screen.jpeg");
	bck.setTexture(&bckk);

	sf::Sprite play;
	sf::Sprite conti;
	sf::Texture playy;
	sf::Texture contii;
	playy.loadFromFile("play.png");
	contii.loadFromFile("continue.png");
	play.setTexture(playy);
	conti.setTexture(contii);
	play.setPosition(350.f, 700.f);
	conti.setPosition(870.f, 700.f);
	play.setScale(1.5f, 1.5f);
	conti.setScale(1.5f, 1.5f);

	float hoverScale = 1.72f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (play.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						rep = false;
						return;
					}
					if (conti.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						rep = true;
						return;
					}
				}
			}
			if (play.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				play.setScale(hoverScale, hoverScale);
			else
				play.setScale(1.5f, 1.5f);
			if (conti.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				conti.setScale(hoverScale, hoverScale);
			else
				conti.setScale(1.5f, 1.5f);
		}
		window.clear();
		window.draw(bck);
		window.draw(play);
		window.draw(conti);
		window.display();
	}
}


bool Chess::validSelect(position _select)
{
	if (_select.ri < 0 || _select.ri>7 || _select.ci < 0 || _select.ci >7)
		return false;
	Piece* piece = b->getpiece(_select);
	return piece != nullptr && piece->getcolor() == ply[turn]->getcolor();
}

bool Chess::validmove(position _move)
{
	if (_move.ri < 0 || _move.ri>7 || _move.ci < 0 || _move.ci >7)
		return false;
	Piece* piece = b->getpiece(_move);
	return piece == nullptr || piece->getcolor() != ply[turn]->getcolor();
}

void Chess::turnChange()
{
	turn++;
	if (turn > 1)
		turn = 0;
}

void Chess::highlight(bool H[][8], position _select)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			H[ri][ci] = ((validmove(position{ ri,ci })) && (b->getpiece(_select)->isLegal(position{ ri,ci })));
			if (H[ri][ci])
				selfcheck(H, _select, ri, ci, 0, 0);
		}
}

void Chess::highlightBox(bool H[][8], sf::Color c, sf::RenderWindow& window)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (H[ri][ci])
			{
				if (b->getpiece(position{ ri,ci }) != nullptr)
					box(ci, ri, sf::Color(224, 60, 60), window);
				else
					box(ci, ri, c, window);

			}
		}
}

bool Chess::check(int& kr, int& kc)
{
	turnChange();
	findKing(kr, kc);
	turnChange();
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
			if (validSelect(position{ ri,ci }))
				if ((validmove(position{ kr,kc })) && (b->getpiece(position{ ri,ci })->isLegal(position{ kr,kc })))
					return true;
	return false;
}

void Chess::findKing(int& kr, int& kc)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (b->getpiece(position{ ri,ci }) != nullptr)
				if (b->getpiece(position{ ri,ci })->getcolor() == ply[turn]->getcolor())
					if (b->getpiece(position{ ri,ci })->getSym() == 'k')
					{
						kr = ri;
						kc = ci;
					}
		}
}

void Chess::legality(bool H[][8], position _select, int kr, int kc)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (H[ri][ci])
			{
				selfcheck(H, _select, ri, ci, kr, kc);
			}
		}
}

void Chess::selfcheck(bool H[][8], position _select, int ri, int ci, int kr, int kc)
{
	b->movee(_select, position{ ri,ci }, 0, 0);
	turnChange();
	H[ri][ci] = !check(kr, kc);
	b->movee(position{ ri,ci }, _select, 0, 1);
	turnChange();
}

void Chess::castling(bool H[][8], position _select)
{
	if (!b->getpiece(_select)->getFirst() && b->getpiece(position{ _select.ri,7 }) != nullptr)
		if (!b->getpiece(position{ _select.ri,7 })->getFirst())
			if (b->getpiece(position{ _select.ri,5 }) == nullptr && b->getpiece(position{ _select.ri,6 }) == nullptr)
			{
				selfcheck(H, _select, _select.ri, 5);
				if (H[_select.ri][5])
					selfcheck(H, _select, _select.ri, 6);
			}
	if (!b->getpiece(_select)->getFirst() && b->getpiece(position{ _select.ri,0 }) != nullptr)
		if (!b->getpiece(position{ _select.ri,0 })->getFirst())
			if (b->getpiece(position{ _select.ri,3 }) == nullptr && b->getpiece(position{ _select.ri,2 }) == nullptr && b->getpiece(position{ _select.ri,1 }) == nullptr)
			{
				selfcheck(H, _select, _select.ri, 3);
				if (H[_select.ri][3])
					selfcheck(H, _select, _select.ri, 2);
			}
}

bool Chess::moveAvaliable(bool H[][8])
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
			if (H[ri][ci])
				return true;
	return false;
}

bool Chess::gameEnd()
{
	bool H[8][8];
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (validSelect(position{ ri,ci }))
			{
				highlight(H, position{ ri,ci });
				legality(H, position{ ri,ci });
				if (moveAvaliable(H))
					return true;
			}
		}
	return false;
}


void Chess::play()
{
	bool rep = false;
	position a1({ 0,0 });
	position a2({ 0,0 });
	sf::RenderWindow window(sf::VideoMode(1550, 950), "CHESS");
	start(window, rep);
	fstream rdr;
	int kr = -1, kc = -1;
	bool H[8][8], Ischeck = false, soundcheck = true;
	bool game = true;
	bool Undo = false;
	bool isSelect = false, isMove = false, prevmove = false;

	sf::RectangleShape background(sf::Vector2f(950, 950));
	sf::Texture backgroundTex;
	background.setPosition(300.f, 0.f);
	backgroundTex.loadFromFile("board.png");
	background.setTexture(&backgroundTex);

	sf::RectangleShape checkmate(sf::Vector2f(1550, 950));
	sf::Texture checkmatee;
	checkmatee.loadFromFile("c.jpg");
	checkmate.setTexture(&checkmatee);

	sf::RectangleShape stalemate(sf::Vector2f(1550, 950));
	sf::Texture stale;
	stale.loadFromFile("stale.png");
	stalemate.setTexture(&stale);

	sf::Text text;
	sf::Font font;
	font.loadFromFile("race.ttf");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setPosition(450.f, 100.f);

	sf::SoundBuffer movee;
	movee.loadFromFile("move.mp3");
	sf::SoundBuffer capturee;
	capturee.loadFromFile("capture.mp3");
	sf::SoundBuffer notifyy;
	notifyy.loadFromFile("notify.mp3");

	sf::Sprite frame;
	sf::Texture framee;
	framee.loadFromFile("frame.png");
	frame.setTexture(framee);
	frame.setScale(0.21f, 0.23f);

	sf::Sound movem;
	movem.setBuffer(movee);
	sf::Sound notify;
	notify.setBuffer(notifyy);
	sf::Sound capture;
	capture.setBuffer(capturee);


	if (rep)
	{
		replay(window, background, Ischeck, game, kr, kc);
		rdr.open("info.txt", std::ios::in | std::ios::out | std::ios::app);
	}
	else
		rdr.open("info.txt", std::ios::in | std::ios::out | std::ios::trunc);

	////////////////////////////////////////////
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					if (!isSelect)
					{
						select.ri = (position.y - 13) / 110;
						select.ci = (position.x - 32 - 300) / 115;
						isSelect = validSelect(select);
					}
					else
					{
						move.ri = (position.y - 13) / 110;
						move.ci = (position.x - 32 - 300) / 115;
						isMove = H[move.ri][move.ci];
						isSelect = false;
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isSelect)
				{
					if (b->undo.empty())
						continue;
					Undo = true;
					isMove = true;
				}
			}
		}
		if (isSelect)
		{
			highlight(H, select);
			legality(H, select, kr, kc);
			if (Ischeck && b->getpiece(select)->getSym() == 'k')
				castling(H, select);
			if (!moveAvaliable(H))
			{
				isSelect = false;
				continue;
			}
		}
		if (isMove)
		{
			if (Undo)
			{
				info a = b->undo.top();
				if (a.piece != nullptr)
					rdr << Undo << "  " << a.start.ri << "  " << a.start.ci << "  " << a.end.ri << "  " << a.end.ci << "  " << a.piece->getSym() << " " << a.piece->getcolor() << endl;
				else
					rdr << Undo << "  " << a.start.ri << "  " << a.start.ci << "  " << a.end.ri << "  " << a.end.ci << "   -   " << endl;

				b->Undoo(window, 0);
				Ischeck = false;
				soundcheck = true;
				Undo = false;
				isMove = false;
				prevmove = false;
			}
			else
			{
				rdr << Undo << "  " << select.ri << "  " << select.ci << "  " << move.ri << "  " << move.ci << endl;
				if (Ischeck)
				{
					Ischeck = false;
					soundcheck = true;
				}

				if (b->getpiece(select)->getSym() == 'k')
				{
					if (select.ci - move.ci == 2)
						b->movee(position{ select.ri,0 }, position{ select.ri,3 }, 1);
					else if (select.ci - move.ci == -2)
						b->movee(position{ select.ri,7 }, position{ select.ri,5 }, 1);
				}
				b->movee(select, move, 1);
				Ischeck = check(kr, kc);
				if (!Ischeck)
				{
					box(move.ci, move.ri, sf::Color::Black, window);
					if (b->undo.top().piece != nullptr)
						capture.play();
					else
						movem.play();
				}
				prevmove = true;
			}
			rdr << endl;
			if (Ischeck && soundcheck)
				soundcheck = true;
			turnChange();
			if (!gameEnd())
				game = false;
		}
		window.clear();
		b->displayTurnMsg(turn, window);
		if (game)
		{
			window.draw(background);
			if (prevmove)
			{
				if (isMove)
				{
					a1 = select;
					a2 = move;
					isMove = false;
				}
				framedraw(a1.ci, a1.ri, frame, window);
				box(a2.ci, a2.ri, sf::Color(242, 198, 67), window);
			}
			if (isSelect)
			{
				box(select.ci, select.ri, sf::Color(75, 216, 20), window);
				highlightBox(H, sf::Color(22, 222, 226), window);
			}
			if (Ischeck)
			{
				box(kc, kr, sf::Color(102, 0, 0), window);
				if (soundcheck)
				{
					notify.play();
					soundcheck = false;
				}
			}
			b->displayBoard(window);
		}
		else
		{
			if (Ischeck)
			{
				window.draw(checkmate);
				if (turn)
					text.setString("Blue wins");
				else
					text.setString("Red wins");
				window.draw(text);
			}
			else
				window.draw(stalemate);
			isMove = false;

		}
		window.display();
	}
	////////////////////////////////////////////
}

void Chess::replay(sf::RenderWindow& window, sf::RectangleShape background, bool& Ischeck, bool& game, int& kr, int& kc)
{
	ifstream rdr;
	rdr.open("info.txt", std::ios::in);
	bool Undo = false;
	int n = 700;
	while (rdr >> Undo)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
				n = 0;
		}
		window.clear();
		if (game)
		{
			window.draw(background);
			if (Ischeck)
				box(kc, kr, sf::Color::Red, window);
		}
		b->displayBoard(window);
		window.display();
		Sleep(n);
		if (Ischeck)
			Ischeck = false;
		if (Undo)
		{
			info temp;
			char sym;
			int c = 0;
			rdr >> temp.start.ri >> temp.start.ci >> temp.end.ri >> temp.end.ci >> sym;
			temp.piece = nullptr;
			if (sym != '-')
			{
				rdr >> c;
			}
			if (c == 0)
				b->Undoo(window, 1, temp, Black, sym);
			else
				b->Undoo(window, 1, temp, White, sym);

		}
		else
		{
			rdr >> select.ri >> select.ci >> move.ri >> move.ci;
			b->movee(select, move, 1);
		}
		if (Ischeck)
		{
			if (b->getpiece(position{ kr,kc }) != nullptr)
			{
				if (b->getpiece(move) != nullptr)
				{
					if (b->getpiece(move)->getSym() == 'k')
					{
						if (select.ci - move.ci == 2)
							b->movee(position{ select.ri,0 }, position{ select.ri,3 }, 1);
						else if (select.ci - move.ci == -2)
							b->movee(position{ select.ri,7 }, position{ select.ri,5 }, 1);
					}
				}
			}
		}
		Ischeck = check(kr, kc);
		turnChange();
		if (!gameEnd())
			game = false;
	}
}