#pragma once
#include "Menu.h"
class TTT_OX_Select :
	public Menu
{
private:
	void item_selected(int id);

public:
	TTT_OX_Select();
	~TTT_OX_Select();
};

