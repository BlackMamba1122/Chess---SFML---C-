#pragma once
#include <string>
#include "Utility.h"
using namespace std;

class Player
{
	string name;
	Color c;
public:
	Player(string _s, Color _c);
	string getname();
	Color getcolor();
};
