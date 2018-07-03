#pragma once
#include "Menu.h"
class Snake_Menu :
	public Menu
{
private:
	void item_selected(int id);

public:
	Snake_Menu();
	~Snake_Menu();
};

