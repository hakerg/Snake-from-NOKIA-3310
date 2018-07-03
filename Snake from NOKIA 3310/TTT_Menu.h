#pragma once
#include "Menu.h"
class TTT_Menu :
	public Menu
{
private:
	void item_selected(int id);

public:
	TTT_Menu();
	~TTT_Menu();
};

