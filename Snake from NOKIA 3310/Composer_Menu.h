#pragma once
#include "Menu.h"
class Composer_Menu :
	public Menu
{
private:
	void item_selected(int id);

public:
	Composer_Menu();
	~Composer_Menu();
};

