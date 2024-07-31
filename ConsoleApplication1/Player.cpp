#include "Player.h"

Player::Player(string _s, Color _c)
{
	name = _s;
	c = _c;
}

string Player::getname()
{
	return name;
}

Color Player::getcolor()
{
	return c;
}