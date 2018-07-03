#pragma once
#include "Menu.h"
class Game_List :
	public Menu
{
private:
	void item_selected(int id);
	void returned();

public:
	Game_List();
	~Game_List();
};

