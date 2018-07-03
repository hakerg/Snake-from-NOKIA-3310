#pragma once
#include "Menu.h"
class TTT_New_Select :
	public Menu
{
private:
	void item_selected(int id);

public:
	TTT_New_Select();
	~TTT_New_Select();
};

